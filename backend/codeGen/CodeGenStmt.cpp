#include "CodeGen.h"
#include "../../ast/AstStmt.h"

llvm::Value* AstCompoundStmt::codegen(CodeGen &context) {
    std::cout << "Generate compound statement" << std::endl;
    // declaration list part
    AstDeclarationList *decl_list = this->getAstDeclarationList();
    if(decl_list) {
        std::vector<AstDeclaration *> decl_v = decl_list->getDeclarationVector();
        for (auto decl:decl_v) {
            decl->codegen(context);
        }
    }

    // stmt list part
    AstStmtList *stmtlist = this->getAstStmtList();

    if(stmtlist) {
        vector<AstStmt *> stmt_vec = stmtlist->getStmtList();
        for(auto stmt: stmt_vec) {
            int stmt_type = stmt->getType();
            switch (stmt_type) {
                case 1:
                    ((AstCompoundStmt *) stmt)->codegen(context);
                    break;
                case 2:
                    ((AstExprStmt *) stmt)->codegen(context);
                    break;
                case 3:
                    ((AstSelectStmt *) stmt)->codegen(context);
                    break;
                case 4:
                    ((AstIterStmt *) stmt)->codegen(context);
                    break;
                case 5:
                    ((AstJmpStmt *) stmt)->codegen(context);
                    break;
            }
        }
    }

    return nullptr;
    // vector<AstDeclaration *> decl_list = ->getDeclarationList();

    // vector<AstStmt *> stmtList = this->getAstStmtList()->getStmtList();


    // Function* theFunction = context.builder.GetInsertBlock()->getParent();


    // BasicBlock* basicBlock = BasicBlock::Create(context.llvmContext, "compoundStmt", theFunction);

    // context.builder.SetInsertPoint(basicBlock);


    // context.pushBlock(basicBlock);


    // for(auto decl : decl_list) {
    //     decl->codegen(context);
    // }
    // Value* last = nullptr;
    // for(auto stmt : stmtList){
    //     last = stmt->codegen(context);
    // }

    // context.popBlock();
    // return last;
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

