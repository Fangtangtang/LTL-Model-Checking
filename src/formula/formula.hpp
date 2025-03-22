#ifndef LTL_MODEL_CHECKING_FORMULA_HPP
#define LTL_MODEL_CHECKING_FORMULA_HPP

#include <memory>
#include <vector>
#include "antlr4-runtime.h"
#include "../parser/LTLBaseVisitor.h"
#include "../transition_system/ap.hpp"
#include "../utils/exception.hpp"

class FormulaBase {
public:
    ~FormulaBase() = default;

    [[nodiscard]] virtual std::string toString() const noexcept = 0;
};

/**
 *  True | AtomicProposition
 */
class AtomicFormula : public FormulaBase {
private:
    bool isTrue = false;
    std::shared_ptr<AtomicProposition> atomicProposition;
public:
    explicit AtomicFormula(std::shared_ptr<AtomicProposition> ap, bool isTrueFormula)
            : atomicProposition(std::move(ap)), isTrue(isTrueFormula) {}

    [[nodiscard]] std::string toString() const noexcept override {
        return "[\033[33mAtomic \033[0m" + (isTrue ? "True" : atomicProposition->toString()) + "]";
    }
};

class ConjunctionFormula : public FormulaBase {
private:
    std::shared_ptr<FormulaBase> leftFormula, rightFormula;
public:
    ConjunctionFormula(std::shared_ptr<FormulaBase> left, std::shared_ptr<FormulaBase> right)
            : leftFormula(std::move(left)), rightFormula(std::move(right)) {}

    [[nodiscard]] std::string toString() const noexcept override {
        return "[\033[33mConjunction \033[0m" + leftFormula->toString() + " ∧ " + rightFormula->toString() + "]";
    }
};

class DisjunctionFormula : public FormulaBase {
private:
    std::shared_ptr<FormulaBase> leftFormula, rightFormula;

public:
    DisjunctionFormula(std::shared_ptr<FormulaBase> left, std::shared_ptr<FormulaBase> right)
            : leftFormula(std::move(left)), rightFormula(std::move(right)) {}

    [[nodiscard]] std::string toString() const noexcept override {
        return "[\033[33mDisjunction \033[0m" + leftFormula->toString() + " ∨ " + rightFormula->toString() + "]";
    }
};

class ImplicationFormula : public FormulaBase {
private:
    std::shared_ptr<FormulaBase> leftFormula, rightFormula;
public:
    ImplicationFormula(std::shared_ptr<FormulaBase> left, std::shared_ptr<FormulaBase> right)
            : leftFormula(std::move(left)), rightFormula(std::move(right)) {}

    [[nodiscard]] std::string toString() const noexcept override {
        return "[\033[33mImplication \033[0m" + leftFormula->toString() + " → " + rightFormula->toString() + "]";
    }
};

class NegationFormula : public FormulaBase {
private:
    std::shared_ptr<FormulaBase> subFormula;
public:
    explicit NegationFormula(std::shared_ptr<FormulaBase> formula)
            : subFormula(std::move(formula)) {}

    [[nodiscard]] std::string toString() const noexcept override {
        return "[\033[33mNegation \033[0m!" + subFormula->toString() + "]";
    }
};

class NextFormula : public FormulaBase {
private:
    std::shared_ptr<FormulaBase> subFormula;
public:
    explicit NextFormula(std::shared_ptr<FormulaBase> formula)
            : subFormula(std::move(formula)) {}

    [[nodiscard]] std::string toString() const noexcept override {
        return "[\033[33mNext \033[0m○" + subFormula->toString() + "]";
    }
};

class AlwaysFormula : public FormulaBase {
private:
    std::shared_ptr<FormulaBase> subFormula;
public:
    explicit AlwaysFormula(std::shared_ptr<FormulaBase> formula)
            : subFormula(std::move(formula)) {}

    [[nodiscard]] std::string toString() const noexcept override {
        return "[\033[33mAlways \033[0m▢" + subFormula->toString() + "]";
    }
};

class EventuallyFormula : public FormulaBase {
private:
    std::shared_ptr<FormulaBase> subFormula;
public:
    explicit EventuallyFormula(std::shared_ptr<FormulaBase> formula)
            : subFormula(std::move(formula)) {}

    [[nodiscard]] std::string toString() const noexcept override {
        return "[\033[33mEventually \033[0m◇" + subFormula->toString() + "]";
    }
};

class UntilFormula : public FormulaBase {
private:
    std::shared_ptr<FormulaBase> leftFormula, rightFormula;
public:
    UntilFormula(std::shared_ptr<FormulaBase> left, std::shared_ptr<FormulaBase> right)
            : leftFormula(std::move(left)), rightFormula(std::move(right)) {}

    [[nodiscard]] std::string toString() const noexcept override {
        return "[\033[33mUntil \033[0m" + leftFormula->toString() + " ∪ " + rightFormula->toString() + "]";
    }
};

class FormulaBuilder : public LTLBaseVisitor {
public:
    std::vector<std::pair<int, std::shared_ptr<FormulaBase>>> formulas;
public:
    void parseSystem_formula(antlr4::tree::ParseTree *formula_tree) {
        std::cout << formula_tree->getText() << "\n";
        auto formulaPtr = std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(formula_tree));
        formulas.emplace_back(-1, formulaPtr);
    }

    void parseState_formula(antlr4::tree::ParseTree *formula_tree) {
        int state_id;
        try {
            std::size_t pos;
            state_id = std::stoi(formula_tree->children[0]->getText(), &pos);
        } catch (...) {
            throw InvalidRequestError("The first two input string the state id");
        }
        std::cout << formula_tree->getText() << "\n";
        auto formulaPtr = std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(formula_tree));
        formulas.emplace_back(state_id, formulaPtr);
    }

    void printFormulas() {
        for (const auto &formula: formulas) {
            if (formula.first >= 0) {
                std::cout << formula.first << "\t";
            }
            std::cout << formula.second->toString() << "\n";
        }
    }

private:
    std::any visitNegationFormula(LTLParser::NegationFormulaContext *ctx) override {
        return std::make_shared<NegationFormula>(
                std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula())));
    }

    std::any visitBracketFormula(LTLParser::BracketFormulaContext *ctx) override {
        return this->visit(ctx->formula());
    }

    std::any visitAlwaysFormula(LTLParser::AlwaysFormulaContext *ctx) override {
        return std::make_shared<AlwaysFormula>(
                std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula())));

    }

    std::any visitUntilFormula(LTLParser::UntilFormulaContext *ctx) override {
        return std::make_shared<UntilFormula>(
                std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula(0))),
                std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula(1)))
        );
    }

    std::any visitEventuallyFormula(LTLParser::EventuallyFormulaContext *ctx) override {
        return std::make_shared<EventuallyFormula>(
                std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula())));
    }

    std::any visitAtomicPropositionFormula(LTLParser::AtomicPropositionFormulaContext *ctx) override {
        return std::make_shared<AtomicFormula>(
                std::any_cast<std::shared_ptr<AtomicProposition>>(ctx->getText()), false
        );
    }

    std::any visitDisjunctionFormula(LTLParser::DisjunctionFormulaContext *ctx) override {
        return std::make_shared<DisjunctionFormula>(
                std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula(0))),
                std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula(1)))
        );
    }

    std::any visitTrueFormula(LTLParser::TrueFormulaContext *ctx) override {
        return std::make_shared<AtomicFormula>(nullptr, true);
    }

    std::any visitImplicationFormula(LTLParser::ImplicationFormulaContext *ctx) override {
        return std::make_shared<ImplicationFormula>(
                std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula(0))),
                std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula(1)))
        );
    }

    std::any visitNextFormula(LTLParser::NextFormulaContext *ctx) override {
        return std::make_shared<NextFormula>(
                std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula())));
    }

    std::any visitConjunctionFormula(LTLParser::ConjunctionFormulaContext *ctx) override {
        return std::make_shared<ConjunctionFormula>(
                std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula(0))),
                std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula(1)))
        );
    }
};

#endif //LTL_MODEL_CHECKING_FORMULA_HPP
