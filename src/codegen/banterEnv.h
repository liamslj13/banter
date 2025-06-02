// for llvm modules
#pragma once

#ifndef BANTER_H
#define BANTER_H

#include "llvm/ADT/APInt.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

static llvm::LLVMContext theContext;
static llvm::IRBuilder<> theBuilder(theContext);
static std::unique_ptr<llvm::Module> theModule;
static std::map<std::string, llvm::Value *> NamedValues;

#endif //BANTER_H
