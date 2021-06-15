#include "AstProg.h"

//============================================
AstProgram::AstProgram() 
            :AstBase("program"){}
void AstProgram::addExternalExpr(AstExternalExpr* extExpr){
    externalExpr.push_back(extExpr);
}
std::vector<AstExternalExpr *> AstProgram::getExternalExpr(){
    return externalExpr;
}

//============================================
AstExternalExpr::AstExternalExpr(AstFunDef* funDef, AstDeclaration* declaration)
                : AstBase("external_expression"),funDef(funDef),declaration(declaration){}
AstFunDef* AstExternalExpr::getFunDef() const{
    return funDef;
}
AstDeclaration* AstExternalExpr::getDeclaration() const{
    return declaration;
}

//====================================================
AstFunDef::AstFunDef(AstSpec* spec, AstPointer* pointer, string funcName, AstParamList* paramList, AstCompoundStmt* compound_statement,bool isExtern)
        :AstBase("function_definition"), funcName(funcName), astParamList(paramList), compound_statement(compound_statement), isExtern(isExtern){

    returnType = spec->getLabel();
    if(pointer!= nullptr)
        returnPtrLevel = pointer->getStarNum();
    else returnPtrLevel = 0;

    this->paramList = paramList->getParamList();
}
int AstFunDef::getReturnPtrLevel(){
    return returnPtrLevel;
}

string AstFunDef::getReturnType(){
    return returnType;
}

string AstFunDef::getFuncName(){
    return funcName;
}

std::vector<std::pair<AstSpec*, AstDeclarator*> > AstFunDef::getParamList(){
    return paramList;
}

AstCompoundStmt* AstFunDef::getCompound_statement() const{
    return compound_statement;
}

AstParamList *AstFunDef::getAstParamList(){
    return this->astParamList;
}

bool AstFunDef::getIsExtern() const{
    return this->isExtern;
}