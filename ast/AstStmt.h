#ifndef OCC_AST_STMT_H
#define OCC_AST_STMT_H
#include <string>
#include <tuple>

#include "AstBase.h"
#include "AstDecl.h"
#include "AstExpr.h"

using namespace std;

/* =======unfinished=======
** compound_statement
** declaration_list
*/

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

class AstLabelStmt : public AstBase{
private:
    string label;
    AstStmt *stmt;
    AstCondiExpr *constExpr;
public:
    AstLabelStmt(AstStmt *stmt, string label, AstCondiExpr *constExpr = nullptr);

    const std::string &getLabel() const;

    AstCondiExpr *getAstCondiExpr() const;
    AstStmt *getStmt() const;
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

class AstCompoundStmt: public AstNonLabelStmt{
private:
    AstDeclarationList* astDeclarationList;
    AstStmtList* astStmtList;

public:
    AstCompoundStmt(AstDeclarationList* astDeclarationList, AstStmtList* astStmtList);

    AstDeclarationList* getAstDeclarationList() const;

    AstStmtList* getAstStmtList() const;
    
};

class AstSelectStmt: public AstNonLabelStmt {
private:
    AstExprList *expr;
    AstStmt *stmt;
    string type;
    AstStmt *else_clause;

public:
    AstSelectStmt(AstExprList *, AstStmt*, string, AstStmt *else_clause);

    AstExprList *getExpr() const;

    AstStmt *getStmt() const;

    AstStmt *getElseClause() const;

    string getIfOrSwitch() const;
};

class AstIterStmt: public AstNonLabelStmt{
private:
    AstExprList *expr1;
    AstExprList *expr2;
    AstExprList *expr3;
    AstStmt *stmt;
    string type;

public:
    AstIterStmt(string, AstStmt*, AstExprList *, AstExprList *, AstExprList *);

    AstExprList *getExpr1() const;

    AstExprList *getExpr2() const;

    AstExprList *getExpr3() const;

    AstStmt *getStmt() const;

    string getType() const;
};

class AstJmpStmt: public AstNonLabelStmt{
private:
    string type;
    string id;
    AstExprList *expr;

public:
    AstJmpStmt(string type, string id, AstExprList *expr);

    string getType() const;

    string getId() const;

    AstExprList *getExpr() const;
};

#endif
