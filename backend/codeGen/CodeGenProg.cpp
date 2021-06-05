#include "../../ast/AstProg.h"
#include "CodeGen.h"

Value *AstProgram::codeGen() {
    std::vector<AstExternalExpr *> external_exprlist = this->getExternalExpr();

    for(auto external_expr: external_exprlist) {
        Value *tp = external_expr->codegen();
        if(tp==nullptr) return LogErrorV("AstProgram codegen error!");
    }
    return nullptr;
}


Value *AstExternalExpr::codeGen() {
    bool is_decl = (this->getDeclaration()!=nullptr); // true is declaration & false is function

    Value *v;
    if(is_decl) {
        v = this->getDeclaration()->codegen();
    } else {
        v = this->getFunDef()->codegen();
    }

    if(!v) LogErrorV("AstExternal->" + (isdecl?"Declaration":"Function") + " codegen: error!");
    return v;
}

llvm::Value* AstFunDef::codegen(CodeGen &context) {

    Type* retType = context.typeSystem.getType(this->getReturnType(), this->getReturnPtrLevel());
    std::string funcName = this->getFuncName();

    std::vector<Type*> argTypes;
    std::vector<std::pair<AstSpec*, AstDeclarator*>> paramList = this->getParamList();
    for(auto param:paramList){
        if(!param.second->hasPointer())
            argTypes.push_back(contex.typeSystem.getType(param.first->getLabel()));
        else{
            int ptrLevel = param.second->getPointer()->getStarNum();
            argTypes.push_back(contex.typeSystem.getType(param.first->getLabel(), ptrLevel));
        }
    }

    FunctionType* functionType = FunctionType::get(retType, argTypes, false);
    Function* function = Function::Create(functionType, GlobalValue::ExternalLinkage, funcName, context.theModule.get());
    context.functions[funcName] = function;

    BasicBlock* basicBlock = BasicBlock::Create(context.llvmContext, "entry", function, nullptr);

    context.builder.SetInsertPoint(basicBlock);
    context.pushBlock(basicBlock);

    // declare function params
    auto param = paramList->begin();

    for(auto &irArgIter: function->args()){
        irArgIter.setName((*param).second->getDirectDeclarator()->getIdentifier());
        Value* argAlloc;
        int ptrLevel = 0;
        if((*param).second->hasPointer())
            ptrLevel = param.second->getPointer()->getStarNum();
        string typeName = param.second->getDirectDeclarator()->getIdentifier();

        argAlloc = context.builder.CreateAlloca(contex.typeSystem.getType(param.first->getLabel(), ptrLevel));

        context.builder.CreateStore(&ir_arg_it, argAlloc, false);
        context.setSymbolValue(typeName, argAlloc);
        context.setSymbolType(typeName, contex.typeSystem.getType(param.first->getLabel(), ptrLevel));
        param++;
    }

    this->getCompound_statement()->codeGen(context);
    if( context.getCurrentReturnValue() ){
        context.builder.CreateRet(context.getCurrentReturnValue());
    } else{
        return LogErrorV("Function block return value not founded");
    }
    context.popBlock();

    return function;

}

//class AstFunDef;
//1. get return type from declaration_specifiers
//2. get function name & parameter_list from declarator (need to judge the type)
//3. Create new BasicBlock and declare new function parameters
//4. AstcompoundStatement->codeGen(context)
//5. create returnValue
//6. return function

