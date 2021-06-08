#include "CodeGen.h"

static Value* CastToBoolean(CodeGen& context, Value* condValue){
    if(condValue->getType()->getTypeID() == Type::IntegerTyID){
        condValue = context.builder.CreateIntCast(condValue, Type::getInt1Ty(context.llvmContext), true);
        return context.builder.CreateICmpNE(condValue, ConstantInt::get(Type::getInt1Ty(context.llvmContext), 0, true));
    }else if( condValue->getType()->getTypeID() == Type::DoubleTyID){
        return context.builder.CreateFCmpONE(condValue, ConstantFP::get(context.llvmContext, APFloat(0.0)));
    }
    return condValue;

}

llvm::Value* AstCompoundStmt::codegen(CodeGen &context) {
    std::cout << "Generate compound statement" << std::endl;

    vector<AstDeclaration *> decl_list = this->getAstDeclarationList()->getDeclarationList();

    vector<AstStmt *> stmtList = this->getAstStmtList()->getStmtList();
    std::cout << "test2" << std::endl;

    Function* theFunction = context.builder.GetInsertBlock()->getParent();
    std::cout << "test3" << std::endl;

    BasicBlock* basicBlock = BasicBlock::Create(context.llvmContext, "compoundStmt", theFunction);
    std::cout << "test4" << std::endl;

    context.builder.SetInsertPoint(basicBlock);
    std::cout << "test5" << std::endl;

    context.pushBlock(basicBlock);
    std::cout << "test6" << std::endl;


    for(auto decl : decl_list) {
        decl->codegen(context);
    }
    Value* last = nullptr;
    for(auto stmt : stmtList){
        last = stmt->codegen(context);
    }

    context.popBlock();
    return last;
}

llvm::Value* AstSelectStmt::codegen(CodeGen &context){
    cout << "Generating select statement" << endl;
    Value* condValue = this->getExpr()->codegen(context);

    // cast to boolean
    condValue = CastToBoolean(context, condValue);

    Function* theFunction = context.builder.GetInsertBlock()->getParent();      // the function where if statement is in

    llvm::BasicBlock *then_block = llvm::BasicBlock::Create(context.llvmContext, "if_then", theFunction);
    llvm::BasicBlock *else_block = llvm::BasicBlock::Create(context.llvmContext, "if_else", theFunction);
    llvm::BasicBlock *cont_block = llvm::BasicBlock::Create(context.llvmContext, "if_cont", theFunction);

    context.builder.CreateCondBr(condValue, then_block, else_block);
    context.builder.SetInsertPoint(then_block);
    this->getThenClause()->codegen(context);

    context.builder.CreateBr(cont_block);
    context.builder.SetInsertPoint(else_block);
    if (this->getElseClause() != nullptr) {
        this->getElseClause()->codegen(context);
    }
    context.builder.CreateBr(cont_block);
    context.builder.SetInsertPoint(cont_block);

    return nullptr;

}

llvm::Value* AstIterStmt::codegen(CodeGen &context){
    Function* theFunction = context.builder.GetInsertBlock()->getParent();

    BasicBlock *block = BasicBlock::Create(context.llvmContext, "for_loop", theFunction);
    BasicBlock *after = BasicBlock::Create(context.llvmContext, "for_cont", theFunction);
    context.currentBlock()->loopBreaks.push_back(after);
    // execute the initial
    if( this->getInitialExpr() )
        this->getInitialExpr()->codegen(context);

    Value* condValue = this->getJudgeExpr()->codegen(context);
    if( !condValue )
        return nullptr;
    condValue = CastToBoolean(context, condValue);

    // fall to the block
    context.builder.CreateCondBr(condValue, block, after);

    context.builder.SetInsertPoint(block);

    context.pushBlock(block);

    this->getBlock()->codegen(context);

    context.popBlock();

    // do increment
    if( this->getUpdateExpr() ){
        this->getUpdateExpr()->codegen(context);
    }

    // execute the again or stop
    condValue = this->getJudgeExpr()->codegen(context);
    condValue = CastToBoolean(context, condValue);
    context.builder.CreateCondBr(condValue, block, after);

    // insert the after block
    theFunction->getBasicBlockList().push_back(after);
    context.builder.SetInsertPoint(after);

    context.currentBlock()->loopBreaks.pop_back();
    return nullptr;
}

llvm::Value* AstExprStmt::codegen(CodeGen &context){
    if(this->getExpr())
        return this->getExpr()->codegen(context);

    return nullptr;
}

llvm::Value* AstJmpStmt::codegen(CodeGen &context){
    string type = this->getType();
    if(type=="continue"){
        //==========Todo==============
    }
    else if(type=="break"){
        if (context.currentBlock()->loopBreaks.empty()) {
            LogError("Cannot use break statement out of loops");
            return nullptr;
        }
        context.builder.CreateBr(context.currentBlock()->loopBreaks.back());
        llvm::Function *theFunction = context.builder.GetInsertBlock()->getParent();
        llvm::BasicBlock *cont_block = llvm::BasicBlock::Create(context.llvmContext, "break_cont", theFunction);
        context.builder.SetInsertPoint(cont_block);
        return nullptr;
    }
    else if(type=="return"){
        cout << "Generating return statement" << endl;
        Value* returnValue;
        if(this->getExpr())
            returnValue = this->getExpr()->codegen(context);
        else returnValue = nullptr;
        context.setCurrentReturnValue(returnValue);
        return returnValue;
    }

    return nullptr;
}

