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

std::vector<std::pair<int, std::shared_ptr<FormulaBase>>> parseFormulas(antlr4::ANTLRInputStream inputStream) {
    LTLLexer lexer(&inputStream);
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

    FormulaBuilder formulaBuilder;

    size_t iter = 2;
    for (size_t i = 0; i < system_formula_number; ++i) {
        formulaBuilder.parseSystemFormula(tree->children.at(iter));
        ++iter;
    }
    for (size_t i = 0; i < state_formula_number; ++i) {
        formulaBuilder.parseStateFormula(tree->children.at(iter));
        ++iter;
    }
    formulaBuilder.printFormulas();
    return formulaBuilder.formulas;
}

bool check(const std::pair<int, std::shared_ptr<FormulaBase>> &formula) {

    // TODO
    // Build GNBA

    // Build NBA

    // TS (x) NBA

    // checking algorithm

    return formula.first >= 0;
}

int main() {
    try {
        std::ifstream file("/mnt/f/repo/LTL-Model-Checking/testcases/LTL-formulas.txt");
        if (!file) {
            std::cerr << "Failed to open file\n";
            return 1;
        }

        antlr4::ANTLRInputStream formula_stream(file);
        std::vector<std::pair<int, std::shared_ptr<FormulaBase>>> formulas = parseFormulas(formula_stream);

        // TODO: build TS

        for (const auto &formula: formulas) {
            std::shared_ptr<FormulaBase> negation_formula;
            if (formula.second->negation != nullptr) {
                negation_formula = formula.second->negation;
            } else {
                negation_formula = std::make_shared<NegationFormula>(formula.second);
            }
            GNBA gnba = GNBA(negation_formula);
            // TODO: NBA
            if (check(formula)) {
                std::cout << 1 << "\n";
            } else {
                std::cout << 0 << "\n";
            }
        }
    } catch (const Exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
