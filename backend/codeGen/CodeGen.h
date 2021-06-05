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
#include "../TypeSystem/TypeSystem.h"
#include <map>
#include <vector>
#include <tuple>
#include <iostream>

class CodeBlock;
class GlobalVarBlock;
class CodeGen;

class CodeGen {
private:
    // main's value included in here
    static std::vector<CodeBlock *> code_stack;

public:
    static LLVMContext llvmContext;
    static std::unique_ptr<Module> TheModule;
    static std::unique_ptr<IRBuilder<>> Builder;

    GlobalVarBlock *globalVars;
    std::map<std::string, llvm::Function*> functions;
    TypeSystem typeSystem;

    CodeGen(): Builder(llvmContext), typeSystem(llvmContext){
        theModule = unique_ptr<Module>(new Module("main", this->llvmContext));
        globalVars = new GlobalVarBlock();
    }

    llvm::Value* getSymbolValue(string name) const();
    llvm::Type* getSymbolType(string name) const();
    void setSymbolValue(string name, Value* value)();
    void setSymbolType(string name, Type* type)();
    CodeBlock* currentBlock() const();
    void pushBlock(CodeBlock * block);
    void popBlock();

};


class CodeBlock {
private:
    std::map<std::string, llvm::Value*> named_values;
    std::map<std::string, llvm:Type*> named_types;
    Value * returnValue = nullptr;
    llvm::BasicBlock *block;
    std::vector<llvm::BasicBlock *> loopBreaks;
public:
    CodeBlock(llvm::BasicBlock *block){
        this->block = block;
    }
};

class GlobalVarBlock : public CodeBlock {

};

Value *LogErrorV(const char *Str) {
    LogError(Str);
    return nullptr;
}

void LogError(const char *Str) {
    std::errc << Str << std::endl;
}