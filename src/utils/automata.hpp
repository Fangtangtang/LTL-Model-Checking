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
    std::unordered_set<StateType, typename StateType::Hash> initialState; // Q_0
    std::unordered_set<StateType, typename StateType::Hash> acceptingState; // F
    std::unordered_set<AtomicProposition, typename AtomicProposition::Hash> alphabet; // Σ

    std::map<
            std::pair<StateType, std::unordered_set<TransitCondition, typename TransitCondition::Hash>>,
            std::unordered_set<StateType, typename StateType::Hash>
    > transition; // δ

public:
    virtual ~Automata() = default;

};

/**
 * GNBA
 */

class ElementarySet {
public:
    struct Hash {
        std::size_t operator()(const ElementarySet &elementarySet) const noexcept {
            // TODO: return std::hash<std::string>{}(ap.name);
        }
    };
};

class GNBA : public Automata<ElementarySet, AtomicProposition> {
private:
    std::shared_ptr<FormulaBase> phi;
    std::vector<std::shared_ptr<FormulaBase>> formula_closure;
public:
    // build GNBA
    explicit GNBA(const std::shared_ptr<FormulaBase> &formula) : phi(formula) {
        // Find Elementary Sets
        // - get closure
        std::map<std::string, std::shared_ptr<FormulaBase>>  closure = formula->getClosure();
        int validCnt = 0;
        for (const auto &sub_formula: closure) {
            sub_formula.second->assignId(validCnt);
            formula_closure.push_back(sub_formula.second);
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
