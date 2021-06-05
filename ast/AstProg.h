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
    Value* codeGen();
private:
    std::vector<AstExternalExpr *> externalExpr;
};

class AstExternalExpr: public AstBase{
public:
    AstExternalExpr(AstFunDef* funDef, AstDeclaration* declaration);
    AstFunDef* getFunDef() const;
    AstDeclaration* getDeclaration() const;
    Value* codeGen();
private:
    AstFunDef* funDef;
    AstDeclaration* declaration;
};


class AstFunDef: public AstBase{
public:
    AstFunDef(AstSpec* spec, AstPointer* pointer, string funcName, AstParamList* paramList, AstCompoundStmt* compound_statement);
    string getReturnType();
    string getFuncName();
    int getReturnPtrLevel();
    std::vector<std::pair<AstSpec*, AstDeclarator*> > getParamList();
    AstParamList *getAstParamList();
    AstCompoundStmt* getCompound_statement() const;
    Value* codeGen(CodeGen &context);
private:
    string returnType;
    int returnPtrLevel;
    string funcName;
    std::vector<std::pair<AstSpec*, AstDeclarator*> > paramList;
    AstParamList *astParamList;
    AstCompoundStmt* compound_statement;
};


#endif