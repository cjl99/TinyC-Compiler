#include "CodeGen.h"
#include "../../ast/AstStmt.h"

llvm::Value* AstCompoundStmt::codegen(CodeGen &context) {
    std::cout << "Generate compound statement" << std::endl;
    // declaration list part
    AstDeclarationList *decl_list = this->getAstDeclarationList();
    Value *lastV = nullptr;
    if(decl_list) {
        std::vector<AstDeclaration *> decl_v = decl_list->getDeclarationVector();
        for (auto decl:decl_v) {
            lastV = decl->codegen(context);
        }
    }

    // stmt list part
    AstStmtList *stmtlist = this->getAstStmtList();
    if(stmtlist) {
        vector<AstStmt *> stmt_vec = stmtlist->getStmtList();
        for(AstStmt *stmt: stmt_vec) {
            lastV = stmt->codegen(context);
        }
    }

    return lastV;
}

llvm::Value * AstStmt::codegen(CodeGen &context) {
    std::cout << "Generate Statement" << std::endl;
    AstNonLabelStmt *nonLabelStmt = this->getStmt();
    int stmt_type = this->getType();
    std::cout << "StmtType: " + to_string(stmt_type) << std::endl;
    switch (stmt_type) {
        case 1:
            return ((AstCompoundStmt *) nonLabelStmt)->codegen(context);
            break;
        case 2:
            return ((AstExprStmt *) nonLabelStmt)->codegen(context);
            break;
        case 3:
            return ((AstSelectStmt *) nonLabelStmt)->codegen(context);
            break;
        case 4:
            return ((AstIterStmt *) nonLabelStmt)->codegen(context);
            break;
        case 5:
            return ((AstJmpStmt *) nonLabelStmt)->codegen(context);
            break;
    }
    return nullptr;
}

llvm::Value* AstSelectStmt::codegen(CodeGen &context){
    cout << "Generating select statement" << endl;
    Value* condValue = this->getExpr()->codegen(context);
    // cast to boolean
    condValue = context.CastToBoolean(context, condValue);

    Function* theFunction = context.builder.GetInsertBlock()->getParent();      // the function where if statement is in
    BasicBlock *thenBlock = BasicBlock::Create(context.llvmContext, "ifthen", theFunction);
    BasicBlock *elseBlock = BasicBlock::Create(context.llvmContext, "ifelse");
    BasicBlock *mergeBlock = BasicBlock::Create(context.llvmContext, "ifcont");

    // get the outer loop
    BasicBlock* parentLoopBreak = context.currentBlock()->loopBreak;
    BasicBlock* parentLoopContinue = context.currentBlock()->loopContinue;

    if( this->getElseClause() ){
        context.builder.CreateCondBr(condValue, thenBlock, elseBlock);
    } else{
        context.builder.CreateCondBr(condValue, thenBlock, mergeBlock);
    }

    // Emit Then
    context.builder.SetInsertPoint(thenBlock);

    context.pushBlock(thenBlock);
    context.currentBlock()->loopBreak = parentLoopBreak;
    context.currentBlock()->loopContinue = parentLoopContinue;
    Value *ThenV = this->getThenClause()->codegen(context);
    context.popBlock();

    if (ThenV == nullptr) {
        std::cout << "No Then clause" << std::endl;
    }

    // Codegen of 'Then' can change the current block, update ThenBB for the PHI.
    thenBlock = context.builder.GetInsertBlock();
    if( thenBlock->getTerminator() == nullptr ){       //
        context.builder.CreateBr(mergeBlock);
    }

    // Emit Else
    Value *ElseV = nullptr;
    if(this->getElseClause()) {
        theFunction->getBasicBlockList().push_back(elseBlock);
        context.builder.SetInsertPoint(elseBlock);
        context.pushBlock(elseBlock);
        context.currentBlock()->loopBreak = parentLoopBreak;
        context.currentBlock()->loopContinue = parentLoopContinue;
        ElseV = this->getElseClause()->codegen(context);
        context.popBlock();

        if (ElseV == nullptr) {
            std::cout << "No else clause" << std::endl;
        }

        if( elseBlock->getTerminator() == nullptr ){       //
            context.builder.CreateBr(mergeBlock);
        }
        // Codegen of 'Else' can change the current block, update ElseBB for the PHI.
        elseBlock = context.builder.GetInsertBlock();
    }

    // Emit merge block.
    theFunction->getBasicBlockList().push_back(mergeBlock);
    context.builder.SetInsertPoint(mergeBlock);

     return nullptr;
}


llvm::Value* AstIterStmt::codegen(CodeGen &context){
    cout << "Generating iteration statement" << endl;

    Function* theFunction = context.builder.GetInsertBlock()->getParent();

    BasicBlock *block = BasicBlock::Create(context.llvmContext, "loop", theFunction);
    BasicBlock *after = BasicBlock::Create(context.llvmContext, "loop_cont", theFunction);
    BasicBlock *continue_block = llvm::BasicBlock::Create(context.llvmContext, "continue_cont", theFunction);

    // execute the initial
    if( this->getInitialExpr() )
        this->getInitialExpr()->codegen(context);

    Value* condValue = ConstantInt::get(Type::getInt32Ty(context.llvmContext), 1 , true);
    if(this->getJudgeExpr()){
        condValue = this->getJudgeExpr()->codegen(context);
    }
    condValue = context.CastToBoolean(context, condValue);

    // fall to the block
    context.builder.CreateCondBr(condValue, block, after);

    context.builder.SetInsertPoint(block);

    context.pushBlock(block);
    context.currentBlock()->loopBreak = after;
    context.currentBlock()->loopContinue = continue_block;
    this->getBlock()->codegen(context);
    context.popBlock();
    context.builder.CreateBr(continue_block);

    // do increment
    context.builder.SetInsertPoint(continue_block);
    if( this->getUpdateExpr() ){
        std::cout<<"Update expression"<<std::endl;
        this->getUpdateExpr()->codegen(context);
    }

    // execute the again or stop
    condValue = ConstantInt::get(Type::getInt32Ty(context.llvmContext), 1 , true);
    if(this->getJudgeExpr()){
        condValue = this->getJudgeExpr()->codegen(context);
    }
    condValue = context.CastToBoolean(context, condValue);
    context.builder.CreateCondBr(condValue, block, after);

    // insert the after block
    // theFunction->getBasicBlockList().push_back(after);
    context.builder.SetInsertPoint(after);
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
        std::cout<<"generate continue"<<std::endl;
        if (context.currentBlock()->loopContinue == nullptr) {
            LogError("Cannot use continue statement out of loops");
            return nullptr;
        }
        context.builder.CreateBr(context.currentBlock()->loopContinue);
        return nullptr;
    }
    else if(type=="break"){
        std::cout<<"generate break"<<std::endl;
        if (context.currentBlock()->loopBreak == nullptr) {
            LogError("Cannot use break statement out of loops");
            return nullptr;
        }
        context.builder.CreateBr(context.currentBlock()->loopBreak);

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

