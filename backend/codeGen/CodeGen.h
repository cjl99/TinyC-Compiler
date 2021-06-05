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
#include <map>
#include <vector>
#include <tuple>
#include <iostream>

class CodeGen {
public:
    static std::unique_ptr<LLVMContext> TheContext;
    static std::unique_ptr<Module> TheModule;
    static std::unique_ptr<IRBuilder<>> Builder;

    // main's value included in here
    static std::vector<CodeBlock *> code_stack;
    static std::vector<FuncBlock *> func_stack;
};


class CodeBlock {
    std::map<std::string, llvm::Value*> named_values;
    std::map<std::string, llvm:Type*> named_types;

    CodeBlock* CreateCodeBlock();
};

class GlobalVarBlock : public CodeBlock {

};

class FuncBlock {
    std::map<std::string, llvm::Function*> named_functions;
    FuncBlock* CreateFuncBlock();
};


Value *LogErrorV(const char *Str) {
    LogError(Str);
    return nullptr;
}

void LogError(const char *Str) {
    std::errc << Str << std::endl;
}