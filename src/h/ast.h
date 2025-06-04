#pragma once

#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <llvm/IR/Value.h>

#include "../h/lex.h"

struct Node {
    virtual ~Node() = default;

    virtual std::string tokenLiteral() = 0;

    virtual std::string toString() = 0;

    virtual std::string type() = 0;

    virtual llvm::Value *codeGen() = 0;
};

struct Statement : Node {
    virtual void statementNode() = 0;

    std::string tokenLiteral() override = 0;

    std::string toString() override = 0;

    std::string type() override = 0;

    llvm::Value *codeGen() override;
};

struct Expression : Node {
    virtual void expressionNode() = 0;

    std::string tokenLiteral() override = 0;
    std::string toString() override = 0;
    std::string type() override = 0;

    llvm::Value *codeGen() override;
};

struct Program : Node {
    std::vector<std::unique_ptr<Statement>> statements;

    ~Program() override = default;

    std::string tokenLiteral() override;
    std::string toString() override;
    std::string type() override { return "program"; }

    llvm::Value *codeGen() override;
};

struct Identifier : Expression {
    Token tok;
    std::string value;

    void expressionNode() override {}

    std::string tokenLiteral() override { return tok.lit; }
    std::string toString() override { return value; }
    std::string type() override { return "identifier"; }
};

struct BlockStatement : Statement {
    Token tok;
    std::vector<std::unique_ptr<Statement>> statements;

    ~BlockStatement() override = default;
    void statementNode() override {}

    std::string tokenLiteral() override { return tok.lit; }
    std::string toString() override;
    std::string type() override { return "block_statement"; }

    llvm::Value *codeGen() override;
};

struct IntLiteral : Expression {
    Token tok;
    int value;

    void expressionNode() override {}

    std::string tokenLiteral() override { return tok.lit; }
    std::string toString() override { return std::to_string(value); }
    std::string type() override { return "int_literal"; }

    llvm::Value *codeGen() override;
};

struct BoolLiteral : Expression {
    Token tok;
    bool value = false;

    void expressionNode() override {}

    std::string tokenLiteral() override { return tok.lit; }
    std::string toString() override { return value ? "true" : "false"; }
    std::string type() override { return "bool_literal"; }

    llvm::Value *codeGen() override;
};

struct StringLiteral : Expression {
    Token tok;
    std::string value;

    void expressionNode() override {}

    std::string tokenLiteral() override { return tok.lit; }
    std::string toString() override { return value; }
    std::string type() override { return "string_literal"; }

    llvm::Value *codeGen() override;
};

struct FuncLiteral : Expression {
    Token tok;
    std::vector<std::unique_ptr<Identifier>> params;
    std::unique_ptr<BlockStatement> body;

    ~FuncLiteral() override = default;
    void expressionNode() override {}

    std::string tokenLiteral() override { return tok.lit; }
    std::string toString() override;
    std::string type() override { return "func_literal"; }

    llvm::Value *codeGen() override;
};

struct ArrayLiteral : Expression {
    Token tok;
    std::vector<std::unique_ptr<Expression>> elements;

    ~ArrayLiteral() override = default;
    void expressionNode() override {}

    std::string tokenLiteral() override { return tok.lit; }
    std::string toString() override;
    std::string type() override { return "array_literal"; }

    llvm::Value *codeGen() override; // todo
};

struct CallExpression : Expression {
    Token tok;
    std::unique_ptr<Expression> callee;
    std::vector<std::unique_ptr<Expression>> arguments;

    ~CallExpression() override = default;
    void expressionNode() override {}

    std::string tokenLiteral() override { return tok.lit; }
    std::string type() override { return "call_expression"; }
    std::string toString() override;

    llvm::Value *codeGen() override; // todo
};

struct IndexExpression : Expression {
    Token tok;
    std::unique_ptr<Expression> index;
    std::unique_ptr<Expression> array;

    void expressionNode() override {}

    std::string tokenLiteral() override { return tok.lit; }
    std::string toString() override;
    std::string type() override { return "index"; }

    llvm::Value *codeGen() override; // todo
};

struct PrefixExpression : Expression {
    Token tok;
    std::string op;
    std::unique_ptr<Expression> rhs;

    void expressionNode() override {}

    std::string tokenLiteral() override { return tok.lit; }
    std::string toString() override;
    std::string type() override { return "prefix_expression"; }

    llvm::Value *codeGen() override;
};

struct InfixExpression : Expression {
    Token tok;
    std::unique_ptr<Expression> lhs;
    std::unique_ptr<Expression> rhs;
    std::string op;

    void expressionNode() override {}

    std::string tokenLiteral() override { return tok.lit; }
    std::string toString() override;
    std::string type() override { return "infix_expression"; }

    llvm::Value *codeGen() override; // todo
};

struct IfExpression : Expression {
    Token tok;
    std::unique_ptr<Expression> condition;
    std::unique_ptr<BlockStatement> consequence;
    std::unique_ptr<BlockStatement> alternative;

    void expressionNode() override {}

    std::string tokenLiteral() override { return tok.lit; }
    std::string toString() override;
    std::string type() override { return "if_expression"; }

    llvm::Value *codeGen() override; // todo
};

struct WhileExpression : Expression {
    Token tok;
    std::unique_ptr<Expression> condition;
    std::unique_ptr<BlockStatement> consequence;

    void expressionNode() override {}

    std::string tokenLiteral() override { return tok.lit; }
    std::string toString() override;
    std::string type() override { return "while_expression"; }

    llvm::Value *codeGen() override; // todo
};

struct DeclareStatement : Statement {
    Token tok;
    std::unique_ptr<Identifier> name;
    std::unique_ptr<Expression> value;

    ~DeclareStatement() override = default;
    void statementNode() override {}

    std::string tokenLiteral() override { return tok.lit; }
    std::string toString() override;
    std::string type() override { return "declare_statement"; }

    llvm::Value *codeGen() override;
};

struct ReferenceStatement : Statement {
    Token tok;
    std::unique_ptr<Identifier> name;
    std::unique_ptr<Expression> value;

    ~ReferenceStatement() override = default;
    void statementNode() override {}

    std::string tokenLiteral() override { return tok.lit; }
    std::string toString() override;
    std::string type() override { return "reference_statement"; }

    llvm::Value *codeGen() override; // todo
};

struct ReturnStatement : Statement {
    Token tok;
    std::unique_ptr<Expression> returnVal;

    ~ReturnStatement() override = default;
    void statementNode() override {}

    std::string tokenLiteral() override { return tok.lit; }
    std::string toString() override;
    std::string type() override { return "return_statement"; }

    llvm::Value *codeGen() override;
};

struct ExpressionStatement : Statement {
    Token tok;
    std::unique_ptr<Expression> expression;

    ~ExpressionStatement() override = default;
    void statementNode() override {}

    std::string tokenLiteral() override { return tok.lit; }
    std::string toString() override;
    std::string type() override { return "expression_statement"; }

    llvm::Value *codeGen() override; // todo
};


#endif //AST_H
