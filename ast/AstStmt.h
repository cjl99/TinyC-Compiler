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

    llvm::Value* codeGen(CodeGen &context);
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
    AstExpression *expr;
public:
    AstExprStmt(AstExpression *expr);

    AstExpression* getExpr();

    llvm::Value* codeGen(CodeGenContext &context);
};

class AstSelectStmt: public AstNonLabelStmt {
private:
    AstExpression *expr;
    AstStmt *thenClause;
    AstStmt *elseClause;

public:
    AstSelectStmt(AstExpression *expr, AstStmt *thenClause, AstStmt *elseClause= nullptr);

    AstExpression *getExpr() const;

    AstStmt *getThenClause() const;

    AstStmt *getElseClause() const;

    llvm::Value* codeGen(CodeGenContext &context);

};

class AstIterStmt: public AstNonLabelStmt{
private:
    AstExpression *initialExpr;
    AstExpression *judgeExpr;
    AstExpression *updateExpr;
    AstStmt *block;

public:
    AstIterStmt(AstExpression *initialExpr, AstExpression *judgeExpr, AstExpression *updateExpr, AstStmt *block);

    AstExpression *getInitialExpr() const;

    AstExpression *getJudgeExpr() const;

    AstExpression *getUpdateExpr() const;

    AstStmt *getBlock() const;

    llvm::Value* codeGen(CodeGenContext &context);

};

class AstJmpStmt: public AstNonLabelStmt{
private:
    string type;
    AstExpression *expr;

public:
    AstJmpStmt(string type, AstExpression *expr);

    string getType() const;

    AstExpression *getExpr() const;

    llvm::Value* codeGen(CodeGenContext &context);
};

#endif
