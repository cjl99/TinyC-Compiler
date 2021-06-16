//
// Created by Jialiang Chen on 2021/5/24.
//

#include "AstDecl.h"

AstDecl::AstDecl(std::string nodeType) :AstBase(nodeType){}
llvm::Value* AstDecl::codegen(CodeGen &context) {
    return nullptr;
}

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

//===================AstDeclartionList======================
AstDeclarationList::AstDeclarationList(): AstDecl("declaration_list"){}

void AstDeclarationList::addDeclaration(AstDeclaration* declaration){
    this->declarationList.push_back(declaration);
}

std::vector<AstDeclaration*>& AstDeclarationList::getDeclarationVector(){
    return this->declarationList;
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
AstDeclarator * AstInitDeclarator::getDeclarator() {
    return this->astDeclarator;
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
void AstDirectDeclarator::addArraySize(std::string size) {
    int num = stoi(size, nullptr, 10);
    this->arraySize.push_back(num);
}
void AstDirectDeclarator::addIdList(AstIdList *id_list) {
    this->idList.push_back(id_list);
}
std::vector<int>& AstDirectDeclarator::getArraySize() {
    return this->arraySize;
}
std::vector<AstIdList *>& AstDirectDeclarator::getIdList() {
    return this->idList;
}
std::string AstDirectDeclarator::getIdentifier() {
    return this->identifier;
}


// AstPointer
AstPointer::AstPointer()
: AstDecl("pointer")
{
    this->starNum = 1;
}
void AstPointer::addOneStar() {
    this->starNum += 1;
}
int AstPointer::getStarNum() {
    return this->starNum;
}
std::string AstPointer::getStars() {
    std::string str = "";
    for(int i=0; i<starNum; ++i) {
        str += "*";
    }
    return str;
}

// AstParamList;
AstParamList::AstParamList(bool empty)
: AstDecl("parameter_list")
{
    this->isempty = empty;
}
bool AstParamList::isEmpty() {
    return this->isempty;
}
void AstParamList::addParam(AstSpec *astSpec, AstDeclarator *astDeclarator) {
    this->astParamList.push_back(std::make_pair(astSpec, astDeclarator));
}
std::vector<std::pair<AstSpec *, AstDeclarator *>> AstParamList::getParamList() {
    return this->astParamList;
}

//==============================================
AstTypeName::AstTypeName(AstSpec *spec, AstPointer *pointer) : AstDecl("type_name"){
    type = spec->getLabel();
    if(pointer!= nullptr)
        ptrLevel = pointer->getStarNum();
    else ptrLevel = 0;
}

std::string AstTypeName::getType(){
    return type;
}

int AstTypeName::getPtrLevel(){
    return ptrLevel;
}

//==============================================
AstIdList::AstIdList(): AstDecl("identifier_list"){}

void AstIdList::addId(std::string id){
    identifiers.push_back(id);
}

std::vector<std::string> AstIdList::getIdentifiers(){
    return identifiers;
}