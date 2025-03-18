cmake_minimum_required(VERSION 3.22)
project(LTL_Model_Checking)

set(CMAKE_CXX_STANDARD 17)

add_executable(LTL_Model_Checking main.cpp parser/LTLLexer.cpp parser/LTLParser.cpp)

target_include_directories(LTL_Model_Checking PRIVATE /usr/include/antlr4/runtime/Cpp/usr/local/include/antlr4-runtime)
target_link_directories(LTL_Model_Checking PRIVATE /usr/include/antlr4/runtime/Cpp/usr/local/lib)
target_link_libraries(LTL_Model_Checking antlr4-runtime)