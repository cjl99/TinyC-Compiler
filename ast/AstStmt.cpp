#include "AstStmt.h"

AstNonLabelStmt::AstNonLabelStmt(std::string nodeType)
                :AstBase(nodeType){}

// ===============================================

AstLabelStmt:: AstLabelStmt(AstStmt *stmt, string label, AstCondiExpr *constExpr)
            : AstBase("labeled_statement"), stmt(stmt), label(label), constExpr(constExpr){}

const string& AstLabelStmt:: getLabel() const{
    return label;
}

AstCondiExpr *AstLabelStmt::getAstCondiExpr() const{
    return constExpr;
}

AstStmt *AstLabelStmt:: getStmt() const{
    return stmt;
};

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

AstSelectStmt::AstSelectStmt(AstExprList *expr, AstStmt* stmt, string type, AstStmt *else_clause = nullptr)
            :AstNonLabelStmt("selection_statement"),expr(expr), stmt(stmt), type(type), else_clause(else_clause){}

AstExprList * AstSelectStmt::getExpr() const{
    return expr;
}

AstStmt * AstSelectStmt::getStmt() const{
    return stmt;
}

AstStmt * AstSelectStmt::getElseClause() const{
    return else_clause;
}

string AstSelectStmt::getIfOrSwitch() const{
    return type;
}

// ===============================================

AstIterStmt::AstIterStmt(string type, AstStmt* stmt, AstExprList *expr1, AstExprList *expr2= nullptr, AstExprList *expr3 = nullptr)
            : AstNonLabelStmt("iteration_statement"), type(type), stmt(stmt), expr1(expr1), expr2(expr2), expr3(expr3){}

AstExprList * AstIterStmt::getExpr1() const{
    return expr1;
}

AstExprList * AstIterStmt::getExpr2() const{
    return expr2;
}

AstExprList * AstIterStmt::getExpr3() const{
    return expr3;
}

AstStmt * AstIterStmt::getStmt() const{
    return stmt;
}

string AstIterStmt::getType() const{
    return type;
}

// ===============================================

AstJmpStmt::AstJmpStmt(string type, string id = "", AstExprList *expr = nullptr)
            :AstNonLabelStmt("jump_statement"), type(type),id(id), expr(expr){}

string AstJmpStmt::getType() const{
    return type;
}

string AstJmpStmt::getId() const{
    return id;
}

AstExprList *AstJmpStmt::getExpr() const{
    return expr;
}