
// Generated from LTL.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "LTLVisitor.h"


/**
 * This class provides an empty implementation of LTLVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  LTLBaseVisitor : public LTLVisitor {
public:

  virtual std::any visitInput(LTLParser::InputContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSystem_formula(LTLParser::System_formulaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitState_formula(LTLParser::State_formulaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNegationFormula(LTLParser::NegationFormulaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBracketFormula(LTLParser::BracketFormulaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAlwaysFormula(LTLParser::AlwaysFormulaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUntilFormula(LTLParser::UntilFormulaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEventuallyFormula(LTLParser::EventuallyFormulaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAtomicPropositionFormula(LTLParser::AtomicPropositionFormulaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDisjunctionFormula(LTLParser::DisjunctionFormulaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTrueFormula(LTLParser::TrueFormulaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImplicationFormula(LTLParser::ImplicationFormulaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNextFormula(LTLParser::NextFormulaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConjunctionFormula(LTLParser::ConjunctionFormulaContext *ctx) override {
    return visitChildren(ctx);
  }


};

