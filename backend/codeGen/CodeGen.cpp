#include "CodeGen.h"
//#include "../../ast/Ast.h"


// use reference to pass value instead of extern
//extern CodeGen* global_codegen;
Value* CodeGen::CastToBoolean(CodeGen& context, Value* condValue){
    if(condValue->getType()->getTypeID() == Type::IntegerTyID){
        condValue = context.builder.CreateIntCast(condValue, Type::getInt1Ty(context.llvmContext), true);
        return context.builder.CreateICmpNE(condValue, ConstantInt::get(Type::getInt1Ty(context.llvmContext), 0, true));
    }else if( condValue->getType()->getTypeID() == Type::DoubleTyID){
        return context.builder.CreateFCmpONE(condValue, ConstantFP::get(context.llvmContext, APFloat(0.0)));
    }
    return condValue;

}

llvm::Value* CodeGen::getSymbolValue(string name) const{
    for(auto it=code_stack.rbegin();it!=code_stack.rend();it++){
        if((*it)->named_values.find(name)!=(*it)->named_values.end()){
            return (*it)->named_values[name];
        }
    }
//    if(globalVars->named_values.find(name)!=globalVars->named_values.end()){
//        return globalVars->named_values[name];
//    }
    return nullptr;
}

llvm::Type* CodeGen::getSymbolType(string name) const{
    for(auto it=code_stack.rbegin();it!=code_stack.rend();it++){
        if((*it)->named_types.find(name)!=(*it)->named_types.end()){
            return (*it)->named_types[name];
        }
    }
    // globalVars stored in the code_stack[0] now.
//    if(globalVars->named_types.find(name)!=globalVars->named_types.end()){
//        return globalVars->named_types[name];
//    }
    return nullptr;
}

llvm::Type* CodeGen::getTypefromValue(Value *value) const {
    for(auto it=code_stack.rbegin();it!=code_stack.rend();it++){
        if((*it)->ValueToType.find(value)!=(*it)->ValueToType.end()){
            return (*it)->ValueToType[value];
        }
    }
    return nullptr;
}

bool CodeGen::isIdentifier(Value* value){
    return value->getType()->isPointerTy() || value->getType()->isPointerTy();
}
void CodeGen::setSymbolValue(string name, Value* value){
    this->code_stack.back()->named_values[name] = value;
    return;
}

void CodeGen::setSymbolType(string name, Type* type){
    this->code_stack.back()->named_types[name] = type;
}

void CodeGen::setValueType(llvm::Value *value, llvm::Type *type) {
    this->code_stack.back()->ValueToType[value] = type;
}

CodeBlock* CodeGen::currentBlock() const{
    return this->code_stack.back();
}
void CodeGen::pushBlock(llvm::BasicBlock *block, bool isFuncBlock){
    CodeBlock *codeBlock = new CodeBlock(block, isFuncBlock);
    codeBlock->returnValue = nullptr;
    this->code_stack.push_back(codeBlock);
}
void CodeGen::popBlock(){
    CodeBlock *block = code_stack.back();
    this->code_stack.pop_back();
    delete block;
}

Value* CodeGen::getCurrentReturnValue(){
    return this->code_stack.back()->returnValue;
}

void CodeGen::setCurrentReturnValue(Value *retValue) {
    for(auto it=code_stack.rbegin();it!=code_stack.rend();it++){
        if((*it)->isFuncBlock){
            (*it)->returnValue = retValue;
            return ;
        }
    }
}

void CodeGen::generateCode(AstProgram* root) {
    cout << "[LLVM] Generating IR code..." << endl;

    std::vector<Type*> sysArgs;
    FunctionType* mainFuncType = FunctionType::get(Type::getVoidTy(this->llvmContext), makeArrayRef(sysArgs), false);
    Function* mainFunc = Function::Create(mainFuncType, GlobalValue::ExternalLinkage, "main");
    BasicBlock* block = BasicBlock::Create(this->llvmContext, "entry");

    pushBlock(block, true);
    Value* retValue = root->codegen(*this);
    popBlock();

    cout << "[LLVM] Code generate success!\n" << endl;

    raw_ostream *out = &outs();
    std::error_code EC;
    out = new raw_fd_ostream("ir.ll", EC);

    llvm::legacy::PassManager passManager;
    passManager.add(createPrintModulePass(*out));
    passManager.run(*(this->theModule.get()));

    if (out != &outs())
        delete out;
    return;
}

void LogError(const char *str) {
    fprintf(stderr, "LogError: %s\n", str);
    std::exit(EXIT_FAILURE);
}

Value *LogErrorV(string str){
    LogErrorV(str.c_str());
    return nullptr;
}

Value *LogErrorV(const char *str) {
    LogError(str);
    return nullptr;
}


