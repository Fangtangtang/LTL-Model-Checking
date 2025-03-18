
// Generated from LTL.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "LTLParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by LTLParser.
 */
class  LTLVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by LTLParser.
   */
    virtual std::any visitInput(LTLParser::InputContext *context) = 0;

    virtual std::any visitSystem_formula(LTLParser::System_formulaContext *context) = 0;

    virtual std::any visitState_formula(LTLParser::State_formulaContext *context) = 0;

    virtual std::any visitNegationFormula(LTLParser::NegationFormulaContext *context) = 0;

    virtual std::any visitBracketFormula(LTLParser::BracketFormulaContext *context) = 0;

    virtual std::any visitAlwaysFormula(LTLParser::AlwaysFormulaContext *context) = 0;

    virtual std::any visitUntilFormula(LTLParser::UntilFormulaContext *context) = 0;

    virtual std::any visitEventuallyFormula(LTLParser::EventuallyFormulaContext *context) = 0;

    virtual std::any visitAtomicPropositionFormula(LTLParser::AtomicPropositionFormulaContext *context) = 0;

    virtual std::any visitDisjunctionFormula(LTLParser::DisjunctionFormulaContext *context) = 0;

    virtual std::any visitTrueFormula(LTLParser::TrueFormulaContext *context) = 0;

    virtual std::any visitImplicationFormula(LTLParser::ImplicationFormulaContext *context) = 0;

    virtual std::any visitNextFormula(LTLParser::NextFormulaContext *context) = 0;

    virtual std::any visitConjunctionFormula(LTLParser::ConjunctionFormulaContext *context) = 0;


};

