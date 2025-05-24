#include <cassert>
#include <iostream>
#include "../src/h/lex.h"

int main() {
    std::string src = "xav + 43444 45678 gagaga";
    lex lexer(src);

    // tokenize the source code
    Token t1 = lexer.nextToken();
    Token t2 = lexer.nextToken();
    Token t3 = lexer.nextToken();
    Token t4 = lexer.nextToken();
    Token t5 = lexer.nextToken();

    // write assertions
    assert(t1.line == 1);
    assert(t1.lit == "xav");
    assert(t1.type == TokenType::IDENT);

    assert(t2.line == 1);
    assert(t2.lit == "+");
    assert(t2.type == TokenType::ADD);

    assert(t3.line == 1);
    assert(t3.lit == "43444");
    assert(t3.type == TokenType::INT);

    assert(t4.line == 1);
    assert(t4.lit == "45678");
    assert(t4.type == TokenType::INT);

    assert(t5.line == 1);
    assert(t5.lit == "gagaga");
    assert(t5.type == TokenType::IDENT);

    std::cout << "All lexer tests pass" << std::endl;
    return 0;
}