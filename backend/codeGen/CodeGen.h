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
class CodeGen;

class CodeBlock {
private:
    std::map<std::string, Value*> named_values;
    std::map<std::string, Type*> named_types;
    Value * returnValue = nullptr;
    llvm::BasicBlock *block;
    std::vector<llvm::BasicBlock *> loopBreaks;
public:
    CodeBlock(llvm::BasicBlock *block){
        this->block = block;
    }
};

class CodeGen {
private:
    // main's value included in here
    std::vector<CodeBlock *> code_stack;

public:
    LLVMContext llvmContext;
    std::unique_ptr<Module> theModule;
    IRBuilder<> Builder;

    CodeBlock *globalVars;
    std::map<std::string, llvm::Function*> functions;
    TypeSystem typeSystem;

    CodeGen(): Builder(llvmContext), typeSystem(llvmContext){
        theModule = std::unique_ptr<Module>(new Module("main", this->llvmContext));
        BasicBlock* basicBlock = BasicBlock::Create(llvmContext);
        globalVars = new CodeBlock(basicBlock);
    }

    Value* getSymbolValue(std::string name) const;
    Type* getSymbolType(std::string name) const;
    void setSymbolValue(std::string name, Value* value);
    void setSymbolType(std::string name, Type* type);
    CodeBlock* currentBlock() const;
    void pushBlock(CodeBlock * block);
    void popBlock();

};

void LogError(const char *Str) {
    std::cout << Str << std::endl;
}

Value *LogErrorV(const char *Str) {
    LogError(Str);
    return nullptr;
}

