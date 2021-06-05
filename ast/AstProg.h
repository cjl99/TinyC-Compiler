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

class AstExternalExpr: public AstBase{
public:
    AstExternalExpr(AstFunDef* funDef, AstDeclaration* declaration);
    AstFunDef* getFunDef() const;
    AstDeclaration* getDeclaration() const;
private:
    AstFunDef* funDef;
    AstDeclaration* declaration;
};

//-------------------Todo-----------------------------
class AstFunDef: public AstBase{
public:
    AstFunDef(string returnType, AstPointer* pointer, string funcName, AstParamList* paramList, AstCompoundStmt* compound_statement);
    string getReturnType();
    string getFuncName();
    std::vector<std::pair<string, string> > getParamList();
    AstCompoundStmt* getCompound_statement() const;
private:
    string returnType;
    string funcName;
    std::vector<std::pair<string, string> > paramList;
    AstCompoundStmt* compound_statement;
};


#endif