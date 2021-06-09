#include "AstStmt.h"

AstNonLabelStmt::AstNonLabelStmt(std::string nodeType)
                :AstBase(nodeType){}

llvm::Value* AstNonLabelStmt::codegen(CodeGen &context) {
    return nullptr;
}
// ===============================================

AstStmt:: AstStmt(int type, AstNonLabelStmt* stmt)
        : AstNonLabelStmt("statement"), type(type), stmt(stmt){}

AstNonLabelStmt* AstStmt::getStmt() {
    return this->stmt;
}

int AstStmt::getType() {
    return this->type;
}

// ===============================================
AstStmtList:: AstStmtList()
        :AstNonLabelStmt("statement_list"){
            stmt_list = vector<AstStmt *>(); 
        }

void AstStmtList:: addStmt(AstStmt *stmt){
    stmt_list.push_back(stmt);
}

std::vector<AstStmt *> AstStmtList::getStmtList(){
    return this->stmt_list;
}

// compound stmt
AstCompoundStmt::AstCompoundStmt(AstDeclarationList* astDeclarationList, AstStmtList* astStmtList)
:AstNonLabelStmt("compound_statement") {
    this->astDeclarationList = astDeclarationList;
    this->astStmtList = astStmtList;
}

AstDeclarationList* AstCompoundStmt::getAstDeclarationList(){
    return this->astDeclarationList;
}

AstStmtList* AstCompoundStmt::getAstStmtList(){
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