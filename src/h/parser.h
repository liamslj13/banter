#pragma once

#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <unordered_map>
#include "lex.h"
#include "ast.h"

struct parser;

typedef std::unique_ptr<Expression> (parser::*PrefixParseFn)();

typedef std::unique_ptr<Expression> (parser::*InfixParseFn)(std::unique_ptr<Expression>);

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
    explicit parser(const lex &l);

    std::vector<std::string> Errors() { return errors; }

    std::unique_ptr<Program> parseProgram();

private:
    void nextToken();

    bool expectPeek(const TokenType &tt);

    [[nodiscard]] Precedence peekPrecedence() const;

    [[nodiscard]] Precedence curPrecedence() const;

    std::unique_ptr<Statement> parseStatement();

    std::unique_ptr<DeclareStatement> parseDeclareStatement();

    std::unique_ptr<ReferenceStatement> parseReferenceStatement();

    std::unique_ptr<ReturnStatement> parseReturnStatement();

    std::unique_ptr<ExpressionStatement> parseExpressionStatement();

    std::unique_ptr<BlockStatement> parseBlockStatement();

    std::unique_ptr<Expression> parseExpression(Precedence precedence);

    std::unique_ptr<Expression> parseIdentifier();

    std::unique_ptr<Expression> parseIntegerLiteral();

    std::unique_ptr<Expression> parseStringLiteral();

    std::unique_ptr<Expression> parsePrefixExpression();

    std::unique_ptr<Expression> parseBoolean();

    std::vector<std::unique_ptr<Identifier>> parseFunctionParameters();

    std::unique_ptr<Expression> parseFunctionLiteral();

    std::unique_ptr<Expression> parseArrayLiteral();

    std::unique_ptr<Expression> parseGroupedExpression();

    std::unique_ptr<Expression> parseIfExpression();

    std::unique_ptr<Expression> parseWhileExpression();

    std::vector<std::unique_ptr<Expression>> parseExpressionList();

    std::unique_ptr<Expression> parseCallExpression(std::unique_ptr<Expression> callee);

    std::unique_ptr<Expression> parseIndexExpression(std::unique_ptr<Expression> array);

    std::unique_ptr<Expression> parseInfixExpression(std::unique_ptr<Expression> lhs);

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
