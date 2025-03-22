#ifndef LTL_MODEL_CHECKING_FORMULA_HPP
#define LTL_MODEL_CHECKING_FORMULA_HPP

#include <memory>
#include <vector>
#include <unordered_set>
#include "antlr4-runtime.h"
#include "../parser/LTLBaseVisitor.h"
#include "ts.hpp"
#include "exception.hpp"

struct FormulaHash;
struct FormulaEqual;

class FormulaBase : public std::enable_shared_from_this<FormulaBase> {
public:
    ~FormulaBase() = default;

    std::unordered_set<std::shared_ptr<FormulaBase>, FormulaHash, FormulaEqual> getClosure();

    [[nodiscard]] virtual std::vector<std::shared_ptr<FormulaBase>> getSubFormula() const = 0;

    [[nodiscard]] virtual std::string toString() const noexcept = 0;
};

struct FormulaHash {
    size_t operator()(const std::shared_ptr<FormulaBase> &formula) const {
        return std::hash<std::string>()(formula->toString());
    }
};

struct FormulaEqual {
    bool operator()(const std::shared_ptr<FormulaBase> &lhs, const std::shared_ptr<FormulaBase> &rhs) const {
        if (!lhs || !rhs) {
            return false;
        }
        return lhs->toString() == rhs->toString();
    }
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

    [[nodiscard]]  std::vector<std::shared_ptr<FormulaBase>> getSubFormula() const override {
        return {};
    }

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

    [[nodiscard]]  std::vector<std::shared_ptr<FormulaBase>> getSubFormula() const override {
        return {leftFormula, rightFormula};
    }

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

    [[nodiscard]]  std::vector<std::shared_ptr<FormulaBase>> getSubFormula() const override {
        return {leftFormula, rightFormula};
    }

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

    [[nodiscard]]  std::vector<std::shared_ptr<FormulaBase>> getSubFormula() const override {
        return {leftFormula, rightFormula};
    }

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

    [[nodiscard]]  std::vector<std::shared_ptr<FormulaBase>> getSubFormula() const override {
        return {subFormula};
    }

    std::shared_ptr<FormulaBase> getNegation() {
        return subFormula;
    }

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

    [[nodiscard]]  std::vector<std::shared_ptr<FormulaBase>> getSubFormula() const override {
        return {subFormula};
    }

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

    [[nodiscard]]  std::vector<std::shared_ptr<FormulaBase>> getSubFormula() const override {
        return {subFormula};
    }

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

    [[nodiscard]]  std::vector<std::shared_ptr<FormulaBase>> getSubFormula() const override {
        return {subFormula};
    }

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

    [[nodiscard]]  std::vector<std::shared_ptr<FormulaBase>> getSubFormula() const override {
        return {leftFormula, rightFormula};
    }

    [[nodiscard]] std::string toString() const noexcept override {
        return "[\033[33mUntil \033[0m" + leftFormula->toString() + " ∪ " + rightFormula->toString() + "]";
    }
};

std::unordered_set<std::shared_ptr<FormulaBase>, FormulaHash, FormulaEqual> FormulaBase::getClosure() {
    std::unordered_set<std::shared_ptr<FormulaBase>, FormulaHash, FormulaEqual> closure;
    std::shared_ptr<FormulaBase> thisFormula = shared_from_this(), negFormula;
    if (auto ptr = std::dynamic_pointer_cast<NegationFormula>(thisFormula)) {
        negFormula = ptr->getNegation();
    } else {
        negFormula = std::static_pointer_cast<FormulaBase>(std::make_shared<NegationFormula>(thisFormula));
    }
    closure.insert(thisFormula);
    closure.insert(negFormula);
    for (const auto &subFormula: getSubFormula()) {
        auto subFormulaClosure = subFormula->getClosure();
        closure.insert(subFormulaClosure.begin(), subFormulaClosure.end());
    }
    return closure;
}

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
            } else {
                std::cout << "TS\t";
            }
            std::cout << formula.second->toString() << "\n";
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
        auto subFormula = std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula()));
        if (auto negPtr = std::dynamic_pointer_cast<NegationFormula>(subFormula)) {
            return negPtr->getNegation();
        } else {
            return std::static_pointer_cast<FormulaBase>(std::make_shared<NegationFormula>(subFormula));
        }
    }

    std::any visitBracketFormula(LTLParser::BracketFormulaContext *ctx) override {
        return std::static_pointer_cast<FormulaBase>(
                std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula()))
        );
    }

    std::any visitAlwaysFormula(LTLParser::AlwaysFormulaContext *ctx) override {
        return std::static_pointer_cast<FormulaBase>(
                std::make_shared<AlwaysFormula>(
                        std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula()))
                )
        );
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
                std::make_shared<EventuallyFormula>(
                        std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula()))
                )
        );
    }

    std::any visitAtomicPropositionFormula(LTLParser::AtomicPropositionFormulaContext *ctx) override {
        return std::static_pointer_cast<FormulaBase>(
                std::make_shared<AtomicFormula>(
                        std::make_shared<AtomicProposition>(ctx->getText()), false
                )
        );
    }

    std::any visitDisjunctionFormula(LTLParser::DisjunctionFormulaContext *ctx) override {
        return std::static_pointer_cast<FormulaBase>(
                std::make_shared<DisjunctionFormula>(
                        std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula(0))),
                        std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula(1)))
                )
        );
    }

    std::any visitTrueFormula(LTLParser::TrueFormulaContext *ctx) override {
        return std::static_pointer_cast<FormulaBase>(
                std::make_shared<AtomicFormula>(nullptr, true)
        );
    }

    std::any visitImplicationFormula(LTLParser::ImplicationFormulaContext *ctx) override {
        return std::static_pointer_cast<FormulaBase>(
                std::make_shared<ImplicationFormula>(
                        std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula(0))),
                        std::any_cast<std::shared_ptr<FormulaBase>>(this->visit(ctx->formula(1)))
                )
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
