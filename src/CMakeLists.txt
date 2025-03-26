cmake_minimum_required(VERSION 3.22)
project(LTL_Model_Checking)

set(CMAKE_CXX_STANDARD 17)

# "path/to/install/antlr4/runtime/Cpp"
set(ANTLR4_RUNTIME_PATH "/usr/include/antlr4/runtime/Cpp")

add_executable(LTL_Model_Checking
        main.cpp
        parser/LTLLexer.cpp parser/LTLParser.cpp
        utils/formula.hpp utils/ts.hpp utils/exception.hpp
        utils/automata.hpp
        utils/check.hpp
)

target_include_directories(LTL_Model_Checking PRIVATE ${ANTLR4_RUNTIME_PATH}/usr/local/include/antlr4-runtime)
target_link_directories(LTL_Model_Checking PRIVATE ${ANTLR4_RUNTIME_PATH}/usr/local/lib)
target_link_libraries(LTL_Model_Checking antlr4-runtime)