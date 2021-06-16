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
class AstInitList;
class AstInitializer;
class AstDeclarator;
class AstDirectDeclarator;
class AstPointer;
class AstParamList;
class AstIdList;
class AstTypeName;

class AstDecl: public AstBase {
public:
    virtual llvm::Value* codegen(CodeGen &context) override;

    AstDecl(std::string nodeType);
};

class AstDeclaration: public AstDecl {
public:
    AstDeclaration(AstSpec* astSpec, AstInitDeclList* astInitDeclList);
    AstSpec* getTypeSpec(); 
    AstInitDeclList* getInitDeclList();
    virtual llvm::Value* codegen(CodeGen &context) override;
private:
    AstSpec* astTypeSpec;
    AstInitDeclList* astInitDeclList;
};

class AstDeclarationList: public AstDecl{
public:
    AstDeclarationList();
    void addDeclaration(AstDeclaration* declaration);
    
    std::vector<AstDeclaration*>& getDeclarationVector();
    // virtual llvm::Value* codegen(CodeGen &context) override;
private:
    std::vector<AstDeclaration*> declarationList;
};

class AstInitDeclList: public AstDecl {
public:
    AstInitDeclList();
    void addInitDeclarator(AstInitDeclarator* astInitDeclarator);
    std::vector<AstInitDeclarator *>& getInitDeclList();
private:
    std::vector<AstInitDeclarator *> astInitDeclList;
};

class AstInitDeclarator: public AstDecl {
public:
    AstInitDeclarator(AstDeclarator *astDeclarator, AstInitializer* astInitializer);
    AstDeclarator *getDeclarator();
    AstInitializer *getInitializer();
    bool hasEqual();

private:
    AstDeclarator *astDeclarator;
    AstInitializer *astInitializer;
};

class AstInitList: public AstDecl {
public:
    AstInitList();
    void addInitializer(AstInitializer *astInitializer);
    std::vector<AstInitializer *>& getInitializerList();

private:
    std::vector<AstInitializer *> astInitializerList;
};

class AstDeclarator: public AstDecl {
public:
    AstDeclarator(AstPointer* astPointer, AstDirectDeclarator* astDirectDeclarator);
    AstDirectDeclarator* getDirectDeclarator();
    AstPointer* getPointer();   
    bool hasPointer();

private:
    AstPointer* astPointer;
    AstDirectDeclarator* astDirectDeclarator;
};

class AstDirectDeclarator: public AstDecl {
public:
    AstDirectDeclarator(std::string identifier);
    std::string getIdentifier();
    void addArraySize(std::string size);
    void addIdList(AstIdList *id_list);
    std::vector<int>& getArraySize();
    std::vector<AstIdList *>& getIdList();

private:
    std::string identifier;
    std::vector<AstIdList *> idList;
    std::vector<int> arraySize;
};

class AstPointer: public AstDecl{
public:
    AstPointer();
    void addOneStar();
    int getStarNum();
    std::string getStars();

private:
    int starNum;
};

class AstParamList: public AstDecl {
public:
    AstParamList(bool empty);
    void addParam(AstSpec* astSpec, AstDeclarator *astDeclarator);
    std::vector<std::pair<AstSpec*, AstDeclarator*> > getParamList();
    bool isEmpty();
private:
    bool isempty;
    std::vector<std::pair<AstSpec*, AstDeclarator*>> astParamList;
};

class AstTypeName: public AstDecl{
public:
    AstTypeName(AstSpec *spec, AstPointer *pointer);
    std::string getType();
    int getPtrLevel();
private:
    std::string type;
    int ptrLevel;
};

class AstIdList: public AstDecl{
public:
    AstIdList();
    void addId(std::string id);
    std::vector<std::string> getIdentifiers();
private:
    std::vector<std::string> identifiers;
};

#endif //OUR_C_COMPILER_ASTDECL_H
