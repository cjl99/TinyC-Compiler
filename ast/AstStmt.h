#ifndef OCC_AST_STMT_H
#define OCC_AST_STMT_H
#include <string>
#include <tuple>

#include "AstBase.h"
#include "AstDecl.h"
#include "AstExpr.h"

using namespace std;

class AstNonLabelStmt;
class AstLabelStmt;
class AstStmt;
class AstStmtList;
class AstCompoundStmt;
class AstSelectStmt;
class AstIterStmt;
class AstJmpStmt;

class AstNonLabelStmt: public AstBase{
public:
    AstNonLabelStmt(std::string nodeType);
};

class AstCompoundStmt: public AstNonLabelStmt{
private:
    AstDeclarationList* astDeclarationList;
    AstStmtList* astStmtList;

public:
    AstCompoundStmt(AstDeclarationList* astDeclarationList, AstStmtList* astStmtList);

    AstDeclarationList* getAstDeclarationList() const;

    AstStmtList* getAstStmtList() const;

};

class AstStmt: public AstBase{
private:
    AstBase *stmt;

public:
    AstStmt(AstBase* stmt);
    AstBase *getStmt() const;
};

class AstStmtList: public AstNonLabelStmt {
private:
    vector<AstStmt *> stmt_list;

public:
    AstStmtList();

    void addStmt(AstStmt *);

    const std::vector<AstStmt *> &getStmtList() const;
};

class AstExprStmt: public AstNonLabelStmt{
private:
    AstExpr *expr;
public:
    AstExprStmt(AstExpr *expr);

    AstExpr* getExpr();

};

class AstSelectStmt: public AstNonLabelStmt {
private:
    AstExpr *expr;
    AstStmt *thenClause;
    AstStmt *elseClause;

public:
    AstSelectStmt(AstExpr *expr, AstStmt *thenClause, AstStmt *elseClause= nullptr);

    AstExpr *getExpr() const;

    AstStmt *getThenClause() const;

    AstStmt *getElseClause() const;

};

class AstIterStmt: public AstNonLabelStmt{
private:
    AstExpr *initialExpr;
    AstExpr *judgeExpr;
    AstExpr *updateExpr;
    AstStmt *block;

public:
    AstIterStmt(AstExpr *initialExpr, AstExpr *judgeExpr, AstExpr *updateExpr, AstStmt *block);

    AstExpr *getInitialExpr() const;

    AstExpr *getJudgeExpr() const;

    AstExpr *getUpdateExpr() const;

    AstStmt *getBlock() const;

};

class AstJmpStmt: public AstNonLabelStmt{
private:
    string type;
    AstExpr *expr;

public:
    AstJmpStmt(string type, AstExpr *expr);

    string getType() const;

    AstExpr *getExpr() const;
};

#endif
