#include "AstStmt.h"

AstNonLabelStmt::AstNonLabelStmt(std::string nodeType)
                :AstBase(nodeType){}

// ===============================================

AstStmt:: AstStmt(AstBase* stmt)
        : AstBase("statement"), stmt(stmt){}

AstBase * AstStmt::getStmt() const{
    return stmt;
}

// ===============================================
AstStmtList:: AstStmtList()
        :AstNonLabelStmt("statement_list"){}

void AstStmtList:: addStmt(AstStmt * stmt){
    stmt_list.push_back(stmt);
}

const std::vector<AstStmt *> & AstStmtList::getStmtList() const{
    return stmt_list;
}
// ===============================================

 AstCompoundStmt::AstCompoundStmt(AstDeclarationList* astDeclarationList,AstStmtList* astStmtList)
                :AstNonLabelStmt("compound_statement"),astDeclarationList(astDeclarationList), astStmtList(astStmtList) {

                }

AstDeclarationList* AstCompoundStmt::getAstDeclarationList() const{
    return astDeclarationList;
}

AstStmtList* AstCompoundStmt::getAstStmtList() const{
    return astStmtList;
}

// ===============================================
AstExprStmt::AstExprStmt(AstExpr *expr)
            :AstNonLabelStmt("expression_statement"), expr(expr){}

AstExpr* AstExprStmt::getExpr(){
    return expr;
}

// ===============================================
AstSelectStmt(AstExpr *expr, AstStmt *thenClause, AstStmt *elseClause)
            :AstNonLabelStmt("selection_statement"),expr(expr), thenClause(thenClause), elseClause(elseClause){}

AstExpr *AstSelectStmt::getExpr() const{
    return expr;
}

AstStmt *AstSelectStmt::getThenClause() const{
    return thenClause;
}

AstStmt *AstSelectStmt::getElseClause() const{
    return elseClause;
}

// ===============================================
AstIterStmt::AstIterStmt(AstExpr *initialExpr, AstExpr *judgeExpr, AstExpr *updateExpr, AstStmt *block)
            :AstNonLabelStmt("iteration_statement"),  block(block), initialExpr(initialExpr), judgeExpr(judgeExpr), updateExpr(updateExpr){}

AstExpr *AstIterStmt::getInitialExpr() const{
    return initialExpr;
}

AstExpr *AstIterStmt::getJudgeExpr() const{
    return judgeExpr;
}

AstExpr *AstIterStmt::getUpdateExpr() const{
    return initialExpr;
}

AstStmt *AstIterStmt::getBlock() const{
    return block;
}

// ===============================================
AstJmpStmt::AstJmpStmt(string type, AstExpr *expr)
        :AstNonLabelStmt("jump_statement"), type(type), expr(expr){}

string AstJmpStmt::getType() const{
    return type;
}

AstExpr *AstJmpStmt::getExpr() const{
    return expr;
}