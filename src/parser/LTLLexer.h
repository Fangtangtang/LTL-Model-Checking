
// Generated from LTL.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"




class  LTLLexer : public antlr4::Lexer {
public:
  enum {
    Negation = 1, Conjunction = 2, Disjunction = 3, Implication = 4, Next = 5, 
    Always = 6, Eventually = 7, Until = 8, LeftBracket = 9, RightBracket = 10, 
    Number = 11, AtomicProposition = 12, True = 13, WhiteSpace = 14, LineBreak = 15
  };

  explicit LTLLexer(antlr4::CharStream *input);

  ~LTLLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static all_state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static all_state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

