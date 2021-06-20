#include "../../ast/AstProg.h"
#include "CodeGen.h"

// program: external_expression list
Value *AstProgram::codegen(CodeGen &context) {
    std::vector<AstExternalExpr *> external_exprlist = this->getExternalExpr();

    for(auto external_expr: external_exprlist) {
        Value *tp = external_expr->codegen(context);
        // if(tp==nullptr) return LogErrorV("AstProgram codegen error!");
    }
    return nullptr;
}

// external_expression : function_definition | declaration
Value *AstExternalExpr::codegen(CodeGen &context) {
    Value *v;
    if(this->getDeclaration()) {
        v = this->getDeclaration()->codegen(context);
    } else if(this->getFunDef()){
        v = this->getFunDef()->codegen(context);
    } else {
        LogError("Generate external_expr error: nothing found!");
    }

    // if(!v) LogErrorV("AstExternal->" + (isdecl?"Declaration":"Function") + " codegen: error!");
    return v;
}


//class AstFunDef;
//1. get return type from declaration_specifiers
//2. get function name & parameter_list from declarator (need to judge the type)
//3. Create new BasicBlock and declare new function parameters
//4. AstCompoundStatement->codeGen(context)
//5. create returnValue
//6. return function
llvm::Value* AstFunDef::codegen(CodeGen &context) {

    Type* retType = context.typeSystem.getType(this->getReturnType(), this->getReturnPtrLevel());
    std::string funcName = this->getFuncName();

    std::vector<Type*> argTypes;
    std::vector<std::pair<AstSpec*, AstDeclarator*>> paramList = this->getParamList();
    for(auto param:paramList){
        if(!param.second->hasPointer()){
            argTypes.push_back(context.typeSystem.getType(param.first->getLabel()));
        }
        else{
            int ptrLevel = param.second->getPointer()->getStarNum();
            argTypes.push_back(context.typeSystem.getType(param.first->getLabel(), ptrLevel));
            // []
        }
    }

    FunctionType* functionType = FunctionType::get(retType, argTypes, false);
    Function* function = Function::Create(functionType, GlobalValue::ExternalLinkage, funcName, context.theModule.get());
    if( !this->getIsExtern() ) {
        BasicBlock *basicBlock = BasicBlock::Create(context.llvmContext, funcName, function, nullptr);

        context.builder.SetInsertPoint(basicBlock);
        context.pushBlock(basicBlock, true);

        // declare function params
        auto param = paramList.begin();

        for (auto &irArgIter: function->args()) {
            irArgIter.setName((*param).second->getDirectDeclarator()->getIdentifier());
            // std::cout << "Args Type: " << context.typeSystem.getTypeStr(irArgIter.getType()) << std::endl;
            Value *argAlloc;
            int ptrLevel = 0;
            if ((*param).second->hasPointer())
                ptrLevel = (*param).second->getPointer()->getStarNum();
            string typeName = (*param).second->getDirectDeclarator()->getIdentifier();

            argAlloc = context.builder.CreateAlloca(context.typeSystem.getType((*param).first->getLabel(), ptrLevel));
            context.builder.CreateStore(&irArgIter, argAlloc);
            context.setSymbolValue(typeName, argAlloc);
            context.setSymbolType(typeName, context.typeSystem.getType((*param).first->getLabel(), ptrLevel));
//            context.setSymbolValue(typeName, &irArgIter);
//            context.setSymbolType(typeName, context.typeSystem.getType((*param).first->getLabel(), ptrLevel));
            param++;
        }

        this->getCompound_statement()->codegen(context);

//        if (context.getCurrentReturnValue()) {
//            context.builder.CreateRet(context.getCurrentReturnValue());
//        } else {
//            return LogErrorV("Function block return value not founded");
//        }
        context.popBlock();
    }
    return function;
}


