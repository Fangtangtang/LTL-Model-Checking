#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include "antlr4-runtime.h"

#include "parser/LTLLexer.h"
#include "parser/LTLParser.h"
#include "formula/formula.hpp"
#include "utils/exception.hpp"

std::vector<std::pair<int, std::shared_ptr<FormulaBase>>> parse_formulas(antlr4::ANTLRInputStream inputStream) {
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
    std::vector<std::pair<int, std::shared_ptr<FormulaBase>>> formulas;

    size_t iter = 2;
    for (size_t i = 0; i < system_formula_number; ++i) {
        antlr4::tree::ParseTree *formula_tree = tree->children.at(iter);
        std::cout << formula_tree->getText() << "\n";
        // TODO: parse
        ++iter;
    }

    for (size_t i = 0; i < state_formula_number; ++i) {
        antlr4::tree::ParseTree *formula_tree = tree->children.at(iter);
        std::cout << formula_tree->getText() << "\n";
        int state_id;
        try {
            std::size_t pos;
            state_id = std::stoi(formula_tree->children[0]->getText(), &pos);
        } catch (...) {
            throw InvalidRequestError("The first two input string the state id");
        }
        // TODO: parse
        ++iter;
    }
    // TODO
    return formulas;
}

int main() {
    try {
        std::ifstream file("/mnt/f/repo/LTL-Model-Checking/testcases/LTL-formulas.txt");
        if (!file) {
            std::cerr << "Failed to open file\n";
            return 1;
        }

        antlr4::ANTLRInputStream formulaStream(file);
        std::vector<std::pair<int, std::shared_ptr<FormulaBase>>> formulas = parse_formulas(formulaStream);

        //  TODO


    } catch (const Exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error occurred!" << std::endl;
    }
    return 0;
}
