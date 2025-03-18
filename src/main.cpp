#include <iostream>
#include <fstream>
#include "antlr4-runtime.h"
#include "parser/LTLLexer.h"
#include "parser/LTLParser.h"

int main() {
    std::ifstream file("/mnt/f/repo/LTL-Model-Checking/testcases/LTL-formulas.txt");
    if (!file) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    antlr4::ANTLRInputStream inputStream(file);
    LTLLexer lexer(&inputStream);
    antlr4::CommonTokenStream tokens(&lexer);
    LTLParser parser(&tokens);

    antlr4::tree::ParseTree *tree = parser.formula();
    std::cout << "Parse Tree: " << tree->toStringTree(&parser) << std::endl;

    //  TODO
//    LTLVisitor visitor;
//    visitor.visit(tree);

    return 0;
}
