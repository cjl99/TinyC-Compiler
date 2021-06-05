#include "../../ast/AstProg.h"
#include "CodeGen.h"

Value *AstProgram::codegen() {
    std::vector<AstExternalExpr *> external_exprlist = this->getExternalExpr();

    for(auto external_expr: external_exprlist) {
        Value *tp = external_expr->codegen();
        if(tp==nullptr) return LogErrorV("AstProgram codegen error!");
    }

    return nullptr;
}


Value *AstExternalExpr::codegen() {
    bool is_decl = this->isdecl; // true is declaration & false is function

    Value *v;
    if(is_decl) {
        v = this->getDeclaration()->codegen();
    } else {
        v = this->getFunDef()->codegen();
    }

    if(!v) LogErrorV("AstExternal->" + (isdecl?"Declaration":"Function") + " codegen: error!");
    return v;
}

llvm::Value* NFunctionDeclaration::codeGen(CodeGenContext &context) {
    cout << "Generating function declaration of " << this->id->name << endl;
    std::vector<Type*> argTypes;

    for(auto &arg: *this->arguments){
        if( arg->type->isArray ){
            argTypes.push_back(PointerType::get(context.typeSystem.getVarType(arg->type->name), 0));
        } else{
            argTypes.push_back(TypeOf(*arg->type, context));
        }
    }
    Type* retType = nullptr;
    if( this->type->isArray )
        retType = PointerType::get(context.typeSystem.getVarType(this->type->name), 0);
    else
        retType = TypeOf(*this->type, context);

    FunctionType* functionType = FunctionType::get(retType, argTypes, false);
    Function* function = Function::Create(functionType, GlobalValue::ExternalLinkage, this->id->name.c_str(), context.theModule.get());

    if( !this->isExternal ){
        BasicBlock* basicBlock = BasicBlock::Create(context.llvmContext, "entry", function, nullptr);

        context.builder.SetInsertPoint(basicBlock);
        context.pushBlock(basicBlock);

        // declare function params
        auto origin_arg = this->arguments->begin();

        for(auto &ir_arg_it: function->args()){
            ir_arg_it.setName((*origin_arg)->id->name);
            Value* argAlloc;
            if( (*origin_arg)->type->isArray )
                argAlloc = context.builder.CreateAlloca(PointerType::get(context.typeSystem.getVarType((*origin_arg)->type->name), 0));
            else
                argAlloc = (*origin_arg)->codeGen(context);

            context.builder.CreateStore(&ir_arg_it, argAlloc, false);
            context.setSymbolValue((*origin_arg)->id->name, argAlloc);
            context.setSymbolType((*origin_arg)->id->name, (*origin_arg)->type);
            context.setFuncArg((*origin_arg)->id->name, true);
            origin_arg++;
        }

        this->block->codeGen(context);
        if( context.getCurrentReturnValue() ){
            context.builder.CreateRet(context.getCurrentReturnValue());
        } else{
            return LogErrorV("Function block return value not founded");
        }
        context.popBlock();

    }


    return function;
}
llvm::Value* AstFunDef::codegen() {
    std::vector<Type*> argTypes;

    int type = this->getType();
    if(type==2) {
        this->getCompound_statement()->congen();
        this->getDeclarationSpec();

        AstDeclarator* declarator = this->getDeclarator()->getAstDirectDeclarator();
        std::string func_name = declarator->getIdentifier();

        std::vector<std::pair<int, void *> > func_list = declarator->getAstDirectDeclarator();
        AstParamTypeList *paramList = nullptr;
        for(auto p: func_list) {
            if(p.first==5) {
                paramList = (AstParamTypeList *)p.second;
                break;
            }
        }

        for(auto param: paramList->getAstParamList()->getParamList()) {
            param->getType();
            if(type==1) {
                AstSpec *astSpec = (param->getAstSpecList()->getSpecList())[0];
                astSpe
                std::string *param_type = ->getLabel();

                std::string param_name = ((AstDeclarator *)param->getPtr())->getAstDirectDeclarator()->getIdentifier();

                argTypes.push_back()
            }
        }


        if(paramList== nullptr) return LogErrorV("AstFunction Declaration error: not find param type list");



        FuncBlock *fb = FuncBlock::CreateFuncBlock();
        global_codegen.func_stack.push_back(fb);

        node->getProgramHead()->Accept(this);
        this->block_stack.push_back(new CodeBlock());
        llvm::FunctionType *func_type = llvm::FunctionType::get(OurType::getLLVMType(this->context, OurType::INT_TYPE), false);
        llvm::Function *main_func = llvm::Function::Create(func_type, llvm::Function::ExternalLinkage, "main", &*(this->module));
        llvm::BasicBlock *entry = llvm::BasicBlock::Create(this->context, "entry", main_func);
        this->builder.SetInsertPoint(entry);
        node->getRoutine()->Accept(this);
        this->builder.CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(this->context), 0, true));

    }

    return nullptr;
}

//class AstFunDef;
//1. get return type from declaration_specifiers
//2. get function name & parameter_list from declarator (need to judge the type)
//3. Create new BasicBlock and declare new function parameters
//4. AstcompoundStatement->codeGen(context)
//5. create returnValue
//6. return function

