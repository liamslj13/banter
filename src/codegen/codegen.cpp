#include "banterEnv.h"
#include "../h/ast.h"

llvm::Value *Node::codeGen() {
    return nullptr;
}

llvm::Value *Statement::codeGen() {
    return nullptr;
}

llvm::Value *Expression::codeGen() {
    return nullptr;
}

llvm::Value *Program::codeGen() {
    return nullptr;
}

llvm::Value *BlockStatement::codeGen() {
    return nullptr;
}

llvm::Value *IntLiteral::codeGen() {
    return nullptr;
}

llvm::Value *BoolLiteral::codeGen() {
    return nullptr;
}

llvm::Value *StringLiteral::codeGen() {
    return nullptr;
}

llvm::Value *FuncLiteral::codeGen() {
    return nullptr;
}

llvm::Value *ArrayLiteral::codeGen() {
    return nullptr;
}

llvm::Value *CallExpression::codeGen() {
    return nullptr;
}

llvm::Value *IndexExpression::codeGen() {
    return nullptr;
}

llvm::Value *PrefixExpression::codeGen() {
    return nullptr;
}

llvm::Value *InfixExpression::codeGen() {
    return nullptr;
}

llvm::Value *IfExpression::codeGen() {
    return nullptr;
}

llvm::Value *WhileExpression::codeGen() {
    return nullptr;
}

llvm::Value *DeclareStatement::codeGen() {
    return nullptr;
}

llvm::Value *ReferenceStatement::codeGen() {
    return nullptr;
}

llvm::Value *ReturnStatement::codeGen() {
    return nullptr;
}

llvm::Value *ExpressionStatement::codeGen() {
    return nullptr;
}
