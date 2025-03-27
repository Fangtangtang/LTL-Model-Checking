#ifndef LTL_MODEL_CHECKING_FORMULA_HPP
#define LTL_MODEL_CHECKING_FORMULA_HPP

#include <memory>
#include <vector>
#include <unordered_set>
#include <map>
#include "antlr4-runtime.h"
#include "../parser/LTLBaseVisitor.h"
#include "ts.hpp"
#include "exception.hpp"

class FormulaBase : public std::enable_shared_from_this<FormulaBase> {
    int id = -1;

public:
    std::shared_ptr<FormulaBase> negation = nullptr;

public:
    ~FormulaBase() = default;

    std::map<std::string, std::shared_ptr<FormulaBase>> getClosure(bool brief_string);

    void assignId(int validId) {
        if (id >= 0 && validId != id) {
            throw RuntimeError("Assign an invalid id");
        }
        id = validId;
    }

    int getId() const {
        if (id < 0) {
            throw RuntimeError("Use an invalid id");
        }
        return id;
    }

    bool operator==(const FormulaBase &other) const {
        return id == other.id;
    }

    struct Hash {
        size_t operator()(const std::shared_ptr<FormulaBase> &formula) const {
            return std::hash<int>{}(formula->getId());
        }
    };

    [[nodiscard]] virtual std::vector<std::shared_ptr<FormulaBase>> getSubFormula() const = 0;

    [[nodiscard]] virtual std::string toString(bool brief) const noexcept = 0;
};


/**
 *  True | AtomicProposition
 */
class AtomicFormula : public FormulaBase {
private:
    bool isTrue = false;
    AtomicProposition atomicProposition;
public:
    explicit AtomicFormula(AtomicProposition ap, bool isTrueFormula)
            : atomicProposition(std::move(ap)), isTrue(isTrueFormula) {}

    bool isTrueFormula() const {
        return isTrue;
    }

    AtomicProposition getAP() {
        return atomicProposition;
    }

    [[nodiscard]]  std::vector<std::shared_ptr<FormulaBase>> getSubFormula() const override {
        return {};
    }

    [[nodiscard]] std::string toString(bool brief) const noexcept override {
        if (brief) {
            return isTrue ? "True" : atomicProposition.toString();
        }
        return "[\033[33mAtomic \033[0m" + (isTrue ? "True" : atomicProposition.toString()) + "]";
    }
};

class ConjunctionFormula : public FormulaBase {
private:
    std::shared_ptr<FormulaBase> left_formula, right_formula;
public:
    ConjunctionFormula(std::shared_ptr<FormulaBase> left, std::shared_ptr<FormulaBase> right)
            : left_formula(std::move(left)), right_formula(std::move(right)) {}

    [[nodiscard]]  std::vector<std::shared_ptr<FormulaBase>> getSubFormula() const override {
        return {left_formula, right_formula};
    }

    [[nodiscard]] std::string toString(bool brief) const noexcept override {
        if (brief) {
            return "(" + left_formula->toString(brief) + " ∧ " + right_formula->toString(brief) + ")";
        }
        return "[\033[33mConjunction \033[0m" + left_formula->toString(brief) + " ∧ "
               + right_formula->toString(brief) + "]";
    }
};

class NegationFormula : public FormulaBase {
private:
    std::shared_ptr<FormulaBase> sub_formula;
public:
    explicit NegationFormula(std::shared_ptr<FormulaBase> formula)
            : sub_formula(formula) {
        negation = formula;
    }

    [[nodiscard]]  std::vector<std::shared_ptr<FormulaBase>> getSubFormula() const override {
        return {sub_formula};
    }

    [[nodiscard]] std::string toString(bool brief) const noexcept override {
        if (brief) {
            return "(!" + sub_formula->toString(brief) + ")";
        }
        return "[\033[33mNegation \033[0m!" + sub_formula->toString(brief) + "]";
    }
};

class NextFormula : public FormulaBase {
private:
    std::shared_ptr<FormulaBase> sub_formula;
public:
    explicit NextFormula(std::shared_ptr<FormulaBase> formula)
            : sub_formula(std::move(formula)) {}

    [[nodiscard]]  std::vector<std::shared_ptr<FormulaBase>> getSubFormula() const override {
        return {sub_formula};
    }

    [[nodiscard]] std::string toString(bool brief) const noexcept override {
        if (brief) {
            return "(○" + sub_formula->toString(brief) + ")";
        }
        return "[\033[33mNext \033[0m○" + sub_formula->toString(brief) + "]";
    }
};

class UntilFormula : public FormulaBase {
private:
    std::shared_ptr<FormulaBase> left_formula, right_formula;
public:
    UntilFormula(std::shared_ptr<FormulaBase> left, std::shared_ptr<FormulaBase> right)
            : left_formula(std::move(left)), right_formula(std::move(right)) {}

    [[nodiscard]]  std::vector<std::shared_ptr<FormulaBase>> getSubFormula() const override {
        return {left_formula, right_formula};
    }

    [[nodiscard]] std::string toString(bool brief) const noexcept override {
        if (brief) {
            return "(" + left_formula->toString(brief) + " ∪ " + right_formula->toString(brief) + ")";
        }
        return "[\033[33mUntil \033[0m" + left_formula->toString(brief) + " ∪ " + right_formula->toString(brief) + "]";
    }
};

std::map<std::string, std::shared_ptr<FormulaBase>> FormulaBase::getClosure(bool brief_string) {
    std::map<std::string, std::shared_ptr<FormulaBase>> closure;
    std::shared_ptr<FormulaBase> this_formula = shared_from_this(), neg_formula;
    if (this_formula->negation != nullptr) {
        neg_formula = this_formula->negation;
    } else {
        neg_formula = std::static_pointer_cast<FormulaBase>(std::make_shared<NegationFormula>(this_formula));
    }
    closure.emplace(this_formula->toString(brief_string), this_formula);
    closure.emplace(neg_formula->toString(brief_string), neg_formula);
    for (const auto &sub_formula: getSubFormula()) {
        auto sub_formula_closure = sub_formula->getClosure(brief_string);
        closure.insert(sub_formula_closure.begin(), sub_formula_closure.end());
    }
    std::shared_ptr<FormulaBase> this_in_closure = closure.at(this_formula->toString(brief_string)),
            neg_in_closure = closure.at(neg_formula->toString(brief_string));
    this_in_closure->negation = neg_in_closure;
    neg_in_closure->negation = this_in_closure;
    return closure;
}

class FormulaBuilder : public LTLBaseVisitor {
private:
    const TransitionSystem &ts;

public:
    std::vector<std::pair<int, std::shared_ptr<FormulaBase>>> formulas;

public:
    explicit FormulaBuilder(const TransitionSystem &transitionSystem) : ts(transitionSystem) {}

    void parseSystemFormula(antlr4::tree::ParseTree *formula_tree) {
        auto formula_ptr = std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(formula_tree));
        formulas.emplace_back(-1, formula_ptr);
    }

    void parseStateFormula(antlr4::tree::ParseTree *formula_tree) {
        int state_id;
        try {
            std::size_t pos;
            state_id = std::stoi(formula_tree->children[0]->getText(), &pos);
        } catch (...) {
            throw InvalidRequestError("The first two input string the all_state id");
        }
        auto formula_ptr = std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(formula_tree));
        formulas.emplace_back(state_id, formula_ptr);
    }

    void printFormulas(bool brief) {
        for (const auto &formula: formulas) {
            if (formula.first >= 0) {
                std::cout << formula.first << "\t";
            } else {
                std::cout << "TS\t";
            }
            std::cout << formula.second->toString(brief) << "\n";
        }
    }

private:
    std::any visitSystem_formula(LTLParser::System_formulaContext *ctx) override {
        return std::static_pointer_cast<FormulaBase>(
                std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula()))
        );
    }

    std::any visitState_formula(LTLParser::State_formulaContext *ctx) override {
        return std::static_pointer_cast<FormulaBase>(
                std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula()))
        );
    }

    std::any visitNegationFormula(LTLParser::NegationFormulaContext *ctx) override {
        auto sub_formula = std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula()));
        if (sub_formula->negation != nullptr) {
            return sub_formula->negation;
        } else {
            return std::static_pointer_cast<FormulaBase>(std::make_shared<NegationFormula>(sub_formula));
        }
    }

    std::any visitBracketFormula(LTLParser::BracketFormulaContext *ctx) override {
        return std::static_pointer_cast<FormulaBase>(
                std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula()))
        );
    }

    // ▢φ = !◇!φ = !(true U (!φ))
    std::any visitAlwaysFormula(LTLParser::AlwaysFormulaContext *ctx) override {
        auto phi = std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula()));
        auto eventuallyNegPhi = std::make_shared<UntilFormula>(
                std::make_shared<AtomicFormula>(ts.getAtomicProposition("true"), true),
                std::make_shared<NegationFormula>(phi)
        );
        return std::static_pointer_cast<FormulaBase>(std::make_shared<NegationFormula>(eventuallyNegPhi));
    }

    std::any visitUntilFormula(LTLParser::UntilFormulaContext *ctx) override {
        return std::static_pointer_cast<FormulaBase>(
                std::make_shared<UntilFormula>(
                        std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula(0))),
                        std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula(1)))
                )
        );
    }

    std::any visitEventuallyFormula(LTLParser::EventuallyFormulaContext *ctx) override {
        return std::static_pointer_cast<FormulaBase>(
                std::make_shared<UntilFormula>(
                        std::make_shared<AtomicFormula>(ts.getAtomicProposition("true"), true),
                        std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula()))
                )
        );
    }

    std::any visitAtomicPropositionFormula(LTLParser::AtomicPropositionFormulaContext *ctx) override {
        return std::static_pointer_cast<FormulaBase>(
                std::make_shared<AtomicFormula>(ts.getAtomicProposition(ctx->getText()), false)
        );
    }

    // φ1 ∨ φ2 = !(!φ1 ∧ !φ2)
    std::any visitDisjunctionFormula(LTLParser::DisjunctionFormulaContext *ctx) override {
        auto neg_phi_1 = std::make_shared<NegationFormula>(
                std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula(0))));
        auto neg_phi_2 = std::make_shared<NegationFormula>(
                std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula(1))));
        return std::static_pointer_cast<FormulaBase>(
                std::make_shared<NegationFormula>(
                        std::make_shared<ConjunctionFormula>(neg_phi_1, neg_phi_2)
                )
        );
    }

    std::any visitTrueFormula(LTLParser::TrueFormulaContext *ctx) override {
        return std::static_pointer_cast<FormulaBase>(
                std::make_shared<AtomicFormula>(ts.getAtomicProposition("true"), true)
        );
    }

    // φ1 → φ2 = !φ1 ∨ φ2 = !(φ1 ∧ !φ2)
    std::any visitImplicationFormula(LTLParser::ImplicationFormulaContext *ctx) override {
        auto phi_1 = std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula(0)));
        auto neg_phi_2 = std::make_shared<NegationFormula>(
                std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula(1))));
        return std::static_pointer_cast<FormulaBase>(
                std::make_shared<NegationFormula>(std::make_shared<ConjunctionFormula>(phi_1, neg_phi_2))
        );
    }

    std::any visitNextFormula(LTLParser::NextFormulaContext *ctx) override {
        return std::static_pointer_cast<FormulaBase>(
                std::make_shared<NextFormula>(
                        std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula()))
                )
        );
    }

    std::any visitConjunctionFormula(LTLParser::ConjunctionFormulaContext *ctx) override {
        return std::static_pointer_cast<FormulaBase>(
                std::make_shared<ConjunctionFormula>(
                        std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula(0))),
                        std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula(1)))
                )
        );
    }
};

#endif //LTL_MODEL_CHECKING_FORMULA_HPP
