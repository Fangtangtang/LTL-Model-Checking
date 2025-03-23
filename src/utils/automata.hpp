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
private:
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
    void getClosure() {
        std::map<std::string, std::shared_ptr<FormulaBase>> closure = phi->getClosure();
        int validCnt = 0;
        for (const auto &sub_formula: closure) {
            sub_formula.second->assignId(validCnt);
            formula_closure.push_back(sub_formula.second);
            if (auto atomic = std::dynamic_pointer_cast<AtomicFormula>(sub_formula.second)) {
                if (atomic->isTrueFormula()) {
                    true_formula_id = validCnt;
                }
            } else if (auto until = std::dynamic_pointer_cast<UntilFormula>(sub_formula.second)) {
                until_formula_ids.emplace(validCnt);
            }
            validCnt++;
        }
        // ------------------------------------------------------
        std::cout << "===Closure===\n";
        for (const auto &sub_formula: closure) {
            std::cout << sub_formula.second->toString() << "\n";
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
            if (ids.count(formula->getId()) + ids.count(formula->negation->getId()) > 1) {
                return false;
            }
            // ψ1 ∧ ψ2 ∈ B ⇔ ψ1 ∈ B and ψ2 ∈ B, none or all
            if (auto ptr = std::dynamic_pointer_cast<ConjunctionFormula>(formula)) {
                auto cnt = ids.count(formula->getId());
                for (const auto &sub_formula: ptr->getSubFormula()) {
                    cnt += ids.count(sub_formula->getId());
                }
                if (cnt != 3 && cnt != 0) {
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

    void buildElementarySet() {
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
        buildElementarySet();

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
