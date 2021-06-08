#include "AstStmt.h"

AstNonLabelStmt::AstNonLabelStmt(std::string nodeType)
                :AstBase(nodeType){}

llvm::Value* AstNonLabelStmt::codegen(CodeGen &context) {
    return nullptr;
}
// ===============================================

AstStmt:: AstStmt(int type, AstBase* stmt)
        : AstNonLabelStmt("statement"), type(type), stmt(stmt){}

AstBase * AstStmt::getStmt() const{
    return stmt;
}

int AstStmt::getType() {
    return type;
}

// ===============================================
AstStmtList:: AstStmtList()
        :AstNonLabelStmt("statement_list"){}

void AstStmtList:: addStmt(AstStmt * stmt){
    stmt_list.push_back(stmt);
}

std::vector<AstStmt *> & AstStmtList::getStmtList(){
    return stmt_list;
}
// ===============================================

 AstCompoundStmt::AstCompoundStmt(AstDeclarationList* astDeclarationList,AstStmtList* astStmtList)
                :AstNonLabelStmt("compound_statement"),astDeclarationList(astDeclarationList), astStmtList(astStmtList) {

                }

AstDeclarationList* AstCompoundStmt::getAstDeclarationList() const{
    return this->astDeclarationList;
}

AstStmtList* AstCompoundStmt::getAstStmtList() const{
    return this->astStmtList;
}

// ===============================================
AstExprStmt::AstExprStmt(AstExpression *expr)
            :AstNonLabelStmt("expression_statement"), expr(expr){}

AstExpression* AstExprStmt::getExpr(){
    return expr;
}

// ===============================================
AstSelectStmt::AstSelectStmt(AstExpression *expr, AstStmt *thenClause, AstStmt *elseClause)
            :AstNonLabelStmt("selection_statement"),expr(expr), thenClause(thenClause), elseClause(elseClause){}

AstExpression *AstSelectStmt::getExpr() const{
    return expr;
}

AstStmt *AstSelectStmt::getThenClause() const{
    return thenClause;
}

AstStmt *AstSelectStmt::getElseClause() const{
    return elseClause;
}

// ===============================================
AstIterStmt::AstIterStmt(int type, AstExpression *initialExpr, AstExpression *judgeExpr, AstExpression *updateExpr, AstStmt *block)
            :AstNonLabelStmt("iteration_statement"),  type(type), block(block), initialExpr(initialExpr), judgeExpr(judgeExpr), updateExpr(updateExpr){}

AstExpression *AstIterStmt::getInitialExpr() const{
    return initialExpr;
}

AstExpression *AstIterStmt::getJudgeExpr() const{
    return judgeExpr;
}

AstExpression *AstIterStmt::getUpdateExpr() const{
    return initialExpr;
}

AstStmt *AstIterStmt::getBlock() const{
    return block;
}

int AstIterStmt::getType() {
    return type;
}

// ===============================================
AstJmpStmt::AstJmpStmt(string type, AstExpression *expr)
        :AstNonLabelStmt("jump_statement"), type(type), expr(expr){}

string AstJmpStmt::getType() const{
    return type;
}

AstExpression *AstJmpStmt::getExpr() const{
    return expr;
}