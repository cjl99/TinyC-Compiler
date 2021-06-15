#include <map>
#include <vector>
#include <tuple>
#include <iostream>
#include <string>

#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/Support/raw_ostream.h>

#include "../TypeSystem/TypeSystem.h"

#include "../../ast/AstBase.h"
#include "../../ast/AstProg.h"

//using legacy::PassManager;

class CodeBlock;
class CodeGen;

// { } or
class CodeBlock {
public:
    std::map<std::string, Value*> named_values;
    std::map<std::string, Type*> named_types;
    std::map<Value*, Type*> ValueToType;

    Value * returnValue = nullptr;
    llvm::BasicBlock *block;
    llvm::BasicBlock *loopBreak = nullptr;
    llvm::BasicBlock *loopContinue = nullptr;

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
    IRBuilder<> builder;

    TypeSystem typeSystem;

    CodeGen(): builder(llvmContext), typeSystem(llvmContext){
        theModule = std::unique_ptr<Module>(new Module("main", this->llvmContext));
    }


    Value* getSymbolValue(std::string name) const;
    Type* getSymbolType(std::string name) const;
    Type* getTypefromValue(Value *value) const;
    void setSymbolValue(std::string name, Value* value);
    void setSymbolType(std::string name, Type* type);
    void setValueType(Value* value, Type* type);

    CodeBlock* currentBlock() const;
    void pushBlock(llvm::BasicBlock * block);
    void popBlock();

    void generateCode(AstProgram *root);
    Value *getCurrentReturnValue();
    void setCurrentReturnValue(Value *retValue);
    static Value* CastToBoolean(CodeGen& context, Value* condValue);
};
void LogError(const char *str);
Value* LogErrorV(const char* str);
Value* LogErrorV(string str);


