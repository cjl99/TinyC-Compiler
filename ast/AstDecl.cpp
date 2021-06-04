//
// Created by Jialiang Chen on 2021/5/24.
//

#include "AstDecl.h"

AstTypeName::AstTypeName(AstSpecList* specQualList, AstAbsDeclarator* abstractDeclarator)
            :AstBase("type_name")
{
    this->specQualList = specQualList;
    this->abstractDeclarator = abstractDeclarator;
}

AstSpecList* AstTypeName::getSpecList() {
    return this->specQualList;
}

AstAbsDeclarator* AstTypeName::getAbstractDeclarator() {
    return  this->abstractDeclarator;
}

AstDecl::AstDecl(std::string nodeType)
        :AstBase(nodeType){}

AstDeclaration::AstDeclaration(AstSpecList *astSpecList1) 
                :AstDecl("declaration")
{
    this->astSpecList = astSpecList1;
}

AstDeclaration::AstDeclaration(AstSpecList *astSpecList1, AstInitDeclList *astInitDeclList1) 
                :AstDecl("declaration")
{
    this->astSpecList = astSpecList1;
    this->astInitDeclList = astInitDeclList1;
}

AstSpecList* AstDeclaration::getAstSpecList() {
    return this->astSpecList;
}
AstInitDeclList* AstDeclaration::getAstInitDeclList(){
    return this->astInitDeclList;
}

AstDeclarationList::AstDeclarationList()
                    :AstDecl("declaration_list"){}
void AstDeclarationList::addDeclaration(AstDeclaration* astDeclaration){
    astDeclarationList.push_back(astDeclaration);
}
std::vector<AstDeclaration *>& AstDeclarationList::getAstDeclartionList(){
    return this->astDeclarationList;
}
AstInitDeclList::AstInitDeclList() 
                :AstDecl("init_declarator_list"){}

void AstInitDeclList::addInitDeclarator(AstInitDeclarator *astInitDeclarator) {
    this->astInitDeclList.push_back(astInitDeclarator);
}

std::vector<AstInitDeclarator *>& AstInitDeclList::getAstInitDeclList() {
    return this->astInitDeclList;
}


AstInitDeclarator::AstInitDeclarator(AstDeclarator *astDeclarator1) 
                    :AstDecl("init_declarator")
{
    this->astDeclarator = astDeclarator1;
}

AstInitDeclarator::AstInitDeclarator(AstDeclarator *astDeclarator1, AstInit *astInitializer1) 
                    :AstDecl("init_declarator")
{
    this->astDeclarator = astDeclarator1;
    this->astInitializer = astInitializer1;
}

AstDeclarator* AstInitDeclarator::getAstDeclarator() const {
    return this->astDeclarator;
}

AstInit* AstInitDeclarator::getAstInitializer() const {
    return this->astInitializer;
}

AstStructDeclList::AstStructDeclList() 
                :AstDecl("struct_declaration_list"){}

void AstStructDeclList::addStructDecl(AstStructDecl *astStructDecl1) {
    this->astStructDeclList.push_back(astStructDecl1);
}

std::vector<AstStructDecl *> AstStructDeclList::getAstStructDeclList() {
    return this->astStructDeclList;
}

AstStructDecl::AstStructDecl(AstSpecList *astSpecList1, AstStructDeclaratorList *astStructDeclaratorList1) 
                :AstDecl("struct_declaration")
{
    this->astSpecList = astSpecList1;
    this->astStructDeclaratorList = astStructDeclaratorList1;
}

AstAbsDeclarator::AstAbsDeclarator(AstPointer* pointer, AstDirectAbsDeclarator* directAbsDeclarator) 
                :AstDecl("abstract_declarator")
{
    this->pointer = pointer;
    this->directAbsDeclarator = directAbsDeclarator;
}

AstPointer* AstAbsDeclarator::getAstPointer() {
    return this->pointer;
}
AstDirectAbsDeclarator* AstAbsDeclarator::getAstDirectAbsDeclarator()  {
    return this->directAbsDeclarator;
}

AstStructDeclaratorList::AstStructDeclaratorList() 
                        :AstDecl("struct_declarator_list"){}

void AstStructDeclaratorList::addStructDeclarator(AstStructDeclarator *astStructDeclarator1) {
    this->astStructDeclaratorList.push_back(astStructDeclarator1);
}

AstStructDeclarator::AstStructDeclarator(int type, void *ptr) 
                    :AstDecl("struct_declarator")
{
    if(type==1) {
        this->type = 1;
        this->astDeclarator = (AstDeclarator *)ptr;
    }
    else if(type==2) {
        this->type = 2;
        this->astConstExpr = ptr;
    }
    else {
        // error
        std::cout << "AstStructDeclarator run type!" << std::endl;
    }
}

AstStructDeclarator::AstStructDeclarator(int type, AstDeclarator* astDeclarator1,
                                         void *astConstExpr1) 
                    :AstDecl("struct_declarator")
{
    if(type==3) {
        this->type = type;
        this->astDeclarator = astDeclarator1;
        this->astConstExpr = astConstExpr1;
    }
}

AstDeclarator::AstDeclarator(AstDirectDeclarator *astDirectDeclarator1) 
                :AstDecl("declarator")
{
    this->hasPointer = false;
    this->astDirectDeclarator = astDirectDeclarator1;
}

AstDeclarator::AstDeclarator(AstPointer *astPointer1, AstDirectDeclarator *astDirectDeclarator1) 
                :AstDecl("declarator")
{
    this->hasPointer = true;
    this->astDirectDeclarator = astDirectDeclarator1;
    this->astPointer = astPointer1;
}

AstDirectDeclarator* AstDeclarator::getAstDirectDeclarator() {
    return this->astDirectDeclarator;
}
AstPointer* AstDeclarator::getAstPointer() {
    return this->astPointer;
}

std::string AstDirectDeclarator::getIdentifier() {
    return this->identifier;
}
AstDeclarator *AstDirectDeclarator::getAstDeclarator() {
    return this->astDeclarator;
}  

AstDirectDeclarator::AstDirectDeclarator(std::string id, AstDeclarator *astDeclarator) :AstDecl("direct_declarator")
{
    this->identifier = id;
    this->astDeclarator = astDeclarator;
}

void AstDirectDeclarator::addToDirectDecl(int type, void *ptr) {
    this->astDirectDeclarator.push_back(std::make_pair(type, ptr));
}

AstDirectAbsDeclarator::AstDirectAbsDeclarator(int type) :AstDecl("direct_abstract_declarator")
{
    this->type = type;
    this->ptr1 = this->ptr2 = nullptr;
}

AstDirectAbsDeclarator::AstDirectAbsDeclarator(int type, void *ptr1) :AstDecl("direct_abstract_declarator")
{
    this->type = type;
    this->ptr1 = ptr1;
    this->ptr2 = nullptr;
}

AstDirectAbsDeclarator::AstDirectAbsDeclarator(int type, void *ptr1, void *ptr2) :AstDecl("direct_abstract_declarator")
{
    this->type = type;
    this->ptr1 = ptr1;
    this->ptr2 = ptr2;
}

int AstDirectAbsDeclarator::getType() {
    return this->type;
}
void* AstDirectAbsDeclarator::getPtr1() {
    return this->ptr1;
}
void* AstDirectAbsDeclarator::getPtr2() {
    return this->ptr2;
}

std::vector<std::pair<int, void *> >& AstDirectDeclarator::getAstDirectDeclarator() {
    return this->astDirectDeclarator;
}

AstParamDecl::AstParamDecl(AstSpecList *astSpecList) :AstDecl("parameter_declaration")
{
    this->declSpec = astSpecList;
    this->type = 0;
    this->ptr = nullptr;
}

AstParamDecl::AstParamDecl(AstSpecList *astSpecList, int type, void *ptr) :AstDecl("parameter_declaration")
{
    this->declSpec = astSpecList;
    this->type = type;
    this->ptr = ptr;
}
AstSpecList *AstParamDecl::getAstSpecList() {
    return this->declSpec;
}
int AstParamDecl::getType() {
    return this->type;
}
void* AstParamDecl::getPtr() {
    return this->ptr;
}
AstParamList::AstParamList() 
            :AstDecl("parameter_list"){}

void AstParamList::addParamDecl(AstParamDecl *astParamDecl) {
    this->paramList.push_back(astParamDecl);
}

std::vector<AstParamDecl *> AstParamList::getParamList() {
    return this->paramList;
}

AstParamTypeList::AstParamTypeList(int type, AstParamList *paramList) 
                :AstDecl("parameter_list")
{
    this->type = type;
    this->paramList = paramList;
}

int AstParamTypeList::getType() {
    return this->type;
}
AstParamList* AstParamTypeList::getAstParamList() {
    return this->paramList;
}

AstIdList::AstIdList() 
            :AstDecl("identifier_list"){}

std::vector<std::string> AstIdList::getIdList() {
    return this->idList;
}

void AstIdList::addId(std::string id) {
    this->idList.push_back(id);
}

AstInitList::AstInitList() 
            :AstDecl("initializer_list"){}

void AstInitList::addInit(AstInit *initializer) {
    this->initializerList.push_back(initializer);
}

std::vector<AstInit* > AstInitList::getInitList() {
    return this->initializerList;
}

AstInit::AstInit(int type, void *ptr) :AstDecl("initializer")
{
    this->type = type;
    this->ptr = ptr;
}
int AstInit::getType() {
    return this->type;
}
void* AstInit::getPtr() {
    return this->ptr;
}

AstPointer::AstPointer(std::string star, AstSpecList *type_qual_list, AstPointer* child_pointer)
    : AstBase("pointer")
{
    this->star = star;
    this->type_qualifier_list = type_qual_list;
    this->pointer_child = child_pointer;
}

AstSpecList * AstPointer::getTypeQualList() {
    return this->type_qualifier_list;
}

AstPointer * AstPointer::getAstPointerChild() {
    return this->pointer_child;
}

std::string AstPointer::getStar() {
    return this->star;
}