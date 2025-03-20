grammar LTL;

input:
    Number Number
    system_formula* state_formula*
    EOF
    ;

system_formula:
    formula;

state_formula:
    Number formula
    ;

formula:
    True                                #TrueFormula
    | AtomicProposition                 #AtomicPropositionFormula
    | LeftBracket formula RightBracket  #BracketFormula
    | formula Conjunction formula       #ConjunctionFormula
    | formula Disjunction formula       #DisjunctionFormula
    | <assoc=right> formula Implication formula     #ImplicationFormula
    | Negation formula                  #NegationFormula
    | Next formula                      #NextFormula
    | Always formula                    #AlwaysFormula
    | Eventually formula                #EventuallyFormula
    | formula Until formula             #UntilFormula
    ;

/*
   LEXER
   =====================================================================================================================
 */
Negation: '!';
Conjunction: '/\\';
Disjunction: '\\/';
Implication: '->';
Next: 'X';
Always: 'G';
Eventually: 'F';
Until: 'U';

LeftBracket: '(';
RightBracket: ')';

Number:
    [1-9] [0-9]*
    | '0'
    ;

AtomicProposition: [a-z];
True: 'true';

WhiteSpace:
    [ \t]+ -> skip;

LineBreak:
    (
     '\r\n'
    | '\n'
    | '\r'
    ) -> skip
    ;