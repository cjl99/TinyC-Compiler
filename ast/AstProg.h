#ifndef _AST_PROG_H
#define _AST_PROG_H

#include "AstBase.h"
#include "AstDecl.h"
#include "AstStmt.h"
#include "AstType.h"

class AstProgram;
class AstExternalExpr;
class AstFunDef;

class AstProgram: public AstBase {
public:
    AstProgram();
    void addExternalExpr(AstExternalExpr* extExpr);
    std::vector<AstExternalExpr *> getExternalExpr();
private:
    std::vector<AstExternalExpr *> externalExpr;
};

class AstFunDef: public AstBase{
public:
    AstFunDef(AstCompoundStmt* compound_statement, AstDeclarator* declarator, AstDeclarationList* declarationList,  AstSpecList* declarationSpec);
    AstSpecList* getDeclarationSpec() const;
    AstDeclarator* getDeclarator() const;
    AstDeclarationList* getDeclarationList() const;
    AstCompoundStmt* getCompound_statement() const;
private:
    AstSpecList* declarationSpec;
    AstDeclarator* declarator;
    AstDeclarationList* declarationList;
    AstCompoundStmt* compound_statement;
    
};

class AstExternalExpr: public AstBase{
public:
    AstExternalExpr(AstFunDef* funDef, AstDeclaration* declaration);
    AstFunDef* getFunDef() const;
    AstDeclaration* getDeclaration() const;
private:
    AstFunDef* funDef;
    AstDeclaration* declaration;  
};
#endif