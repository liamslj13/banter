cmake_minimum_required(VERSION 3.30)
project(banter)

set(CMAKE_CXX_STANDARD 26)

enable_testing()

add_executable(banter main.cpp
        src/lex.cpp
        src/h/lex.h
        unit_tests/test_lexer.cpp
        src/ast.cpp
        src/h/ast.h
        src/h/parser.h
        src/parser.cpp
        src/codegen/banterEnv.h
        src/codegen/codegen.cpp
        unit_tests/test_ast.cpp
        unit_tests/test_parser.cpp)

find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(LLVM_LIBS core support)
target_link_libraries(banter ${LLVM_LIBS})



