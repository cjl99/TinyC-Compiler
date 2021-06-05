//
// Created by Jialiang Chen on 2021/5/24.
//

#include "AstDecl.h"


AstDecl::AstDecl(std::string nodeType) :AstBase(nodeType){}

AstDeclaration::AstDeclaration(AstSpec* astSpec, AstInitDeclList* astInitDeclList) :AstDecl("declaration")
{
    this->astTypeSpec = astSpec;
    this->astInitDeclList = astInitDeclList;
}
AstSpec* AstDeclaration::getTypeSpec() {
    return this->astTypeSpec;
}
AstInitDeclList* AstDeclaration::getInitDeclList() {
    return this->astInitDeclList;
}

/* AstInitDeclList
 * */
AstInitDeclList::AstInitDeclList() :AstDecl("init_declarator_list") {}
std::vector<AstInitDeclarator *> & AstInitDeclList::getInitDeclList() {
    return this->astInitDeclList;
}
void AstInitDeclList::addInitDeclarator(AstInitDeclarator *astInitDeclarator) {
    this->astInitDeclList.push_back(astInitDeclarator);
}

//AstInitDeclarator
AstInitDeclarator::AstInitDeclarator(AstDeclarator *astDeclarator, AstInitializer *astInitializer)
: AstDecl("init_declarator")
{
    this->astInitializer = astInitializer;
    this->astDeclarator = astDeclarator;
}
bool AstInitDeclarator::hasEqual() {
    return astInitializer!=nullptr;
}
AstInitializer * AstInitDeclarator::getInitializer() {
    return this->astInitializer;
}
AstDeclarator * AstInitDeclarator::getInitDeclarator() {
    return this->astDeclarator;
}

// AstInitializer
AstInitializer::AstInitializer(AstExpression *astExpression, AstInitList *astInitList)
: AstDecl("initializer")
{
    this->astExpression = astExpression;
    this->astInitList = astInitList;
}
AstInitList * AstInitializer::getInitList() {
    return this->astInitList;
}
AstExpression * AstInitializer::getExpression() {
    return this->astExpression;
}

// AstInitList;
AstInitList::AstInitList() : AstDecl("initializer_list"){}
std::vector<AstInitializer *> & AstInitList::getInitializerList() {
    return this->astInitializerList;
}
void AstInitList::addInitializer(AstInitializer *astInitializer) {
    this->astInitializerList.push_back(astInitializer);
}

// AstDeclarator;
AstDeclarator::AstDeclarator(AstPointer *astPointer, AstDirectDeclarator *astDirectDeclarator)
: AstDecl("declarator")
{
    this->astPointer = astPointer;
    this->astDirectDeclarator = astDirectDeclarator;
}
bool AstDeclarator::hasPointer() {
    return this->astPointer!=nullptr;
}
AstDirectDeclarator * AstDeclarator::getDirectDeclarator() {
    return this->astDirectDeclarator;
}
AstPointer * AstDeclarator::getPointer() {
    return this->astPointer;
}

// AstDirectDeclarator;
AstDirectDeclarator::AstDirectDeclarator(std::string identifier)
: AstDecl("direct_declarator")
{
    this->identifier = identifier;
}

class AstPointer;
class AstParamList;