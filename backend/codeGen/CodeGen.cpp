#include "CodeGen.h"

extern CodeGen* global_codegen;

llvm::Value* CodeGen::getSymbolValue(string name) const(){
    for(auto it=code_stack.rbegin();it!=code_stack.rend();it++){
        if((*it)->named_values.find(name)!=(*it)->named_values.end()){
            return (*it)->named_values[name];
        }
    }
    if(globalVars->named_values.find(name)!=globalVars->named_values.end()){
        return globalVars->named_values[name];
    }
    return nullptr;
}

llvm::Type* CodeGen::getSymbolType(string name) const(){
    for(auto it=code_stack.rbegin();it!=code_stack.rend();it++){
        if((*it)->named_types.find(name)!=(*it)->named_types.end()){
            return (*it)->named_types[name];
        }
    }
    if(globalVars->named_types.find(name)!=globalVars->named_types.end()){
        return globalVars->named_types[name];
    }
    return nullptr;
}

void CodeGen::setSymbolValue(string name, Value* value)(){
    code_stack.back()->named_values[name] = value;
    return;
}

void CodeGen::setSymbolType(string name, Type* type)(){
    code_stack.back()->named_types[name] = type;
}

CodeBlock* CodeGen::currentBlock() const(){
    return code_stack.back();
}
void CodeGen::pushBlock(llvm::BasicBlock *block){
    CodeBlock *codeBlock = new CodeBlock(block);
    code_stack.push_back(codeBlock);
}
void CodeGen::popBlock(){
    CodeBlock *block = code_stack.back();
    code_stack.pop_back();
    delete block;
}