#pragma once

#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <unordered_map>
#include "lex.h"
#include "ast.h"

struct parser;

typedef Expression * (parser::*PrefixParseFn)();

typedef Expression * (parser::*InfixParseFn)(Expression *);

enum Precedence {
    LOWEST,
    EQUALS,
    LESSGREATER,
    SUM,
    PRODUCT,
    PREFIX,
    CALL,
    INDEX,
};

extern std::unordered_map<TokenType, Precedence> precedence_map;

struct parser {
    void New(lex &l);

    std::vector<std::string> Errors() { return errors; }

    Program *parseProgram();

private:
    void nextToken();

    bool expectPeek(const TokenType &tt);

    Precedence peekPrecedence();

    Precedence curPrecedence();

    Statement *parseStatement();

    DeclareStatement *parseDeclareStatement();

    ReferenceStatement *parseReferenceStatement();

    ReturnStatement *parseReturnStatement();

    ExpressionStatement *parseExpressionStatement();

    BlockStatement *parseBlockStatement();

    Expression *parseExpression(Precedence precedence);

    Expression *parseIdentifier();

    Expression *parseIntegerLiteral();

    Expression *parseStringLiteral();

    Expression *parsePrefixExpression();

    Expression *parseBoolean();

    std::vector<Identifier *> parseFunctionParameters();

    Expression *parseFunctionLiteral();

    Expression *parseArrayLiteral();

    Expression *parseGroupedExpression();

    Expression *parseIfExpression();

    Expression *parseWhileExpression();

    std::vector<Expression *> parseExpressionList();

    Expression *parseCallExpression(Expression *function);

    Expression *parseIndexExpression(Expression *array);

    Expression *parseInfixExpression(Expression *lhs);

    void noPrefixParseFnError(TokenType tt);

    void peekError(const TokenType &tt);

    lex l;
    Token curTok;
    Token peekTok;

    std::unordered_map<TokenType, PrefixParseFn> prefixParseFns;
    std::unordered_map<TokenType, InfixParseFn> infixParseFns;
    std::vector<std::string> errors;
};


#endif //PARSER_H
