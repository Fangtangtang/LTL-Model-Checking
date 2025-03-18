
// Generated from LTL.g4 by ANTLR 4.12.0


#include "LTLListener.h"
#include "LTLVisitor.h"

#include "LTLParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct LTLParserStaticData final {
  LTLParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  LTLParserStaticData(const LTLParserStaticData&) = delete;
  LTLParserStaticData(LTLParserStaticData&&) = delete;
  LTLParserStaticData& operator=(const LTLParserStaticData&) = delete;
  LTLParserStaticData& operator=(LTLParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag ltlParserOnceFlag;
LTLParserStaticData *ltlParserStaticData = nullptr;

void ltlParserInitialize() {
  assert(ltlParserStaticData == nullptr);
  auto staticData = std::make_unique<LTLParserStaticData>(
    std::vector<std::string>{
      "input", "system_formula", "state_formula", "formula"
    },
    std::vector<std::string>{
      "", "'!'", "'/\\'", "'\\/'", "'->'", "'X'", "'G'", "'F'", "'U'", "'('", 
      "')'", "", "", "'true'"
    },
    std::vector<std::string>{
      "", "Negation", "Conjunction", "Disjunction", "Implication", "Next", 
      "Always", "Eventually", "Until", "LeftBracket", "RightBracket", "Number", 
      "AtomicProposition", "True", "WhiteSpace", "LineBreak"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,15,64,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,1,0,1,0,1,0,5,0,12,8,0,10,0,
  	12,0,15,9,0,1,0,5,0,18,8,0,10,0,12,0,21,9,0,1,0,1,0,1,1,1,1,1,2,1,2,1,
  	2,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,45,
  	8,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,5,3,59,8,3,10,3,12,
  	3,62,9,3,1,3,0,1,6,4,0,2,4,6,0,0,71,0,8,1,0,0,0,2,24,1,0,0,0,4,26,1,0,
  	0,0,6,44,1,0,0,0,8,9,5,11,0,0,9,13,5,11,0,0,10,12,3,2,1,0,11,10,1,0,0,
  	0,12,15,1,0,0,0,13,11,1,0,0,0,13,14,1,0,0,0,14,19,1,0,0,0,15,13,1,0,0,
  	0,16,18,3,4,2,0,17,16,1,0,0,0,18,21,1,0,0,0,19,17,1,0,0,0,19,20,1,0,0,
  	0,20,22,1,0,0,0,21,19,1,0,0,0,22,23,5,0,0,1,23,1,1,0,0,0,24,25,3,6,3,
  	0,25,3,1,0,0,0,26,27,5,11,0,0,27,28,3,6,3,0,28,5,1,0,0,0,29,30,6,3,-1,
  	0,30,45,5,13,0,0,31,45,5,12,0,0,32,33,5,9,0,0,33,34,3,6,3,0,34,35,5,10,
  	0,0,35,45,1,0,0,0,36,37,5,1,0,0,37,45,3,6,3,5,38,39,5,5,0,0,39,45,3,6,
  	3,4,40,41,5,6,0,0,41,45,3,6,3,3,42,43,5,7,0,0,43,45,3,6,3,2,44,29,1,0,
  	0,0,44,31,1,0,0,0,44,32,1,0,0,0,44,36,1,0,0,0,44,38,1,0,0,0,44,40,1,0,
  	0,0,44,42,1,0,0,0,45,60,1,0,0,0,46,47,10,8,0,0,47,48,5,2,0,0,48,59,3,
  	6,3,9,49,50,10,7,0,0,50,51,5,3,0,0,51,59,3,6,3,8,52,53,10,6,0,0,53,54,
  	5,4,0,0,54,59,3,6,3,6,55,56,10,1,0,0,56,57,5,8,0,0,57,59,3,6,3,2,58,46,
  	1,0,0,0,58,49,1,0,0,0,58,52,1,0,0,0,58,55,1,0,0,0,59,62,1,0,0,0,60,58,
  	1,0,0,0,60,61,1,0,0,0,61,7,1,0,0,0,62,60,1,0,0,0,5,13,19,44,58,60
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  ltlParserStaticData = staticData.release();
}

}

LTLParser::LTLParser(TokenStream *input) : LTLParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

LTLParser::LTLParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  LTLParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *ltlParserStaticData->atn, ltlParserStaticData->decisionToDFA, ltlParserStaticData->sharedContextCache, options);
}

LTLParser::~LTLParser() {
  delete _interpreter;
}

const atn::ATN& LTLParser::getATN() const {
  return *ltlParserStaticData->atn;
}

std::string LTLParser::getGrammarFileName() const {
  return "LTL.g4";
}

const std::vector<std::string>& LTLParser::getRuleNames() const {
  return ltlParserStaticData->ruleNames;
}

const dfa::Vocabulary& LTLParser::getVocabulary() const {
  return ltlParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView LTLParser::getSerializedATN() const {
  return ltlParserStaticData->serializedATN;
}


//----------------- InputContext ------------------------------------------------------------------

LTLParser::InputContext::InputContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> LTLParser::InputContext::Number() {
  return getTokens(LTLParser::Number);
}

tree::TerminalNode* LTLParser::InputContext::Number(size_t i) {
  return getToken(LTLParser::Number, i);
}

tree::TerminalNode* LTLParser::InputContext::EOF() {
  return getToken(LTLParser::EOF, 0);
}

std::vector<LTLParser::System_formulaContext *> LTLParser::InputContext::system_formula() {
  return getRuleContexts<LTLParser::System_formulaContext>();
}

LTLParser::System_formulaContext* LTLParser::InputContext::system_formula(size_t i) {
  return getRuleContext<LTLParser::System_formulaContext>(i);
}

std::vector<LTLParser::State_formulaContext *> LTLParser::InputContext::state_formula() {
  return getRuleContexts<LTLParser::State_formulaContext>();
}

LTLParser::State_formulaContext* LTLParser::InputContext::state_formula(size_t i) {
  return getRuleContext<LTLParser::State_formulaContext>(i);
}


size_t LTLParser::InputContext::getRuleIndex() const {
  return LTLParser::RuleInput;
}

void LTLParser::InputContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInput(this);
}

void LTLParser::InputContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInput(this);
}


std::any LTLParser::InputContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitInput(this);
  else
    return visitor->visitChildren(this);
}

LTLParser::InputContext* LTLParser::input() {
  InputContext *_localctx = _tracker.createInstance<InputContext>(_ctx, getState());
  enterRule(_localctx, 0, LTLParser::RuleInput);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(8);
    match(LTLParser::Number);
    setState(9);
    match(LTLParser::Number);
    setState(13);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 13026) != 0)) {
      setState(10);
      system_formula();
      setState(15);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(19);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LTLParser::Number) {
      setState(16);
      state_formula();
      setState(21);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(22);
    match(LTLParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- System_formulaContext ------------------------------------------------------------------

LTLParser::System_formulaContext::System_formulaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LTLParser::FormulaContext* LTLParser::System_formulaContext::formula() {
  return getRuleContext<LTLParser::FormulaContext>(0);
}


size_t LTLParser::System_formulaContext::getRuleIndex() const {
  return LTLParser::RuleSystem_formula;
}

void LTLParser::System_formulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSystem_formula(this);
}

void LTLParser::System_formulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSystem_formula(this);
}


std::any LTLParser::System_formulaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitSystem_formula(this);
  else
    return visitor->visitChildren(this);
}

LTLParser::System_formulaContext* LTLParser::system_formula() {
  System_formulaContext *_localctx = _tracker.createInstance<System_formulaContext>(_ctx, getState());
  enterRule(_localctx, 2, LTLParser::RuleSystem_formula);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(24);
    formula(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- State_formulaContext ------------------------------------------------------------------

LTLParser::State_formulaContext::State_formulaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LTLParser::State_formulaContext::Number() {
  return getToken(LTLParser::Number, 0);
}

LTLParser::FormulaContext* LTLParser::State_formulaContext::formula() {
  return getRuleContext<LTLParser::FormulaContext>(0);
}


size_t LTLParser::State_formulaContext::getRuleIndex() const {
  return LTLParser::RuleState_formula;
}

void LTLParser::State_formulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterState_formula(this);
}

void LTLParser::State_formulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitState_formula(this);
}


std::any LTLParser::State_formulaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitState_formula(this);
  else
    return visitor->visitChildren(this);
}

LTLParser::State_formulaContext* LTLParser::state_formula() {
  State_formulaContext *_localctx = _tracker.createInstance<State_formulaContext>(_ctx, getState());
  enterRule(_localctx, 4, LTLParser::RuleState_formula);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(26);
    match(LTLParser::Number);
    setState(27);
    formula(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormulaContext ------------------------------------------------------------------

LTLParser::FormulaContext::FormulaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t LTLParser::FormulaContext::getRuleIndex() const {
  return LTLParser::RuleFormula;
}

void LTLParser::FormulaContext::copyFrom(FormulaContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- NegationFormulaContext ------------------------------------------------------------------

tree::TerminalNode* LTLParser::NegationFormulaContext::Negation() {
  return getToken(LTLParser::Negation, 0);
}

LTLParser::FormulaContext* LTLParser::NegationFormulaContext::formula() {
  return getRuleContext<LTLParser::FormulaContext>(0);
}

LTLParser::NegationFormulaContext::NegationFormulaContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLParser::NegationFormulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNegationFormula(this);
}
void LTLParser::NegationFormulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNegationFormula(this);
}

std::any LTLParser::NegationFormulaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitNegationFormula(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BracketFormulaContext ------------------------------------------------------------------

tree::TerminalNode* LTLParser::BracketFormulaContext::LeftBracket() {
  return getToken(LTLParser::LeftBracket, 0);
}

LTLParser::FormulaContext* LTLParser::BracketFormulaContext::formula() {
  return getRuleContext<LTLParser::FormulaContext>(0);
}

tree::TerminalNode* LTLParser::BracketFormulaContext::RightBracket() {
  return getToken(LTLParser::RightBracket, 0);
}

LTLParser::BracketFormulaContext::BracketFormulaContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLParser::BracketFormulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBracketFormula(this);
}
void LTLParser::BracketFormulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBracketFormula(this);
}

std::any LTLParser::BracketFormulaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitBracketFormula(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AlwaysFormulaContext ------------------------------------------------------------------

tree::TerminalNode* LTLParser::AlwaysFormulaContext::Always() {
  return getToken(LTLParser::Always, 0);
}

LTLParser::FormulaContext* LTLParser::AlwaysFormulaContext::formula() {
  return getRuleContext<LTLParser::FormulaContext>(0);
}

LTLParser::AlwaysFormulaContext::AlwaysFormulaContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLParser::AlwaysFormulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAlwaysFormula(this);
}
void LTLParser::AlwaysFormulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAlwaysFormula(this);
}

std::any LTLParser::AlwaysFormulaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitAlwaysFormula(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UntilFormulaContext ------------------------------------------------------------------

std::vector<LTLParser::FormulaContext *> LTLParser::UntilFormulaContext::formula() {
  return getRuleContexts<LTLParser::FormulaContext>();
}

LTLParser::FormulaContext* LTLParser::UntilFormulaContext::formula(size_t i) {
  return getRuleContext<LTLParser::FormulaContext>(i);
}

tree::TerminalNode* LTLParser::UntilFormulaContext::Until() {
  return getToken(LTLParser::Until, 0);
}

LTLParser::UntilFormulaContext::UntilFormulaContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLParser::UntilFormulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUntilFormula(this);
}
void LTLParser::UntilFormulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUntilFormula(this);
}

std::any LTLParser::UntilFormulaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitUntilFormula(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EventuallyFormulaContext ------------------------------------------------------------------

tree::TerminalNode* LTLParser::EventuallyFormulaContext::Eventually() {
  return getToken(LTLParser::Eventually, 0);
}

LTLParser::FormulaContext* LTLParser::EventuallyFormulaContext::formula() {
  return getRuleContext<LTLParser::FormulaContext>(0);
}

LTLParser::EventuallyFormulaContext::EventuallyFormulaContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLParser::EventuallyFormulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEventuallyFormula(this);
}
void LTLParser::EventuallyFormulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEventuallyFormula(this);
}

std::any LTLParser::EventuallyFormulaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitEventuallyFormula(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AtomicPropositionFormulaContext ------------------------------------------------------------------

tree::TerminalNode* LTLParser::AtomicPropositionFormulaContext::AtomicProposition() {
  return getToken(LTLParser::AtomicProposition, 0);
}

LTLParser::AtomicPropositionFormulaContext::AtomicPropositionFormulaContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLParser::AtomicPropositionFormulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtomicPropositionFormula(this);
}
void LTLParser::AtomicPropositionFormulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtomicPropositionFormula(this);
}

std::any LTLParser::AtomicPropositionFormulaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitAtomicPropositionFormula(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DisjunctionFormulaContext ------------------------------------------------------------------

std::vector<LTLParser::FormulaContext *> LTLParser::DisjunctionFormulaContext::formula() {
  return getRuleContexts<LTLParser::FormulaContext>();
}

LTLParser::FormulaContext* LTLParser::DisjunctionFormulaContext::formula(size_t i) {
  return getRuleContext<LTLParser::FormulaContext>(i);
}

tree::TerminalNode* LTLParser::DisjunctionFormulaContext::Disjunction() {
  return getToken(LTLParser::Disjunction, 0);
}

LTLParser::DisjunctionFormulaContext::DisjunctionFormulaContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLParser::DisjunctionFormulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDisjunctionFormula(this);
}
void LTLParser::DisjunctionFormulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDisjunctionFormula(this);
}

std::any LTLParser::DisjunctionFormulaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitDisjunctionFormula(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TrueFormulaContext ------------------------------------------------------------------

tree::TerminalNode* LTLParser::TrueFormulaContext::True() {
  return getToken(LTLParser::True, 0);
}

LTLParser::TrueFormulaContext::TrueFormulaContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLParser::TrueFormulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTrueFormula(this);
}
void LTLParser::TrueFormulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTrueFormula(this);
}

std::any LTLParser::TrueFormulaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitTrueFormula(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ImplicationFormulaContext ------------------------------------------------------------------

std::vector<LTLParser::FormulaContext *> LTLParser::ImplicationFormulaContext::formula() {
  return getRuleContexts<LTLParser::FormulaContext>();
}

LTLParser::FormulaContext* LTLParser::ImplicationFormulaContext::formula(size_t i) {
  return getRuleContext<LTLParser::FormulaContext>(i);
}

tree::TerminalNode* LTLParser::ImplicationFormulaContext::Implication() {
  return getToken(LTLParser::Implication, 0);
}

LTLParser::ImplicationFormulaContext::ImplicationFormulaContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLParser::ImplicationFormulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImplicationFormula(this);
}
void LTLParser::ImplicationFormulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImplicationFormula(this);
}

std::any LTLParser::ImplicationFormulaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitImplicationFormula(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NextFormulaContext ------------------------------------------------------------------

tree::TerminalNode* LTLParser::NextFormulaContext::Next() {
  return getToken(LTLParser::Next, 0);
}

LTLParser::FormulaContext* LTLParser::NextFormulaContext::formula() {
  return getRuleContext<LTLParser::FormulaContext>(0);
}

LTLParser::NextFormulaContext::NextFormulaContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLParser::NextFormulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNextFormula(this);
}
void LTLParser::NextFormulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNextFormula(this);
}

std::any LTLParser::NextFormulaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitNextFormula(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConjunctionFormulaContext ------------------------------------------------------------------

std::vector<LTLParser::FormulaContext *> LTLParser::ConjunctionFormulaContext::formula() {
  return getRuleContexts<LTLParser::FormulaContext>();
}

LTLParser::FormulaContext* LTLParser::ConjunctionFormulaContext::formula(size_t i) {
  return getRuleContext<LTLParser::FormulaContext>(i);
}

tree::TerminalNode* LTLParser::ConjunctionFormulaContext::Conjunction() {
  return getToken(LTLParser::Conjunction, 0);
}

LTLParser::ConjunctionFormulaContext::ConjunctionFormulaContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLParser::ConjunctionFormulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConjunctionFormula(this);
}
void LTLParser::ConjunctionFormulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConjunctionFormula(this);
}

std::any LTLParser::ConjunctionFormulaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitConjunctionFormula(this);
  else
    return visitor->visitChildren(this);
}

LTLParser::FormulaContext* LTLParser::formula() {
   return formula(0);
}

LTLParser::FormulaContext* LTLParser::formula(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  LTLParser::FormulaContext *_localctx = _tracker.createInstance<FormulaContext>(_ctx, parentState);
  LTLParser::FormulaContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 6;
  enterRecursionRule(_localctx, 6, LTLParser::RuleFormula, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(44);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LTLParser::True: {
        _localctx = _tracker.createInstance<TrueFormulaContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(30);
        match(LTLParser::True);
        break;
      }

      case LTLParser::AtomicProposition: {
        _localctx = _tracker.createInstance<AtomicPropositionFormulaContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(31);
        match(LTLParser::AtomicProposition);
        break;
      }

      case LTLParser::LeftBracket: {
        _localctx = _tracker.createInstance<BracketFormulaContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(32);
        match(LTLParser::LeftBracket);
        setState(33);
        formula(0);
        setState(34);
        match(LTLParser::RightBracket);
        break;
      }

      case LTLParser::Negation: {
        _localctx = _tracker.createInstance<NegationFormulaContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(36);
        match(LTLParser::Negation);
        setState(37);
        formula(5);
        break;
      }

      case LTLParser::Next: {
        _localctx = _tracker.createInstance<NextFormulaContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(38);
        match(LTLParser::Next);
        setState(39);
        formula(4);
        break;
      }

      case LTLParser::Always: {
        _localctx = _tracker.createInstance<AlwaysFormulaContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(40);
        match(LTLParser::Always);
        setState(41);
        formula(3);
        break;
      }

      case LTLParser::Eventually: {
        _localctx = _tracker.createInstance<EventuallyFormulaContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(42);
        match(LTLParser::Eventually);
        setState(43);
        formula(2);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(60);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(58);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<ConjunctionFormulaContext>(_tracker.createInstance<FormulaContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleFormula);
          setState(46);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(47);
          match(LTLParser::Conjunction);
          setState(48);
          formula(9);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<DisjunctionFormulaContext>(_tracker.createInstance<FormulaContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleFormula);
          setState(49);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(50);
          match(LTLParser::Disjunction);
          setState(51);
          formula(8);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<ImplicationFormulaContext>(_tracker.createInstance<FormulaContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleFormula);
          setState(52);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(53);
          match(LTLParser::Implication);
          setState(54);
          formula(6);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<UntilFormulaContext>(_tracker.createInstance<FormulaContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleFormula);
          setState(55);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(56);
          match(LTLParser::Until);
          setState(57);
          formula(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(62);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool LTLParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 3: return formulaSempred(antlrcpp::downCast<FormulaContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool LTLParser::formulaSempred(FormulaContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 8);
    case 1: return precpred(_ctx, 7);
    case 2: return precpred(_ctx, 6);
    case 3: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

void LTLParser::initialize() {
  ::antlr4::internal::call_once(ltlParserOnceFlag, ltlParserInitialize);
}
