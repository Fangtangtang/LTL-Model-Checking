#ifndef LTL_MODEL_CHECKING_FORMULA_HPP
#define LTL_MODEL_CHECKING_FORMULA_HPP

#include <memory>
#include "../transition_system/ap.hpp"

class FormulaBase {
public:
    virtual ~FormulaBase() = default;
};

/**
 *  True | AtomicProposition
 */
class AtomicFormula : public FormulaBase {
private:
    std::shared_ptr<AtomicProposition> atomicProposition;
public:
    explicit AtomicFormula(std::shared_ptr<AtomicProposition> ap)
            : atomicProposition(std::move(ap)) {}
};

class ConjunctionFormula : public FormulaBase {
private:
    std::shared_ptr<FormulaBase> leftFormula, rightFormula;
public:
    ConjunctionFormula(std::shared_ptr<FormulaBase> left, std::shared_ptr<FormulaBase> right)
            : leftFormula(std::move(left)), rightFormula(std::move(right)) {}
};

class DisjunctionFormula : public FormulaBase {
private:
    std::shared_ptr<FormulaBase> leftFormula, rightFormula;

public:
    DisjunctionFormula(std::shared_ptr<FormulaBase> left, std::shared_ptr<FormulaBase> right)
            : leftFormula(std::move(left)), rightFormula(std::move(right)) {}
};

class ImplicationFormula : public FormulaBase {
private:
    std::shared_ptr<FormulaBase> leftFormula, rightFormula;
public:
    ImplicationFormula(std::shared_ptr<FormulaBase> left, std::shared_ptr<FormulaBase> right)
            : leftFormula(std::move(left)), rightFormula(std::move(right)) {}
};

class NegationFormula : public FormulaBase {
private:
    std::shared_ptr<FormulaBase> subFormula;
public:
    explicit NegationFormula(std::shared_ptr<FormulaBase> formula)
            : subFormula(std::move(formula)) {}
};

class NextFormula : public FormulaBase {
private:
    std::shared_ptr<FormulaBase> subFormula;
public:
    explicit NextFormula(std::shared_ptr<FormulaBase> formula)
            : subFormula(std::move(formula)) {}
};

class AlwaysFormula : public FormulaBase {
private:
    std::shared_ptr<FormulaBase> subFormula;
public:
    explicit AlwaysFormula(std::shared_ptr<FormulaBase> formula)
            : subFormula(std::move(formula)) {}
};

class EventuallyFormula : public FormulaBase {
private:
    std::shared_ptr<FormulaBase> subFormula;
public:
    explicit EventuallyFormula(std::shared_ptr<FormulaBase> formula)
            : subFormula(std::move(formula)) {}
};

class UntilFormula : public FormulaBase {
private:
    std::shared_ptr<FormulaBase> leftFormula, rightFormula;
public:
    UntilFormula(std::shared_ptr<FormulaBase> left, std::shared_ptr<FormulaBase> right)
            : leftFormula(std::move(left)), rightFormula(std::move(right)) {}
};

#endif //LTL_MODEL_CHECKING_FORMULA_HPP
