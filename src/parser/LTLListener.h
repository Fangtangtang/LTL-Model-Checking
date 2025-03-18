
// Generated from LTL.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "LTLParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by LTLParser.
 */
class  LTLListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterInput(LTLParser::InputContext *ctx) = 0;
  virtual void exitInput(LTLParser::InputContext *ctx) = 0;

  virtual void enterSystem_formula(LTLParser::System_formulaContext *ctx) = 0;
  virtual void exitSystem_formula(LTLParser::System_formulaContext *ctx) = 0;

  virtual void enterState_formula(LTLParser::State_formulaContext *ctx) = 0;
  virtual void exitState_formula(LTLParser::State_formulaContext *ctx) = 0;

  virtual void enterNegationFormula(LTLParser::NegationFormulaContext *ctx) = 0;
  virtual void exitNegationFormula(LTLParser::NegationFormulaContext *ctx) = 0;

  virtual void enterBracketFormula(LTLParser::BracketFormulaContext *ctx) = 0;
  virtual void exitBracketFormula(LTLParser::BracketFormulaContext *ctx) = 0;

  virtual void enterAlwaysFormula(LTLParser::AlwaysFormulaContext *ctx) = 0;
  virtual void exitAlwaysFormula(LTLParser::AlwaysFormulaContext *ctx) = 0;

  virtual void enterUntilFormula(LTLParser::UntilFormulaContext *ctx) = 0;
  virtual void exitUntilFormula(LTLParser::UntilFormulaContext *ctx) = 0;

  virtual void enterEventuallyFormula(LTLParser::EventuallyFormulaContext *ctx) = 0;
  virtual void exitEventuallyFormula(LTLParser::EventuallyFormulaContext *ctx) = 0;

  virtual void enterAtomicPropositionFormula(LTLParser::AtomicPropositionFormulaContext *ctx) = 0;
  virtual void exitAtomicPropositionFormula(LTLParser::AtomicPropositionFormulaContext *ctx) = 0;

  virtual void enterDisjunctionFormula(LTLParser::DisjunctionFormulaContext *ctx) = 0;
  virtual void exitDisjunctionFormula(LTLParser::DisjunctionFormulaContext *ctx) = 0;

  virtual void enterTrueFormula(LTLParser::TrueFormulaContext *ctx) = 0;
  virtual void exitTrueFormula(LTLParser::TrueFormulaContext *ctx) = 0;

  virtual void enterImplicationFormula(LTLParser::ImplicationFormulaContext *ctx) = 0;
  virtual void exitImplicationFormula(LTLParser::ImplicationFormulaContext *ctx) = 0;

  virtual void enterNextFormula(LTLParser::NextFormulaContext *ctx) = 0;
  virtual void exitNextFormula(LTLParser::NextFormulaContext *ctx) = 0;

  virtual void enterConjunctionFormula(LTLParser::ConjunctionFormulaContext *ctx) = 0;
  virtual void exitConjunctionFormula(LTLParser::ConjunctionFormulaContext *ctx) = 0;


};

