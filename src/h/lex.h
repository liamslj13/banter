#pragma once

#ifndef LEX_H
#define LEX_H

#include <iostream>
#include <unordered_map>

// define a token type struct
enum struct TokenType {
    // types
    IDENT,
    INT,
    STRING,
    DECLARE,

    // basic operator
    ASSIGN,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,

    // braces, brackets etc
    LPAREN,
    RPAREN,
    LBRACKET,
    RBRACKET,
    LBRACE,
    RBRACE,

    SEMICOLON,
    COLON,
    COMMA,
    BANG,
    BAR,
    AMPERSAND,
    DOT,

    // boolean operators
    GT,
    LT,
    EQ,
    LTE,
    GTE,
    NEQ,
    AND,
    OR,

    // keywords
    FUNCTION,
    IF,
    ELSE,
    WHILE,
    RETURN,
    BREAK,
    TRUE,
    FALSE,
    VAR_DECL,

    // keyword literals
    int_type,
    str_type,
    bool_type,
    arr_type,

    ILLEGAL,
    EoF,
};

struct Token {
    TokenType type;
    std::string lit;
    int line;

    Token();
    Token(TokenType type, std::string lit, int line);
    [[nodiscard]] std::string toString() const;
};

class lex {
    std::string input;
    char ch;
    int pos, readPos, line{}, linePos;
    std::unordered_map<std::string, TokenType> keywords;

public:

    static std::string tokenTypeToString(const TokenType type);
    explicit lex(std::string &input);
    void readChar();
    void skipWhitespace();

    void printError(const Token &t) const;
    [[nodiscard]] Token nextToken();
    [[nodiscard]] char peekChar() const;

    static Token newToken(TokenType type, const std::string &lit, int line);
    std::string readIdent();
    std::string readInt();
    std::string readString();
};

#endif //LEX_H