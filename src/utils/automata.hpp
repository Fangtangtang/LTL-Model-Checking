#ifndef LTL_MODEL_CHECKING_AUTOMATA_HPP
#define LTL_MODEL_CHECKING_AUTOMATA_HPP

#include <memory>
#include <vector>
#include <unordered_set>
#include <map>
#include "formula.hpp"
#include "ts.hpp"

template<typename StateType, typename TransitCondition>
class Automata {
protected:
    std::unordered_set<StateType, typename StateType::Hash> state; // Q
    std::unordered_set<StateType, typename StateType::Hash> initial_state; // Q_0
    std::unordered_set<StateType, typename StateType::Hash> accepting_state; // F
    std::unordered_set<AtomicProposition, typename AtomicProposition::Hash> alphabet; // Σ

    std::map<
            std::pair<StateType, std::unordered_set<TransitCondition, typename TransitCondition::Hash>>,
            std::unordered_set<StateType, typename StateType::Hash>
    > transition; // δ

public:
    virtual ~Automata() = default;

    void addState(StateType state_) {
        state.emplace(state_);
    }

    void addInitState(StateType state_) {
        initial_state.emplace(state_);
    }

    void addAcceptingState(StateType state_) {
        accepting_state.emplace(state_);
    }
};

/**
 * GNBA
 */

// subset of Closure(φ)
class ElementarySet {
public:
    std::unordered_set<int> element; // ids of the formulas

public:
    explicit ElementarySet(std::unordered_set<int> element_) : element(std::move(element_)) {}


    bool operator==(const ElementarySet &other) const noexcept {
        return element == other.element;
    }

    struct Hash {
        std::size_t operator()(const ElementarySet &elementarySet) const noexcept {
            std::size_t hashValue = 0;
            for (int id: elementarySet.element) {
                hashValue ^= std::hash<int>{}(id) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
            }
            return hashValue;
        }
    };
};

class GNBA : public Automata<ElementarySet, AtomicProposition> {
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

    void getClosure() {
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
                }
            } else if (auto until = std::dynamic_pointer_cast<UntilFormula>(sub_formula.second)) {
                until_formula_ids.emplace(validCnt);
            }
            validCnt++;
        }
        // reformat to ensure all sub formulas are in the closure
        for (const auto &sub_formula: closure) {
            reformat(sub_formula.second, stringToId, use_brief_string);
        }
        // ------------------------------------------------------
        std::cout << "===Closure===\n";
        for (const auto &sub_formula: closure) {
            std::cout << sub_formula.second->toString(true) << "\n";
        }
        std::cout << "======\n";
        // ------------------------------------------------------
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
                ElementarySet elementary_set(ids);
                addState(elementary_set);
                // Q_0 = {B ∈ Q | φ ∈ B}
                if (ids.count(phi->getId()) > 0) {
                    addInitState(elementary_set);
                }
                // F
                for (int until_formula_id: until_formula_ids) {
                    std::shared_ptr<FormulaBase> until_formula = formula_closure[until_formula_id];
                    if (ids.count(until_formula_id) == 0 || ids.count(until_formula->getSubFormula()[1]->getId()) > 0) {
                        addAcceptingState(elementary_set);
                    }
                }
            }
        }
    }

public:
    // build GNBA
    explicit GNBA(const std::shared_ptr<FormulaBase> &formula) : phi(formula) {
        // Find Elementary Sets
        getClosure();
        buildStates();
        printStates(true);
    }

    void printStates(bool brief) {
        std::cout << "=== States ===\t" << state.size() << "\n";
        for (const auto &state_: state) {
            std::cout << "{\n";
            for (auto formula_id: state_.element) {
                auto formula = formula_closure[formula_id];
                std::cout << "\t" << formula_id << "\t" << formula->toString(brief) << ",\n";
            }
            std::cout << "}\n";
        }
        std::cout << "=== === ===\n";

        std::cout << "=== Init States ===\t" << initial_state.size() << "\n";
        for (const auto &state_: initial_state) {
            std::cout << "{\n";
            for (auto formula_id: state_.element) {
                auto formula = formula_closure[formula_id];
                std::cout << "\t" << formula_id << "\t" << formula->toString(brief) << ",\n";
            }
            std::cout << "}\n";
        }
        std::cout << "=== === ===\n";

        std::cout << "=== Final States ===\t" << accepting_state.size() << "\n";
        for (const auto &state_: accepting_state) {
            std::cout << "{\n";
            for (auto formula_id: state_.element) {
                auto formula = formula_closure[formula_id];
                std::cout << "\t" << formula_id << "\t" << formula->toString(brief) << ",\n";
            }
            std::cout << "}\n";
        }
        std::cout << "=== === ===\n";
    }
};

/**
 * NBA
 */
// TODO
//class NBA : public Automata {
//public:
//    // build NBA from GNBA
//    explicit NBA(const std::shared_ptr<GNBA> &automata) {
//
//    }
//};

#endif //LTL_MODEL_CHECKING_AUTOMATA_HPP
