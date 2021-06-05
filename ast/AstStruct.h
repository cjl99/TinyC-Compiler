#ifndef OCC_AST_STRUCT_H
#define OCC_AST_STRUCT_H

#include "AstBase.h"
#include "AstExpr.h"
#include "AstDecl.h"
using namespace std;

class AstStructDeclarationList{
private:
    vector<string> memRawType;
    vector<int> ptrLevel;
    vector<string> memName;
public:
    AstStructDeclarationList();

    void addMember(AstSpec* spec, AstDeclarator* declarator);

    vector<string> getMemRawType() const;

    vector<int> getPtrLevel() const;

    vector<string> getMemName() const;

};

class AstStructSpec{
private:
    string name;
    vector<pair<string, string> > members;
public:
    AstStructSpec(string name, AstStructDeclarationList* structDeclaration);

    string getName() const;

    vector<pair<string, string> > getMembers() const;

};
#endif