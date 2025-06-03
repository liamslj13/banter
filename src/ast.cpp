#include "h/ast.h"

#include <functional>

std::string Program::tokenLiteral() {
    if (statements.size()) {
        return statements[0]->tokenLiteral();
    } else {
        return "";
    }
}

std::string Program::toString() {
    std::string res;
    for (const auto& stmt : statements) {
        res += stmt->toString() + "\n";
    }
    return res;
}

std::string DeclareStatement::toString() {
    std::string res = tokenLiteral() + " " + name->toString() +
        " = ";
    if (value != nullptr) {
        res += value->toString();
    }
    res += ";";
    return res;
}

std::string ReferenceStatement::toString() {
    std::string res = tokenLiteral() + " " + name->toString() + " = ";
    if (value != nullptr) {
        res += value->toString();
    }
    res +=  ";";
    return res;
}

std::string ReturnStatement::toString() {
    std::string res = tokenLiteral() + " ";
    if (returnVal != nullptr) {
        res += returnVal->toString();
    }
    res += ";";
    return res;
}

std::string ExpressionStatement::toString() {
    std::string res = "";
    if (expression != nullptr) {
        res += expression->toString();
    }
    res +=  ";";
    return res;
}

std::string BlockStatement::toString() {
    std::string res = "{ ";
    for (const auto& stmt : statements) {
        res += stmt->toString() + " ";
    }
    res += "}";
    return res;
}

std::string PrefixExpression::toString() {
    std::string res = "(" + op + rhs->toString() + ")";
    return res;
}

std::string InfixExpression::toString() {
    std::string res = "(" + lhs->toString() + op + rhs->toString() + ")";
    return res;
}

std::string IfExpression::toString() {
    std::string res = "if " + condition->toString() + " " + consequence->toString() + " ";
    if (alternative != nullptr) {
        res += " else " + alternative->toString();
    }
    return res;
}

std::string WhileExpression::toString() {
    std::string res = "while " + condition->toString() + " " + consequence->toString();
    return res;
}

std::string FuncLiteral::toString() {
    std::string res = tokenLiteral() + " (";
    for (const auto& param : params) {
        res += param->toString() + ", ";
    }
    res += ")";
    res += body->toString();
    return res;
}

std::string ArrayLiteral::toString() {
    std::string res = "[";
    for (const auto& element : elements) {
        res += element->toString() + ", ";
    }
    res += "]";
    return res;
}

std::string CallExpression::toString() {
    std::string res = callee->toString() + "(";
    for (const auto& arg : arguments) {
        res += arg->toString() + ", ";
    }
    res += ")";
    return res;
}

std::string IndexExpression::toString() {
    return "(" + array->toString() + "[" + index->toString() + "])";
}