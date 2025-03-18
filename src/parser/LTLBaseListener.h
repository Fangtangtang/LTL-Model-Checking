
// Generated from LTL.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "LTLListener.h"


/**
 * This class provides an empty implementation of LTLListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  LTLBaseListener : public LTLListener {
public:

  virtual void enterInput(LTLParser::InputContext * /*ctx*/) override { }
  virtual void exitInput(LTLParser::InputContext * /*ctx*/) override { }

  virtual void enterSystem_formula(LTLParser::System_formulaContext * /*ctx*/) override { }
  virtual void exitSystem_formula(LTLParser::System_formulaContext * /*ctx*/) override { }

  virtual void enterState_formula(LTLParser::State_formulaContext * /*ctx*/) override { }
  virtual void exitState_formula(LTLParser::State_formulaContext * /*ctx*/) override { }

  virtual void enterNegationFormula(LTLParser::NegationFormulaContext * /*ctx*/) override { }
  virtual void exitNegationFormula(LTLParser::NegationFormulaContext * /*ctx*/) override { }

  virtual void enterBracketFormula(LTLParser::BracketFormulaContext * /*ctx*/) override { }
  virtual void exitBracketFormula(LTLParser::BracketFormulaContext * /*ctx*/) override { }

  virtual void enterAlwaysFormula(LTLParser::AlwaysFormulaContext * /*ctx*/) override { }
  virtual void exitAlwaysFormula(LTLParser::AlwaysFormulaContext * /*ctx*/) override { }

  virtual void enterUntilFormula(LTLParser::UntilFormulaContext * /*ctx*/) override { }
  virtual void exitUntilFormula(LTLParser::UntilFormulaContext * /*ctx*/) override { }

  virtual void enterEventuallyFormula(LTLParser::EventuallyFormulaContext * /*ctx*/) override { }
  virtual void exitEventuallyFormula(LTLParser::EventuallyFormulaContext * /*ctx*/) override { }

  virtual void enterAtomicPropositionFormula(LTLParser::AtomicPropositionFormulaContext * /*ctx*/) override { }
  virtual void exitAtomicPropositionFormula(LTLParser::AtomicPropositionFormulaContext * /*ctx*/) override { }

  virtual void enterDisjunctionFormula(LTLParser::DisjunctionFormulaContext * /*ctx*/) override { }
  virtual void exitDisjunctionFormula(LTLParser::DisjunctionFormulaContext * /*ctx*/) override { }

  virtual void enterTrueFormula(LTLParser::TrueFormulaContext * /*ctx*/) override { }
  virtual void exitTrueFormula(LTLParser::TrueFormulaContext * /*ctx*/) override { }

  virtual void enterImplicationFormula(LTLParser::ImplicationFormulaContext * /*ctx*/) override { }
  virtual void exitImplicationFormula(LTLParser::ImplicationFormulaContext * /*ctx*/) override { }

  virtual void enterNextFormula(LTLParser::NextFormulaContext * /*ctx*/) override { }
  virtual void exitNextFormula(LTLParser::NextFormulaContext * /*ctx*/) override { }

  virtual void enterConjunctionFormula(LTLParser::ConjunctionFormulaContext * /*ctx*/) override { }
  virtual void exitConjunctionFormula(LTLParser::ConjunctionFormulaContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

