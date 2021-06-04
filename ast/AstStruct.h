#ifndef OCC_AST_STRUCT_H
#define OCC_AST_STRUCT_H

#include "AstBase.h"
#include "AstExpr.h"
#include "AstDecl.h"
using namespace std;

class AstComplexSpec;
class AstEnumerator;
class AstEnumList;
class AstEnumSpec;
class AstStructOrUnionSpec;
class AstTypeSpec;


class AstComplexSpec: public AstBase{
private:
    string type;
    string id;
    
public:
    AstComplexSpec(string, string, string);

    string getType() const;

    string getId() const;
};

class AstEnumSpec: public AstComplexSpec{
private:
    AstEnumList *enumList;
public:
    AstEnumSpec(string, string id= "", AstEnumList *enumList = nullptr) ;

    AstEnumList *getEnumList() const;
};

class AstStructOrUnionSpec: public AstComplexSpec{
private:
    AstStructDeclList *structList;

public:
    AstStructOrUnionSpec(string label, string id= "", AstStructDeclList *structList = nullptr) ;
    AstStructDeclList *getStructList() const;
};


class AstEnumerator: public AstBase{
private:
    string label;
    AstCondiExpr *constExpr;

public:
    AstEnumerator(string label, AstCondiExpr *constExpr = nullptr);

    AstExpr *getConstExpr() const;

    string getLabel() const;
};

class AstEnumList: public AstBase{
private:
    vector<AstEnumerator *> enumList;

public:
    AstEnumList();

    void addEnumerator(AstEnumerator *);

    const std::vector<AstEnumerator *> &getEnumList() const;
};

class AstTypeSpec: public AstSpec{
private:
    AstComplexSpec *complexSpec;
    // std::string label;
    // char *label1;

public:
    AstTypeSpec(std::string label1, AstComplexSpec *complexSpec=nullptr);
    
    AstComplexSpec *getComplexSpec() const;
};





#endif