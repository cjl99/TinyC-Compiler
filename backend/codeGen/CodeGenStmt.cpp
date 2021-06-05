#include "CodeGen.h"

static Value* CastToBoolean(CodeGenContext& context, Value* condValue){
    if(condValue->getType()->getTypeID()==Type::IntegerTyID)){
        condValue = context.builder.CreateIntCast(condValue, Type::getInt1Ty(context.llvmContext), true);
        return context.builder.CreateICmpNE(condValue, ConstantInt::get(Type::getInt1Ty(context.llvmContext), 0, true));
    }else if( condValue->getType()->getTypeID() == Type::DoubleTyID){
        retrun context.builder.CreateFCmpONE(condValue, ConstantFP::get(context.llvmContext, APFloat(0.0)));
    }
    return condValue;

}

llvm::Value* AstCompoundStmt::codeGen(CodeGenContext &context) {
    cout << "Generate compound statement" << endl;
    AstDeclarationList* declarationList = this->getAstDeclarationList();
    vector<AstStmt *> stmtList = this->getAstStmtList()->getStmtList();

    Function* theFunction = context.builder.GetInsertBlock()->getParent();
    BasicBlock* basicBlock = BasicBlock::Create(context.llvmContext, "compoundStmt", theFunction);
    context.builder.SetInsertPoint(basicBlock);
    context.pushBlock(basicBlock);

    declarationList->codeGen(context);
    Value* last = nullptr;
    for(auto it=stmtList->begin(); it!=stmtList->end(); it++){
        last = (*it)->codeGen(context);
    }

    context.popBlock();
    return last;
}

llvm::Value* AstSelectStmt::codeGen(CodeGen &context){
    cout << "Generating select statement" << endl;
    Value* condValue = this->getExpr()->codeGen(context);

    // cast to boolean
    condValue = CastToBoolean(context, condValue);

    Function* theFunction = context.builder.GetInsertBlock()->getParent();      // the function where if statement is in

    llvm::BasicBlock *then_block = llvm::BasicBlock::Create(this->context, "if_then", func);
    llvm::BasicBlock *else_block = llvm::BasicBlock::Create(this->context, "if_else", func);
    llvm::BasicBlock *cont_block = llvm::BasicBlock::Create(this->context, "if_cont", func);

    context.builder.CreateCondBr(condValue->getValue(), then_block, else_block);
    context.builder.SetInsertPoint(then_block);
    this->getThenClause()->codeGen();

    context.builder.CreateBr(cont_block);
    context.builder.SetInsertPoint(else_block);
    if (this->getElseClause() != nullptr) {
        this->getElseClause()->codeGen();
    }
    context.builder.CreateBr(cont_block);
    context.builder.SetInsertPoint(cont_block);

    return nullptr;

}

llvm::Value* AstIterStmt::codeGen(CodeGen &context){
    Function* theFunction = context.builder.GetInsertBlock()->getParent();

    BasicBlock *block = BasicBlock::Create(context.llvmContext, "for_loop", theFunction);
    BasicBlock *after = BasicBlock::Create(context.llvmContext, "for_cont", theFunction);
    context.currentBlock()->loopBreaks.push_back(after);
    // execute the initial
    if( this->getInitialExpr() )
        this->getInitialExpr()->codeGen(context);

    Value* condValue = this->getJudgeExpr()->codeGen(context);
    if( !condValue )
        return nullptr;
    condValue = CastToBoolean(context, condValue);

    // fall to the block
    context.builder.CreateCondBr(condValue, block, after);

    context.builder.SetInsertPoint(block);

    context.pushBlock(block);

    this->getBlock()->codeGen(context);

    context.popBlock();

    // do increment
    if( this->getUpdateExpr() ){
        this->getUpdateExpr()->codeGen(context);
    }

    // execute the again or stop
    condValue = this->getJudgeExpr()->codeGen(context);
    condValue = CastToBoolean(context, condValue);
    context.builder.CreateCondBr(condValue, block, after);

    // insert the after block
    theFunction->getBasicBlockList().push_back(after);
    context.builder.SetInsertPoint(after);

    context.currentBlock()->loopBreaks.pop_back(after);
    return nullptr;
}

llvm::Value* AstExprStmt::codeGen(CodeGen &context){
    if(this->getExpr())
        return this->getExpr()->codeGen(context);

    return nullptr;
}

llvm::Value* AstJmpStmt::codeGen(CodeGen &context){
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
        llvm::BasicBlock *cont_block = llvm::BasicBlock::Create(context, "break_cont", theFunction);
        context.builder.SetInsertPoint(cont_block);
        return nullptr;
    }
    else if(type=="return"){
        cout << "Generating return statement" << endl;
        Value* returnValue;
        if(this->getExpr())
            returnValue = this->getExpr()->codeGen(context);
        else returnValue = nullptr;
        context.setCurrentReturnValue(returnValue);
        return returnValue;
    }

}

