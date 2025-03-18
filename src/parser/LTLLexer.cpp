
// Generated from LTL.g4 by ANTLR 4.12.0


#include "LTLLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct LTLLexerStaticData final {
  LTLLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  LTLLexerStaticData(const LTLLexerStaticData&) = delete;
  LTLLexerStaticData(LTLLexerStaticData&&) = delete;
  LTLLexerStaticData& operator=(const LTLLexerStaticData&) = delete;
  LTLLexerStaticData& operator=(LTLLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag ltllexerLexerOnceFlag;
LTLLexerStaticData *ltllexerLexerStaticData = nullptr;

void ltllexerLexerInitialize() {
  assert(ltllexerLexerStaticData == nullptr);
  auto staticData = std::make_unique<LTLLexerStaticData>(
    std::vector<std::string>{
      "Negation", "Conjunction", "Disjunction", "Implication", "Next", "Always", 
      "Eventually", "Until", "LeftBracket", "RightBracket", "Number", "AtomicProposition", 
      "True", "WhiteSpace", "LineBreak"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
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
  	4,0,15,85,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,1,0,1,0,1,1,1,1,1,1,1,2,1,2,1,2,1,3,1,3,1,3,1,4,1,4,1,5,1,5,1,6,
  	1,6,1,7,1,7,1,8,1,8,1,9,1,9,1,10,1,10,5,10,57,8,10,10,10,12,10,60,9,10,
  	1,10,3,10,63,8,10,1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,13,4,13,73,8,13,
  	11,13,12,13,74,1,13,1,13,1,14,1,14,1,14,3,14,82,8,14,1,14,1,14,0,0,15,
  	1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,
  	29,15,1,0,5,1,0,49,57,1,0,48,57,1,0,97,122,2,0,9,9,32,32,2,0,10,10,13,
  	13,88,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,
  	1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,
  	0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,1,31,1,0,0,0,
  	3,33,1,0,0,0,5,36,1,0,0,0,7,39,1,0,0,0,9,42,1,0,0,0,11,44,1,0,0,0,13,
  	46,1,0,0,0,15,48,1,0,0,0,17,50,1,0,0,0,19,52,1,0,0,0,21,62,1,0,0,0,23,
  	64,1,0,0,0,25,66,1,0,0,0,27,72,1,0,0,0,29,81,1,0,0,0,31,32,5,33,0,0,32,
  	2,1,0,0,0,33,34,5,47,0,0,34,35,5,92,0,0,35,4,1,0,0,0,36,37,5,92,0,0,37,
  	38,5,47,0,0,38,6,1,0,0,0,39,40,5,45,0,0,40,41,5,62,0,0,41,8,1,0,0,0,42,
  	43,5,88,0,0,43,10,1,0,0,0,44,45,5,71,0,0,45,12,1,0,0,0,46,47,5,70,0,0,
  	47,14,1,0,0,0,48,49,5,85,0,0,49,16,1,0,0,0,50,51,5,40,0,0,51,18,1,0,0,
  	0,52,53,5,41,0,0,53,20,1,0,0,0,54,58,7,0,0,0,55,57,7,1,0,0,56,55,1,0,
  	0,0,57,60,1,0,0,0,58,56,1,0,0,0,58,59,1,0,0,0,59,63,1,0,0,0,60,58,1,0,
  	0,0,61,63,5,48,0,0,62,54,1,0,0,0,62,61,1,0,0,0,63,22,1,0,0,0,64,65,7,
  	2,0,0,65,24,1,0,0,0,66,67,5,116,0,0,67,68,5,114,0,0,68,69,5,117,0,0,69,
  	70,5,101,0,0,70,26,1,0,0,0,71,73,7,3,0,0,72,71,1,0,0,0,73,74,1,0,0,0,
  	74,72,1,0,0,0,74,75,1,0,0,0,75,76,1,0,0,0,76,77,6,13,0,0,77,28,1,0,0,
  	0,78,79,5,13,0,0,79,82,5,10,0,0,80,82,7,4,0,0,81,78,1,0,0,0,81,80,1,0,
  	0,0,82,83,1,0,0,0,83,84,6,14,0,0,84,30,1,0,0,0,5,0,58,62,74,81,1,6,0,
  	0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  ltllexerLexerStaticData = staticData.release();
}

}

LTLLexer::LTLLexer(CharStream *input) : Lexer(input) {
  LTLLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *ltllexerLexerStaticData->atn, ltllexerLexerStaticData->decisionToDFA, ltllexerLexerStaticData->sharedContextCache);
}

LTLLexer::~LTLLexer() {
  delete _interpreter;
}

std::string LTLLexer::getGrammarFileName() const {
  return "LTL.g4";
}

const std::vector<std::string>& LTLLexer::getRuleNames() const {
  return ltllexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& LTLLexer::getChannelNames() const {
  return ltllexerLexerStaticData->channelNames;
}

const std::vector<std::string>& LTLLexer::getModeNames() const {
  return ltllexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& LTLLexer::getVocabulary() const {
  return ltllexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView LTLLexer::getSerializedATN() const {
  return ltllexerLexerStaticData->serializedATN;
}

const atn::ATN& LTLLexer::getATN() const {
  return *ltllexerLexerStaticData->atn;
}




void LTLLexer::initialize() {
  ::antlr4::internal::call_once(ltllexerLexerOnceFlag, ltllexerLexerInitialize);
}
