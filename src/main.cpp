#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include "antlr4-runtime.h"

#include "parser/LTLLexer.h"
#include "parser/LTLParser.h"
#include "utils/formula.hpp"
#include "utils/exception.hpp"
#include "utils/automata.hpp"
#include "utils/ts.hpp"
#include "utils/check.hpp"

std::vector<std::pair<int, std::shared_ptr<FormulaBase>>> parseFormulas(
        antlr4::ANTLRInputStream stream, const TransitionSystem &ts
) {
    LTLLexer lexer(&stream);
    antlr4::CommonTokenStream tokens(&lexer);
    LTLParser parser(&tokens);

    antlr4::tree::ParseTree *tree = parser.input();

    int system_formula_number, state_formula_number;
    try {
        std::size_t pos;
        system_formula_number = std::stoi(tree->children[0]->getText(), &pos);
        state_formula_number = std::stoi(tree->children[1]->getText(), &pos);
    } catch (...) {
        throw InvalidRequestError("The first two input string should be 2 integers indicating the number of formulas.");
    }
    std::cout << system_formula_number << "\n";
    std::cout << state_formula_number << "\n";

    // validity check: parsed into 2 int, some formulas, <EOF>
    if (tree->children.size() != system_formula_number + state_formula_number + 3) {
        throw InvalidRequestError("The number of formulas should be consistent with the request number");
    }

    FormulaBuilder formulaBuilder(ts);

    size_t iter = 2;
    for (size_t i = 0; i < system_formula_number; ++i) {
        formulaBuilder.parseSystemFormula(tree->children.at(iter));
        ++iter;
    }
    for (size_t i = 0; i < state_formula_number; ++i) {
        formulaBuilder.parseStateFormula(tree->children.at(iter));
        ++iter;
    }
    formulaBuilder.printFormulas(true);
    return formulaBuilder.formulas;
}

bool check(const std::pair<int, std::shared_ptr<FormulaBase>> &formula, const TransitionSystem &ts) {
    std::shared_ptr<FormulaBase> negation_formula;
    if (formula.second->negation != nullptr) {
        negation_formula = formula.second->negation;
    } else {
        negation_formula = std::make_shared<NegationFormula>(formula.second);
    }
    // Build GNBA
    GNBA gnba(negation_formula);
    // Build NBA
    NBA nba(gnba);
    nba.printStates(true);
    nba.printTransition(true);
    // TS (x) NBA
    TransitionSystemProductNBA checked_ts(ts, nba, formula.first);
    // checking algorithm
    return checked_ts.check();
}

int main() {
    try {
        TransitionSystem transition_system("/mnt/f/repo/LTL-Model-Checking/testcases/TS.txt");

        std::ifstream formula_file("/mnt/f/repo/LTL-Model-Checking/testcases/LTL-formulas.txt");
        if (!formula_file) {
            std::cerr << "Failed to open formula_file\n";
            return 1;
        }

        antlr4::ANTLRInputStream formula_stream(formula_file);
        std::vector<std::pair<int, std::shared_ptr<FormulaBase>>> formulas = parseFormulas(
                formula_stream, transition_system);

        std::vector<int> ans;
        for (const auto &formula: formulas) {
            if (check(formula, transition_system)) {
                std::cout << 1 << "\n";
                ans.push_back(1);
            } else {
                std::cout << 0 << "\n";
                ans.push_back(0);
            }
        }

        std::cout << "\n\n";
        for (int a: ans) {
            std::cout << a << "\t";
        }
    } catch (const Exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
