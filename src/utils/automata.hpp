#ifndef LTL_MODEL_CHECKING_AUTOMATA_HPP
#define LTL_MODEL_CHECKING_AUTOMATA_HPP

#include <memory>
#include <vector>
#include <unordered_set>
#include <map>
#include "formula.hpp"
#include "ts.hpp"

/**
 * State of GNBA
 * -----------------------------------
 * subset of Closure(φ)
 */
class ElementarySet {
private:
    static int counter;
    int id;
public:
    std::unordered_set<int> element; // ids of the formulas

public:
    explicit ElementarySet(std::unordered_set<int> element_) : element(std::move(element_)) {
        id = ++counter;
    }

    bool contains(int formula_id) const {
        return element.count(formula_id) > 0;
    }

    bool operator<(const ElementarySet &other) const { return id < other.id; }

    bool operator==(const ElementarySet &other) const noexcept {
        return id == other.id;
    }
};

int ElementarySet::counter{0};

/**
 * State of NBA
 * -----------------------------------
 * copy of ElementarySet
 */
class ElementarySetCopy {
public:
    std::shared_ptr<ElementarySet> original;
    int copy_id;

public:
    // ! do not move
    ElementarySetCopy(std::shared_ptr<ElementarySet> original_state, int id) : original(original_state), copy_id(id) {}

    bool operator<(const ElementarySetCopy &other) const {
        if (original == other.original) {
            return copy_id < other.copy_id;
        }
        return original < other.original;
    }

    bool operator==(const ElementarySetCopy &other) const noexcept {
        return original == other.original && copy_id == other.copy_id;
    }
};

template<typename StateType, typename AlphabetType, typename TransitCondition>
class Automata {
public:
    // all states are referred though index in this array
    std::vector<std::shared_ptr<StateType>> state; // Q

    std::unordered_set<int> AP_formula_ids;
    std::unordered_set<AtomicProposition, AtomicProposition::Hash> AP;
    std::vector<AlphabetType> alphabet; // Σ

    std::unordered_set<int> initial_state; // Q_0

    std::map<int, std::map<TransitCondition, std::unordered_set<int>>> transition;
public:
    virtual ~Automata() = default;

    void addWord(AlphabetType word) {
        alphabet.push_back(word);
    }

    /**
     * append one state into the array
     * @param state_
     * @return state_ index in array
     */
    int addState(std::shared_ptr<StateType> state_) {
        state.push_back(state_);
        return state.size() - 1;
    }

    void addInitState(int index_in_state) {
        initial_state.emplace(index_in_state);
    }

    void addTransition(int key_l1, TransitCondition key_l2, int value) {
        auto it = transition.find(key_l1);
        if (it != transition.end()) {
            auto iter = it->second.find(key_l2);
            if (iter != it->second.end()) {
                iter->second.insert(value);
            } else {
                it->second[key_l2] = {value};
            }
        } else {
            std::map<TransitCondition, std::unordered_set<int>> map_l2;
            map_l2[key_l2] = {value};
            transition.emplace(key_l1, map_l2);
            return;
        }
    }
};

/**
 * GNBA
 */

class GNBA : public Automata<ElementarySet, Word, Word> {
public:
    // F
    std::map<int, std::unordered_set<int>> accepting_state;

private:
    std::shared_ptr<FormulaBase> phi;

    int true_formula_id = -1;
    std::vector<std::shared_ptr<FormulaBase>> formula_closure;
    std::unordered_set<int> until_formula_ids;
private:

    void reformat(const std::shared_ptr<FormulaBase> &formula, std::map<std::string, int> stringToId,
                  bool use_brief_string) {
        formula->assignId(stringToId[formula->toString(use_brief_string)]);
        for (const auto &sub_formula: formula->getSubFormula()) {
            reformat(sub_formula, stringToId, use_brief_string);
        }
    }

    void getClosureAndAP() {
        bool use_brief_string = true;
        std::map<std::string, std::shared_ptr<FormulaBase>> closure = phi->getClosure(use_brief_string);
        std::map<std::string, int> stringToId;
        int validCnt = 0;
        for (const auto &sub_formula: closure) {
            sub_formula.second->assignId(validCnt);
            formula_closure.push_back(sub_formula.second);
            stringToId.emplace(sub_formula.first, validCnt);
            if (auto atomic = std::dynamic_pointer_cast<AtomicFormula>(sub_formula.second)) {
                if (atomic->isTrueFormula()) {
                    true_formula_id = validCnt;
                } else {
                    AP.emplace(atomic->getAP());
                }
            } else if (std::dynamic_pointer_cast<UntilFormula>(sub_formula.second)) {
                until_formula_ids.emplace(validCnt);
            }
            validCnt++;
        }
        // reformat to ensure all sub formulas are in the closure
        for (const auto &sub_formula: closure) {
            reformat(sub_formula.second, stringToId, use_brief_string);
        }
        // ------------------------------------------------------
//        std::cout << "===Closure===\n";
//        for (const auto &sub_formula: closure) {
//            std::cout << sub_formula.second->toString(true) << "\n";
//        }
//        std::cout << "======\n";
//        std::cout << "===AP===\n";
//        for (const auto &ap: AP) {
//            std::cout << ap.toString() << "\n";
//        }
//        std::cout << "======\n";
        // ------------------------------------------------------
    }

    void buildAlphabet() {
        std::vector<AtomicProposition> tmp_ap(AP.begin(), AP.end());
        for (int mask = 0; mask < 1 << tmp_ap.size(); ++mask) {
            std::vector<AtomicProposition> ap_list;
            for (int i = 0; i < tmp_ap.size(); ++i) {
                if (mask & (1 << i)) {
                    ap_list.push_back(tmp_ap[i]);
                }
            }
            addWord(Word(ap_list));
        }
    }

    /**
     * Check whether the subset is a valid elementary set
     * - follow the constrains in Fig 5.20 on the textbook
     * @param ids ids of subset of Closure(φ)
     * @return true if subset is a valid elementary set
     */
    bool isValidElementarySet(const std::unordered_set<int> &ids) {
        // true ∈ Closure(φ) ⇒ true ∈ B
        if (true_formula_id >= 0) {
            if (ids.count(true_formula_id) == 0) {
                return false;
            }
        }
        for (const auto &formula: formula_closure) {
            // ψ ∈ B ⇔ !ψ ∉ B, only one holds
            if (ids.count(formula->getId()) + ids.count(formula->negation->getId()) != 1) {
                return false;
            }
            // ψ1 ∧ ψ2 ∈ B ⇔ ψ1 ∈ B and ψ2 ∈ B, none or all
            if (auto ptr = std::dynamic_pointer_cast<ConjunctionFormula>(formula)) {
                size_t left_cnt = ids.count(formula->getId());
                size_t right_cnt = 0;
                for (const auto &sub_formula: ptr->getSubFormula()) {
                    right_cnt += ids.count(sub_formula->getId());
                }
                if ((left_cnt == 1 && right_cnt != 2) || (right_cnt == 2 && left_cnt == 0)) {
                    return false;
                }
            }
            // for all ψ1 ∪ ψ2
            if (until_formula_ids.count(formula->getId()) > 0) {
                auto sub_formulas = formula->getSubFormula();
                std::shared_ptr<FormulaBase> psi_1 = sub_formulas[0], psi_2 = sub_formulas[1];
                // ψ2 ∈ B ⇒ ψ1 ∪ ψ2 ∈ B
                if (ids.count(psi_2->getId()) > 0 && ids.count(formula->getId()) == 0) {
                    return false;
                }
                // ψ1 ∪ ψ2 ∈ B and ψ2 ∉ B ⇒ ψ1 ∈ B
                if (ids.count(psi_2->getId()) == 0 && ids.count(formula->getId()) > 0 &&
                    ids.count(psi_1->getId()) == 0) {
                    return false;
                }
            }
        }
        return true;
    }

    void addAcceptingState(int key, int state_id) {
        auto it = accepting_state.find(key);
        if (it != accepting_state.end()) {
            it->second.insert(state_id);
        } else {
            accepting_state[key] = {state_id};
        }
    }

    void buildStates() {
        auto closure_size = formula_closure.size();
        for (int mask = 0; mask < 1 << closure_size; ++mask) {
            std::vector<std::shared_ptr<FormulaBase>> subset;
            std::unordered_set<int> ids;
            for (int i = 0; i < closure_size; ++i) {
                if (mask & (1 << i)) {
                    ids.emplace(i);
                }
            }
            // check validity
            if (isValidElementarySet(ids)) {
                std::shared_ptr<ElementarySet> elementary_set = std::make_shared<ElementarySet>(ids);
                int state_idx = addState(elementary_set);
                // Q_0 = {B ∈ Q | φ ∈ B}
                if (ids.count(phi->getId()) > 0) {
                    addInitState(state_idx);
                }
                // F
                for (int until_formula_id: until_formula_ids) {
                    std::shared_ptr<FormulaBase> until_formula = formula_closure[until_formula_id];
                    if (ids.count(until_formula_id) == 0 || ids.count(until_formula->getSubFormula()[1]->getId()) > 0) {
                        addAcceptingState(until_formula_id, state_idx);
                    }
                }
            }
        }
        // transform to an equivalent form with at least one accepting set
        if (accepting_state.empty()) {
            std::unordered_set<int> tmp;
            for (int i = 0; i < state.size(); ++i) {
                tmp.emplace(i);
            }
            accepting_state.emplace(-1, tmp);
        }
    }

    Word stateIntersectAP(const std::shared_ptr<ElementarySet> &state_b) {
        std::vector<AtomicProposition> ap_list;
        for (const int &elem: state_b->element) {
            if (auto atomic_formula = std::dynamic_pointer_cast<AtomicFormula>(formula_closure[elem])) {
                if ((!atomic_formula->isTrueFormula())) {
                    ap_list.push_back(atomic_formula->getAP());
                }
            }
        }
        return Word(ap_list);
    }

    bool isValidTransition(const std::shared_ptr<ElementarySet> &state_b,
                           const std::shared_ptr<ElementarySet> &state_b_prime) {
        for (const auto &formula: formula_closure) {
            if (auto next_formula = std::dynamic_pointer_cast<NextFormula>(formula)) { // next formula
                auto sub_formula = next_formula->getSubFormula()[0];
                if (state_b->contains(next_formula->getId()) ^ state_b_prime->contains(sub_formula->getId())) {
                    return false;
                }
            } else if (until_formula_ids.count(formula->getId()) > 0) { // until formula
                auto sub_formulas = formula->getSubFormula();
                std::shared_ptr<FormulaBase> psi_1 = sub_formulas[0], psi_2 = sub_formulas[1];
                // ψ1 ∪ ψ2 ∈ B
                bool cond1 = state_b->contains(formula->getId());
                // ψ2 ∈ B ∨ (ψ1 ∈ B ∧ ψ1 ∪ ψ2 ∈ B')
                bool cond2 = state_b->contains(psi_2->getId()) ||
                             (state_b->contains(psi_1->getId()) && state_b_prime->contains(formula->getId()));
                if (cond1 ^ cond2) {
                    return false;
                }
            }
        }
        return true;
    }

    void buildTransition() {
        // δ(B,A) = ?
        for (int idx_b = 0; idx_b < state.size(); ++idx_b) {
            std::shared_ptr<ElementarySet> state_b = state[idx_b];
            // B ∩ AP
            Word b_ap = stateIntersectAP(state_b);
            for (const auto &word: alphabet) {
                // A ≠ B ∩ AP, δ(B,A) = ⌀
                if (!(b_ap == word)) {
                    continue;
                }
                // A = B ∩ AP,
                std::pair<int, Word> key = std::make_pair(idx_b, word);
                for (int idx_b_prime = 0; idx_b_prime < state.size(); ++idx_b_prime) {
                    std::shared_ptr<ElementarySet> state_b_prime = state[idx_b_prime];
                    if (isValidTransition(state_b, state_b_prime)) {
                        addTransition(idx_b, word, idx_b_prime);
                    }
                }
            }
        }
    }

public:
    // build GNBA
    explicit GNBA(const std::shared_ptr<FormulaBase> &formula) : phi(formula) {
        getClosureAndAP();
        buildAlphabet();
        buildStates();
        buildTransition();
//        printStates(true);
//        printTransition(true);
    }

    void printStates(bool brief) {
        std::cout << "=== States ===\t" << state.size() << "\n";
        int idx = 0;
        for (const auto &state_: state) {
            std::cout << idx << ": {\n";
            ++idx;
            for (auto formula_id: state_->element) {
                auto formula = formula_closure[formula_id];
                std::cout << "\t" << formula_id << "\t" << formula->toString(brief) << ",\n";
            }
            std::cout << "}\n";
        }
        std::cout << "=== === ===\n";

        std::cout << "=== Init States ===\t" << initial_state.size() << "\n";
        for (const auto &state_id: initial_state) {
            std::cout << "{\n";
            for (auto formula_id: state[state_id]->element) {
                auto formula = formula_closure[formula_id];
                std::cout << "\t" << formula_id << "\t" << formula->toString(brief) << ",\n";
            }
            std::cout << "}\n";
        }
        std::cout << "=== === ===\n";

        std::cout << "=== Final States ===\t" << accepting_state.size() << " sets\n";
        for (const auto &[key, state_id_set]: accepting_state) {
            std::cout << "[" << key << "]: " << state_id_set.size() << "\t<<<\n";
            for (const auto &state_id: state_id_set) {
                std::cout << "{\n";
                for (auto formula_id: state[state_id]->element) {
                    auto formula = formula_closure[formula_id];
                    std::cout << "\t" << formula_id << "\t" << formula->toString(brief) << ",\n";
                }
                std::cout << "}\n";
            }
            std::cout << ">>>\n";
        }
        std::cout << "=== === ===\n";
    }

    void printTransition(bool brief) {
        std::cout << "=== GNBA Transition ===\n";
        for (const auto &[key_l1, map_l2]: transition) {
            for (const auto &[key_l2, id_set]: map_l2) {
                std::cout << key_l1 << "\t" << key_l2.toString() << "\n==>";
                for (auto id: id_set) {
                    std::cout << "\t" << id << "\n";
                }
            }
        }
        std::cout << "=== === === ===\n";
    }
};

/**
 * NBA
 */
class NBA : public Automata<ElementarySetCopy, Word, Word> {
public:
    std::unordered_set<int> accepting_state;

public:
    // build NBA from GNBA
    explicit NBA(const GNBA &automata) {
        auto copy_number = automata.accepting_state.size();
        std::vector<std::unordered_set<int>> accepting_states_in_gnba;
        for (const auto &[key, state_id_set]: automata.accepting_state) {
            accepting_states_in_gnba.push_back(state_id_set);
        }
        if (copy_number == 0) {
            throw NotSupportedError("expect at least one accepting all_state set in GNBA");
        }
        std::map<std::pair<int, int>, int> state_map; // (original_idx, copy_id) -> new_idx
        // Q' = Q x {1, ..., k}
        for (int original_state_idx = 0; original_state_idx < automata.state.size(); ++original_state_idx) {
            std::shared_ptr<ElementarySet> original_state = automata.state[original_state_idx];
            for (int copy_id = 1; copy_id <= copy_number; ++copy_id) {
                std::shared_ptr<ElementarySetCopy> state_copy
                        = std::make_shared<ElementarySetCopy>(original_state, copy_id);
                int state_idx = addState(state_copy);
                state_map[std::make_pair(original_state_idx, copy_id)] = state_idx;
                if (copy_id == 1) {
                    // Q_0' = Q_0 x {1}
                    if (automata.initial_state.count(original_state_idx) > 0) {
                        addInitState(state_idx);
                    }
                    // F' = F x {1}
                    if (accepting_states_in_gnba[0].count(original_state_idx) > 0) {
                        accepting_state.emplace(state_idx);
                    }
                }
            }
        }
        // same alphabet
        AP = automata.AP;
        AP_formula_ids = automata.AP_formula_ids;
        alphabet = automata.alphabet;
        // transition
        for (const auto &[org_src_state_idx, map_l2]: automata.transition) {
            for (int copy_id = 1; copy_id <= copy_number; ++copy_id) {
                int src_state_idx = state_map[{org_src_state_idx, copy_id}];
                for (const auto &[word, state_id_set]: map_l2) {
                    for (int org_dst_state_idx: state_id_set) { // (org_src_state_idx, key_pair.second) -> org_dst_state_idx
                        int dst_state_idx;
                        if (accepting_states_in_gnba[copy_id - 1].count(org_src_state_idx) > 0) {
                            int next_copy_id = copy_id + 1 > copy_number ? copy_id + 1 - copy_number : copy_id + 1;
                            dst_state_idx = state_map[{org_dst_state_idx, next_copy_id}];
                        } else {
                            dst_state_idx = state_map[{org_dst_state_idx, copy_id}];
                        }
                        addTransition(src_state_idx, word, dst_state_idx);
                    }
                }
            }
        }
    }

    std::unordered_set<int> getInit() const {
        return initial_state;
    }

    std::unordered_set<int> getFinal() const {
        return accepting_state;
    }

    std::vector<std::shared_ptr<ElementarySetCopy>> getStates() const {
        return state;
    }

    std::unordered_set<int> getTransition(int src_id, const Word &word) const {
        auto it = transition.find(src_id);
        std::map<Word, std::unordered_set<int>> map;
        std::unordered_set<int> ret;
        if (it != transition.end()) {
            map = it->second;
        } else {
            return ret;
        }
        for (const auto &[key, id_set]: map) {
            if (key.isTrue() || word.equal(key, AP)) {
                ret.insert(id_set.begin(), id_set.end());
            }
        }
        return ret;
    }

    void printStates(bool brief) {
        std::cout << "=== States ===\t" << state.size() << "\n";
        int idx = 0;
        for (const auto &state_: state) {
            std::cout << idx << ": {\n";
            ++idx;
            for (auto formula_id: state_->original->element) {
                std::cout << "\t" << formula_id << ",";
            }
            std::cout << "\n[" << state_->copy_id << "]\n";
            std::cout << "}\n";
        }
        std::cout << "=== === ===\n";

        std::cout << "=== Init States ===\t" << initial_state.size() << "\n";
        for (const auto &state_id: initial_state) {
            std::cout << "{\n";
            for (auto formula_id: state[state_id]->original->element) {
                std::cout << "\t" << formula_id << ",";
            }
            std::cout << "\n[" << state[state_id]->copy_id << "]\n";
            std::cout << "}\n";
        }
        std::cout << "=== === ===\n";

        std::cout << "=== Final States ===\t" << accepting_state.size() << "\n";
        for (const auto state_id: accepting_state) {
            std::cout << "{\n";
            for (auto formula_id: state[state_id]->original->element) {
                std::cout << "\t" << formula_id << ",";
            }
            std::cout << "\n[" << state[state_id]->copy_id << "]\n";
            std::cout << "}\n";
        }
        std::cout << "=== === ===\n";
    }

    void printTransition(bool brief) {
        std::cout << "=== NBA Transition ===\n";
        for (const auto &[key_l1, map_l2]: transition) {
            for (const auto &[key_l2, id_set]: map_l2) {
                std::cout << key_l1 << "\t" << key_l2.toString() << "\n==>";
                for (auto id: id_set) {
                    std::cout << "\t" << id << "\n";
                }
            }
        }
        std::cout << "=== === === ===\n";
    }
};

#endif //LTL_MODEL_CHECKING_AUTOMATA_HPP
