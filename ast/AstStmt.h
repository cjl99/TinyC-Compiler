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
    virtual llvm::Value* codegen(CodeGen &context) override;
};

class AstCompoundStmt: public AstNonLabelStmt{
private:
    AstDeclarationList* astDeclarationList;
    AstStmtList* astStmtList;

public:
    AstCompoundStmt(AstDeclarationList* astDeclarationList, AstStmtList* astStmtList);
    AstDeclarationList* getAstDeclarationList();
    AstStmtList* getAstStmtList();
    virtual llvm::Value* codegen(CodeGen &context) override;
};

class AstStmt: public AstNonLabelStmt{
private:
    AstNonLabelStmt *stmt;
    int type;
public:
    AstStmt(int type, AstNonLabelStmt* stmt);
    int getType();
    AstNonLabelStmt* getStmt();
    virtual llvm::Value* codegen(CodeGen &context) override;

};

class AstStmtList: public AstNonLabelStmt {
private:
    vector<AstStmt *> stmt_list;

public:
    AstStmtList();

    void addStmt(AstStmt *);

    std::vector<AstStmt *> getStmtList();
};

class AstExprStmt: public AstNonLabelStmt{
private:
    AstExpression *expr;
public:
    AstExprStmt(AstExpression *expr);

    AstExpression* getExpr();

    virtual llvm::Value* codegen(CodeGen &context) override;
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
    virtual llvm::Value* codegen(CodeGen &context) override;
};

class AstIterStmt: public AstNonLabelStmt{
private:
    AstExpression *initialExpr;
    AstExpression *judgeExpr;
    AstExpression *updateExpr;
    AstStmt *block;
    int type;

public:
    AstIterStmt(int type, AstExpression *initialExpr, AstExpression *judgeExpr, AstExpression *updateExpr, AstStmt *block);
    AstExpression *getInitialExpr() const;
    AstExpression *getJudgeExpr() const;
    AstExpression *getUpdateExpr() const;
    AstStmt *getBlock() const;
    int getType();

    virtual llvm::Value* codegen(CodeGen &context) override;

};

class AstJmpStmt: public AstNonLabelStmt{
private:
    string type;
    AstExpression *expr;

public:
    AstJmpStmt(string type, AstExpression *expr);
    string getType() const;
    AstExpression *getExpr() const;

    virtual llvm::Value* codegen(CodeGen &context) override;
};

#endif
