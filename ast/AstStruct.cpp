#include "AstStruct.h"

AstStructDeclarationList::AstStructDeclarationList(){}

void AstStructDeclarationList::addMember(AstSpec* spec, AstDeclarator* declarator){
    string rawType = spec->getLabel();
    string memName;
    string memType;
//================Todo================================

    members.push_back(make_pair(memType, memName));
}

vector<pair<string, string> > AstStructDeclarationList::getMembers() const{
    return members;
}

//=====================================================
AstStructSpec::AstStructSpec(string name, AstStructDeclarationList* structDeclaration)
                : name(name){
    members = structDeclaration->getMembers();
}

string AstStructSpec::getName() const{
    return name;
}

vector<pair<string, string> > AstStructSpec::getMembers() const{
    return members;
}