#pragma once

#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include "../h/lex.h"

struct Node {
    virtual ~Node() = default;

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
    std::vector<std::unique_ptr<Statement>> statements;

    ~Program() override = default;

    std::string tokenLiteral() override;

    std::string toString() override;

    std::string type() override { return "program"; }
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
    std::vector<std::unique_ptr<Statement>> statements;

    ~BlockStatement() override = default;

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
    bool value = false;

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
    std::vector<std::unique_ptr<Identifier>> params;
    std::unique_ptr<BlockStatement> body;

    ~FuncLiteral() override = default;

    std::string tokenLiteral() override { return tok.lit; }
    std::string toString() override;
    std::string type() override { return "func_literal"; }
};

struct ArrayLiteral : Expression {
    Token tok;
    std::vector<std::unique_ptr<Expression>> elements;

    ~ArrayLiteral() override = default;

    std::string tokenLiteral() override { return tok.lit; }
    std::string toString() override;
    std::string type() override { return "array_literal"; }
};

struct CallExpression : Expression {
    Token tok;
    std::unique_ptr<Expression> callee;
    std::vector<std::unique_ptr<Expression>> arguments;

    ~CallExpression() override = default;

    std::string tokenLiteral() override { return tok.lit; }
    std::string type() override { return "call_expression"; }
    std::string toString() override;
};



struct IndexExpression : Expression {
    Token tok;
    std::unique_ptr<Expression> index;
    std::unique_ptr<Expression> array;

    std::string tokenLiteral() override { return tok.lit; }
    std::string toString() override;
    std::string type() override { return "index"; }
};

struct PrefixExpression : Expression {
    Token tok;
    std::string op;
    std::unique_ptr<Expression> rhs;

    std::string tokenLiteral() override { return tok.lit; }

    std::string toString() override;

    std::string type() override { return "prefix_expression"; }
};

struct InfixExpression : Expression {
    Token tok;
    std::unique_ptr<Expression> lhs;
    std::unique_ptr<Expression> rhs;
    std::string op;

    std::string tokenLiteral() override { return tok.lit; }

    std::string toString() override;

    std::string type() override { return "infix_expression"; }
};

struct IfExpression : Expression {
    Token tok;
    std::unique_ptr<Expression> condition;
    std::unique_ptr<BlockStatement> consequence;
    std::unique_ptr<BlockStatement> alternative;

    std::string tokenLiteral() override { return tok.lit; }

    std::string toString() override;

    std::string type() override { return "if_expression"; }
};

struct WhileExpression : Expression {
    Token tok;
    std::unique_ptr<Expression> condition;
    std::unique_ptr<BlockStatement> consequence;

    std::string tokenLiteral() override { return tok.lit; }

    std::string toString() override;

    std::string type() override { return "while_expression"; }
};

struct DeclareStatement : Statement {
    Token tok;
    std::unique_ptr<Identifier> name;
    std::unique_ptr<Expression> value;

    ~DeclareStatement() override = default;
    void statementNode() override {
    }

    std::string tokenLiteral() override { return tok.lit; }

    std::string toString() override;

    std::string type() override { return "declare"; }
};

struct ReferenceStatement : Statement {
    Token tok;
    std::unique_ptr<Identifier> name;
    std::unique_ptr<Expression> value;

    ~ReferenceStatement() override = default;

    void statementNode() override {
    }

    std::string tokenLiteral() override { return tok.lit; }

    std::string toString() override;

    std::string type() override { return "reference_statement"; }
};

struct ReturnStatement : Statement {
    Token tok;
    std::unique_ptr<Expression> returnVal;

    ~ReturnStatement() override = default;

    void statementNode() override {}

    std::string tokenLiteral() override { return tok.lit; }

    std::string toString() override;

    std::string type() override { return "return_statement"; }
};

struct ExpressionStatement : Statement {
    Token tok;
    std::unique_ptr<Expression> expression;

    ~ExpressionStatement() override = default;

    void statementNode() override {
    }

    std::string tokenLiteral() override { return tok.lit; }

    std::string toString() override;

    std::string type() override { return "expression_statement"; }
};


#endif //AST_H
