#include "AstProg.h"

AstProgram::AstProgram() 
            :AstBase("program"){}
void AstProgram::addExternalExpr(AstExternalExpr* extExpr){
    externalExpr.push_back(extExpr);
}
std::vector<AstExternalExpr *> AstProgram::getExternalExpr(){
    return externalExpr;
}

AstFunDef::AstFunDef(AstCompoundStmt* compound_statement, AstDeclarator* declarator, AstDeclarationList* declarationList,  AstSpecList* declarationSpec)
            :AstBase("function")
{
    this->compound_statement = compound_statement;
    this->declarator = declarator;
    this->declarationList = declarationList;
    this->declarationSpec = declarationSpec;
}
AstSpecList* AstFunDef::getDeclarationSpec() const{
    return declarationSpec;
}
AstDeclarator* AstFunDef::getDeclarator() const{
    return declarator;
}
AstDeclarationList* AstFunDef::getDeclarationList() const{
    return declarationList;
}
AstCompoundStmt* AstFunDef::getCompound_statement() const{
    return compound_statement;
}

AstExternalExpr::AstExternalExpr(AstFunDef* funDef, AstDeclaration* declaration)
                : AstBase("external_expression"),funDef(funDef),declaration(declaration){}
AstFunDef* AstExternalExpr::getFunDef() const{
    return funDef;
}
AstDeclaration* AstExternalExpr::getDeclaration() const{
    return declaration;
}
