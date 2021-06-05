#ifndef OCC_AST_STRUCT_H
#define OCC_AST_STRUCT_H

#include "AstBase.h"
#include "AstExpr.h"
#include "AstDecl.h"
using namespace std;

class AstStructDeclarationList{
private:
    vector<pair<string, string> > members;
public:
    AstStructDeclarationList();

    void addMember(AstSpec* spec, AstDeclarator* declarator);

    vector<pair<string, string> > getMembers() const ;
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