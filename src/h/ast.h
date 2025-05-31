#pragma once

#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include "../src/h/lex.h"

struct Node {
    virtual ~Node() {
    }

    virtual std::string tokenLiteral() = 0;

    virtual std::string toString() = 0;

    virtual std::string type() = 0;
};

struct Statement : Node {
    virtual void statementNode() = 0;

    std::string tokenLiteral() override = 0;

    std::string toString() override = 0;

    std::string type() override = 0;
};

struct Expression : Node {
    virtual void expressionNode() = 0;

    std::string tokenLiteral() override = 0;

    std::string toString() override = 0;

    std::string type() override = 0;
};

struct Program final : Node {
    std::vector<Statement *> statements;

    ~Program() override {
        for (auto stmt: statements) {
            delete stmt;
        }
    }

    std::string tokenLiteral() override;

    std::string toString() override;

    std::string type() override;
};

struct Identifier : Expression {
    Token tok;
    std::string value;

    std::string tokenLiteral() override { return tok.lit; }
    std::string toString() override { return value; }
    std::string type() override { return "identifier"; }
};

struct BlockStatement : Statement {
    Token tok;
    std::vector<Statement *> statements;

    ~BlockStatement() override {
        for (auto stmt: statements) {
            delete stmt;
        }
    }

    void statementNode() override {
    }

    std::string tokenLiteral() override { return tok.lit; }

    std::string toString() override;

    std::string type() override { return "block_statement"; }
};

struct IntLiteral : Expression {
    Token tok;
    int value;

    std::string tokenLiteral() override { return tok.lit; }
    std::string toString() override { return std::to_string(value); }
    std::string type() override { return "int_literal"; }
};

struct BoolLiteral : Expression {
    Token tok;
    bool value;

    std::string tokenLiteral() override { return tok.lit; }
    std::string toString() override { return value ? "true" : "false"; }
    std::string type() override { return "bool_literal"; }
};

struct StringLiteral : Expression {
    Token tok;
    std::string value;

    std::string tokenLiteral() override { return tok.lit; }
    std::string toString() override { return value; }
    std::string type() override { return "string_literal"; }
};

struct FuncLiteral : Expression {
    Token tok;
    std::vector<Identifier *> params;
    BlockStatement *body;

    ~FuncLiteral() override {
        for (auto param: params) {
            delete param;
        }
    }

    std::string tokenLiteral() override { return tok.lit; }
    std::string toString() override { return "func_literal"; }
    std::string type() override { return "func_literal"; }
};

struct CallExpression : Expression {
    Token tok;
    Expression *callee;
    std::vector<Expression *> arguments;

    ~CallExpression() override {
        for (auto argument: arguments) {
            delete argument;
        }
        delete callee;
    }

    std::string tokenLiteral() override { return tok.lit; }
    std::string type() override { return "call_expression"; }
    std::string toString() override { return "call_expression"; }
};

struct IndexExpression : Expression {
    Token tok;
    Expression *index;
    Expression *array;

    std::string tokenLiteral() override { return tok.lit; }
    std::string toString() override { return "index"; }
    std::string type() override { return "index"; }
};

struct PrefixExpression : Expression {
    Token tok;
    std::string op;
    Expression *rhs;

    std::string tokenLiteral() override { return tok.lit; }

    std::string toString() override;

    std::string type() override { return "prefix_expression"; }
};

struct InfixExpression : Expression {
    Token tok;
    Expression *lhs;
    Expression *rhs;
    std::string op;

    std::string tokenLiteral() override { return tok.lit; }

    std::string toString() override;

    std::string type() override { return "infix_expression"; }
};

struct IfExpression : Expression {
    Token tok;
    Expression *condition;
    BlockStatement *consequence;
    BlockStatement *alternative;

    std::string tokenLiteral() override { return tok.lit; }

    std::string toString() override;

    std::string type() override { return "if_expression"; }
};

struct WhileExpression : Expression {
    Token tok;
    Expression *condition;
    BlockStatement *body;

    std::string tokenLiteral() override { return tok.lit; }

    std::string toString() override;

    std::string type() override { return "while_expression"; }
};

struct DeclareStatement : Statement {
    Token tok;
    Identifier *name;
    Expression *value;

    ~DeclareStatement() override {
        delete value;
    }

    void statementNode() override {
    }

    std::string tokenLiteral() override { return tok.lit; }

    std::string toString() override;

    std::string type() override { return "declare"; }
};

struct ReferenceStatement : Statement {
    Token tok;
    Identifier *name;
    Expression *value;

    ~ReferenceStatement() override {
        delete value;
    }

    void statementNode() override {
    }

    std::string tokenLiteral() override { return tok.lit; }

    std::string toString() override;

    std::string type() override { return "reference_statement"; }
};

struct ReturnStatement : Statement {
    Token tok;
    Expression *returnVal;

    ~ReturnStatement() override {
        delete returnVal;
    }

    void statementNode() override {
    }

    std::string tokenLiteral() override { return tok.lit; }

    std::string toString() override;

    std::string type() override { return "return_statement"; }
};

struct ExpressionStatement : Statement {
    Token tok;
    Expression *expression;

    ~ExpressionStatement() override {
        delete expression;
    }

    void statementNode() override {
    }

    std::string tokenLiteral() override { return tok.lit; }

    std::string toString() override;

    std::string type() override { return "expression_statement"; }
};


#endif //AST_H
