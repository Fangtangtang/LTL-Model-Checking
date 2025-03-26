
// Generated from LTL.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"




class  LTLParser : public antlr4::Parser {
public:
  enum {
    Negation = 1, Conjunction = 2, Disjunction = 3, Implication = 4, Next = 5, 
    Always = 6, Eventually = 7, Until = 8, LeftBracket = 9, RightBracket = 10, 
    Number = 11, AtomicProposition = 12, True = 13, WhiteSpace = 14, LineBreak = 15
  };

  enum {
    RuleInput = 0, RuleSystem_formula = 1, RuleState_formula = 2, RuleFormula = 3
  };

  explicit LTLParser(antlr4::TokenStream *input);

  LTLParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~LTLParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class InputContext;
  class System_formulaContext;
  class State_formulaContext;
  class FormulaContext; 

  class  InputContext : public antlr4::ParserRuleContext {
  public:
    InputContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> Number();
    antlr4::tree::TerminalNode* Number(size_t i);
    antlr4::tree::TerminalNode *EOF();
    std::vector<System_formulaContext *> system_formula();
    System_formulaContext* system_formula(size_t i);
    std::vector<State_formulaContext *> state_formula();
    State_formulaContext* state_formula(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InputContext* input();

  class  System_formulaContext : public antlr4::ParserRuleContext {
  public:
    System_formulaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FormulaContext *formula();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  System_formulaContext* system_formula();

  class  State_formulaContext : public antlr4::ParserRuleContext {
  public:
    State_formulaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Number();
    FormulaContext *formula();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  State_formulaContext* state_formula();

  class  FormulaContext : public antlr4::ParserRuleContext {
  public:
    FormulaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    FormulaContext() = default;
    void copyFrom(FormulaContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  NegationFormulaContext : public FormulaContext {
  public:
    NegationFormulaContext(FormulaContext *ctx);

    antlr4::tree::TerminalNode *Negation();
    FormulaContext *formula();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BracketFormulaContext : public FormulaContext {
  public:
    BracketFormulaContext(FormulaContext *ctx);

    antlr4::tree::TerminalNode *LeftBracket();
    FormulaContext *formula();
    antlr4::tree::TerminalNode *RightBracket();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AlwaysFormulaContext : public FormulaContext {
  public:
    AlwaysFormulaContext(FormulaContext *ctx);

    antlr4::tree::TerminalNode *Always();
    FormulaContext *formula();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UntilFormulaContext : public FormulaContext {
  public:
    UntilFormulaContext(FormulaContext *ctx);

    std::vector<FormulaContext *> formula();
    FormulaContext* formula(size_t i);
    antlr4::tree::TerminalNode *Until();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EventuallyFormulaContext : public FormulaContext {
  public:
    EventuallyFormulaContext(FormulaContext *ctx);

    antlr4::tree::TerminalNode *Eventually();
    FormulaContext *formula();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AtomicPropositionFormulaContext : public FormulaContext {
  public:
    AtomicPropositionFormulaContext(FormulaContext *ctx);

    antlr4::tree::TerminalNode *AtomicProposition();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DisjunctionFormulaContext : public FormulaContext {
  public:
    DisjunctionFormulaContext(FormulaContext *ctx);

    std::vector<FormulaContext *> formula();
    FormulaContext* formula(size_t i);
    antlr4::tree::TerminalNode *Disjunction();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TrueFormulaContext : public FormulaContext {
  public:
    TrueFormulaContext(FormulaContext *ctx);

    antlr4::tree::TerminalNode *True();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ImplicationFormulaContext : public FormulaContext {
  public:
    ImplicationFormulaContext(FormulaContext *ctx);

    std::vector<FormulaContext *> formula();
    FormulaContext* formula(size_t i);
    antlr4::tree::TerminalNode *Implication();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NextFormulaContext : public FormulaContext {
  public:
    NextFormulaContext(FormulaContext *ctx);

    antlr4::tree::TerminalNode *Next();
    FormulaContext *formula();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ConjunctionFormulaContext : public FormulaContext {
  public:
    ConjunctionFormulaContext(FormulaContext *ctx);

    std::vector<FormulaContext *> formula();
    FormulaContext* formula(size_t i);
    antlr4::tree::TerminalNode *Conjunction();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  FormulaContext* formula();
  FormulaContext* formula(int precedence);

  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool formulaSempred(FormulaContext *_localctx, size_t predicateIndex);

  // By default the static all_state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static all_state
  // ahead of time.
  static void initialize();

private:
};

