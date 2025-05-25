#include <cassert>
#include <iostream>
#include "../src/h/lex.h"

int main() {
    std::string src = R"(keywords
true false func if else while
expr 4 + 5 = 7;
,!|&||.&&
int str
)";
    lex lexer(src);

    // tokenize the source code
    Token t1 = lexer.nextToken();
    Token t2 = lexer.nextToken();
    Token t3 = lexer.nextToken();
    Token t4 = lexer.nextToken();
    Token t5 = lexer.nextToken();
    Token t6 = lexer.nextToken();
    Token t7 = lexer.nextToken();
    Token t8 = lexer.nextToken();
    Token t9 = lexer.nextToken();
    Token t10 = lexer.nextToken();
    Token t11 = lexer.nextToken();
    Token t12 = lexer.nextToken();
    Token t13 = lexer.nextToken();
    Token t14 = lexer.nextToken();
    Token t15 = lexer.nextToken();
    Token t16 = lexer.nextToken();
    Token t17 = lexer.nextToken();
    Token t18 = lexer.nextToken();
    Token t19 = lexer.nextToken();
    Token t20 = lexer.nextToken();
    Token t21 = lexer.nextToken();
    Token t22 = lexer.nextToken();
    Token t23 = lexer.nextToken();
    Token t24 = lexer.nextToken();

    assert(t1.line == 1);
    assert(t1.lit == "keywords");
    assert(t1.type == TokenType::IDENT);

    assert(t2.line == 2);
    assert(t2.lit == "true");
    assert(t2.type == TokenType::TRUE);

    assert(t3.line == 2);
    assert(t3.lit == "false");
    assert(t3.type == TokenType::FALSE);

    assert(t4.line == 2);
    assert(t4.lit == "func");
    assert(t4.type ==  TokenType::FUNCTION);

    assert(t5.line == 2);
    assert(t5.lit == "if");
    assert(t5.type == TokenType::IF);

    assert(t6.line == 2);
    assert(t6.lit == "else");
    assert(t6.type ==  TokenType::ELSE);

    assert(t7.line == 2);
    assert(t7.lit == "while");
    assert(t7.type == TokenType::WHILE);

    assert(t8.line == 3);
    assert(t8.lit == "expr");
    assert(t8.type == TokenType::IDENT);

    assert(t9.line == 3);
    assert(t9.lit == "4");
    assert(t9.type == TokenType::INT);

    assert(t10.line == 3);
    assert(t10.lit == "+");
    assert(t10.type == TokenType::ADD);

    assert(t11.line == 3);
    assert(t11.lit == "5");
    assert(t11.type == TokenType::INT);

    assert(t12.line == 3);
    assert(t12.lit == "=");
    assert(t12.type == TokenType::ASSIGN);

    assert(t13.line == 3);
    assert(t13.lit == "7");
    assert(t13.type == TokenType::INT);

    assert(t14.line == 3);
    assert(t14.lit == ";");
    assert(t14.type == TokenType::SEMICOLON);

    assert(t15.line == 4);
    assert(t15.lit == ",");
    assert(t15.type == TokenType::COMMA);

    assert(t16.line == 4);
    assert(t16.lit == "!");
    assert(t16.type == TokenType::BANG);

    assert(t17.line == 4);
    assert(t17.lit == "|");
    assert(t17.type == TokenType::BAR);

    assert(t18.line == 4);
    assert(t18.lit == "&");
    assert(t18.type == TokenType::AMPERSAND);

    assert(t19.line == 4);
    assert(t19.lit == "||");
    assert(t19.type == TokenType::OR);

    assert(t20.line == 4);
    assert(t20.lit == ".");
    assert(t20.type == TokenType::DOT);

    assert(t21.line == 4);
    assert(t21.lit == "&&");
    assert(t21.type == TokenType::AND);

    assert(t22.line == 5);
    assert(t22.lit == "int");
    assert(t22.type == TokenType::int_type);

    assert(t23.line == 5);
    assert(t23.lit == "str");
    assert(t23.type == TokenType::str_type);

    assert(t24.line == 6);
    assert(t24.lit == "");
    assert(t24.type == TokenType::EoF);

    std::cout << "All lexer tests pass" << std::endl;
    return 0;
}