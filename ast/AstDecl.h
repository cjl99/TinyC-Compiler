//
// Created by Jialiang Chen on 2021/5/24.
//

#ifndef OUR_C_COMPILER_ASTDECL_H
#define OUR_C_COMPILER_ASTDECL_H

#include "AstBase.h"
#include "AstType.h"

class AstDecl;
class AstDeclaration;
class AstDeclarationList;
class AstInitDeclList;
class AstInitDeclarator;
class AstDeclarator;
class AstStructDeclList;
class AstStructDecl;
class AstStructDeclaratorList;
class AstStructDeclarator;
class AstDirectDeclarator;
class AstPointer;
class AstParamDecl;
class AstParamList;
class AstParamTypeList;
class AstIdList;
class AstAbsDeclarator;
class AstDirectAbsDeclarator;
class AstInit;
class AstInitList;
class AstPointer;
class AstTypeName;

class AstTypeName: public AstBase{
public:
    AstTypeName(AstSpecList* specQualList, AstAbsDeclarator* abstractDeclarator);
    AstSpecList* getSpecList();
    AstAbsDeclarator* getAbstractDeclarator();
private:
    AstSpecList* specQualList;
    AstAbsDeclarator* abstractDeclarator;
};


class AstDecl: public AstBase {
public:
    AstDecl(std::string nodeType);
};

class AstDeclaration: public AstDecl {
public:
    AstDeclaration(AstSpecList* astSpecList1);
    AstDeclaration(AstSpecList* astSpecList1, AstInitDeclList* astInitDeclList1);
    AstSpecList* getAstSpecList(); 
    AstInitDeclList* getAstInitDeclList();
private:
    AstSpecList* astSpecList = nullptr;
    AstInitDeclList* astInitDeclList = nullptr;
};

class AstDeclarationList: public AstDecl{
public:
    AstDeclarationList();
    void addDeclaration(AstDeclaration* astDeclaration);
    std::vector<AstDeclaration *>& getAstDeclartionList();
private:
    std::vector<AstDeclaration *> astDeclarationList;
};

class AstInitDeclList: public AstDecl {
public:
    AstInitDeclList();
    void addInitDeclarator(AstInitDeclarator* astInitDeclarator);
    std::vector<AstInitDeclarator *>& getAstInitDeclList();
private:
    std::vector<AstInitDeclarator *> astInitDeclList;
};

class AstInitDeclarator: public AstDecl {
public:
    AstInitDeclarator(AstDeclarator* astDeclarator1);
    AstInitDeclarator(AstDeclarator* astDeclarator1, AstInit* astInitializer1);
    AstDeclarator* getAstDeclarator() const;
    AstInit* getAstInitializer() const;

private:
    AstDeclarator* astDeclarator = nullptr;
    AstInit* astInitializer = nullptr;
};

class AstDeclarator: public AstDecl {
public:
    AstDeclarator(AstPointer* astPointer1, AstDirectDeclarator* astDirectDeclarator1);
    AstDeclarator(AstDirectDeclarator* astDirectDeclarator1);
    AstDirectDeclarator* getAstDirectDeclarator();
    AstPointer* getAstPointer();   
    bool hasPointer = false;
private:
    AstDirectDeclarator* astDirectDeclarator = nullptr;
    AstPointer* astPointer = nullptr;
};

class AstPointer: public AstBase{
public:
    AstPointer(std::string star, AstSpecList *type_qual_list, AstPointer* child_pointer);
    std::string getStar();
    AstSpecList *getTypeQualList();
    AstPointer *getAstPointerChild();

private:
    std::string star;
    AstSpecList* type_qualifier_list;
    AstPointer *pointer_child;
};

class AstStructDeclList: public AstDecl {
public:
    AstStructDeclList();
    void addStructDecl(AstStructDecl* astStructDecl1);
    std::vector<AstStructDecl *> getAstStructDeclList();
private:
    std::vector<AstStructDecl *> astStructDeclList;
};

class AstStructDecl: public AstDecl {
public:
    AstStructDecl(AstSpecList* astSpecList1, AstStructDeclaratorList* astStructDeclaratorList1);

private:
    AstSpecList* astSpecList = nullptr;
    AstStructDeclaratorList* astStructDeclaratorList = nullptr;
};


class AstStructDeclaratorList: public AstDecl {
public:
    AstStructDeclaratorList();
    void addStructDeclarator(AstStructDeclarator* astStructDeclarator1);

private:
    std::vector<AstStructDeclarator *> astStructDeclaratorList;
};


class AstStructDeclarator: public AstDecl {
public:
    AstStructDeclarator(int type, void *ptr );
    AstStructDeclarator(int type, AstDeclarator* astDeclarator1, void* astConstExpr1);
private:
    int type = 0; // 1:only declarator 2:only constant expr 3:both
    AstDeclarator* astDeclarator = nullptr;
    void* astConstExpr = nullptr;
};

class AstDirectDeclarator: public AstDecl {
public:
    AstDirectDeclarator(std::string id, AstDeclarator *astDeclarator);
    void addToDirectDecl(int type, void *ptr);
    std::vector<std::pair<int, void *> >& getAstDirectDeclarator();
    std::string getIdentifier();
    AstDeclarator *getAstDeclarator();   
private:
    std::string identifier;
    AstDeclarator *astDeclarator;
    std::vector<std::pair<int, void *> > astDirectDeclarator;
};

class AstParamDecl: public AstDecl {
public:
    AstParamDecl(AstSpecList* astSpecList);
    AstParamDecl(AstSpecList* astSpecList, int type, void* ptr);
    
    AstSpecList *getAstSpecList();
    int getType();
    void *getPtr();
private:
    AstSpecList* declSpec; // declaration_specifiers
    // type =0 <--> null
    // type==1 <--> AstDeclarator*
    // type==2 <--> Ast_abstract_declarator*
    int type;
    void *ptr;
};

class AstParamList: public AstDecl {
public:
    AstParamList();
    void addParamDecl(AstParamDecl* astParamDecl);
    std::vector<AstParamDecl *> getParamList();
private:
    std::vector<AstParamDecl *> paramList;
};

class AstParamTypeList: public AstDecl {
public:
    AstParamTypeList(int type, AstParamList* paramList);
    int getType();
    AstParamList *getAstParamList();
private:
    int type = 0;
    // type = 0 parameter_list
    // type = 1 parameter_list ',' ELLIPSIS
    AstParamList* paramList;
};

class AstIdList: public AstDecl {
public:
    AstIdList();
    void addId(std::string id);
    std::vector<std::string> getIdList();
private:
    std::vector<std::string> idList;
};

class AstAbsDeclarator: public AstDecl {
public:
    AstAbsDeclarator(AstPointer* pointer, AstDirectAbsDeclarator* directAbsDeclarator);
    AstPointer* getAstPointer();
    AstDirectAbsDeclarator* getAstDirectAbsDeclarator();
private:
    AstPointer* pointer;
    AstDirectAbsDeclarator* directAbsDeclarator;
};


class AstDirectAbsDeclarator: public AstDecl {
public:
    AstDirectAbsDeclarator(int type);
    AstDirectAbsDeclarator(int type, void *ptr1);
    AstDirectAbsDeclarator(int type, void* ptr1, void *ptr2);

    int getType();
    void* getPtr1();
    void* getPtr2();
private:
    // type=1   (' ptr1= abstract_declarator ')'
    // type=2   [] ptr1=ptr2=null
    // type=6   () ptr1=ptr2=null
    // type=3   [ ptr1=constant_expression ]
    // type=4   ptr1=direct_abstract_declarator []
    // type=5   ptr1=direct_abstract_declarator [ ptr2 = constant_expression ]
    // type=7   ( ptr1=parameter_type_list )
    // type=8   ptr1=direct_abstract_declarator' ()
    // type=9   ptr1=direct_abstract_declarator [ ptr2 = parameter_type_list ]
    int type = 0;
    void *ptr1 = nullptr;
    void *ptr2 = nullptr;
};

class AstInit: public AstDecl {
public:
    AstInit(int type, void * ptr);
    int getType();
    void *getPtr();
private:
    int type = 0;
    // type = 0 <--> assignment_expression
    // type = 1 <--> '{' initializer_list '}'
    // type = 2 <--> '{' initializer_list ',' '}'
    void *ptr = nullptr;
};

class AstInitList: public AstDecl {
public:
    AstInitList();
    void addInit(AstInit* initializer);
    std::vector<AstInit* > getInitList();
private:
    std::vector<AstInit* > initializerList;
};


#endif //OUR_C_COMPILER_ASTDECL_H
