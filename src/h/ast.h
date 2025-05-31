#pragma once

#ifndef AST_H
#define AST_H

#include <memory>
#include <string>
#include <vector>

class ExprAST {
public:
    virtual ~ExprAST() = default;
};

class IntExprAST : public ExprAST {
    int value;
public:
    explicit IntExprAST(const int value) : value(value) {}
};

class VariableExprAST : public ExprAST {
    std::string name;
public:
    explicit VariableExprAST(const std::string &name) : name(name) {}
};

class BinaryExprAST : public ExprAST {
    char op;
    std::unique_ptr<ExprAST> lhs, rhs;
public:
    explicit BinaryExprAST(const char &op, std::unique_ptr<ExprAST> lhs,  std::unique_ptr<ExprAST> rhs)
    :  op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}
};

class CallExprAST : public ExprAST {
    std::string callee;
    std::vector<std::unique_ptr<ExprAST>> args;
public:
    explicit CallExprAST(const std::string &callee, std::vector<std::unique_ptr<ExprAST>> args)
        : callee(callee), args(std::move(args)) {}
};

class PrototypeAST {
    std::string name;
    std::vector<std::string> args;

public:
    explicit PrototypeAST(const std::string &name, std::vector<std::string> args)
        : name(name), args(std::move(args)) {}

    [[nodiscard]] const std::string &getName() const { return name; }
};

class FunctionAST {
    std::unique_ptr<PrototypeAST> proto;
    std::unique_ptr<ExprAST> body;

public:
    explicit FunctionAST(std::unique_ptr<PrototypeAST> proto, std::unique_ptr<ExprAST> body)
        :  proto(std::move(proto)), body(std::move(body)) {}
};





#endif //AST_H
