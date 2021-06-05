#include "AstStruct.h"

//=====================================================
AstStructDeclarationList::AstStructDeclarationList(){}

void AstStructDeclarationList::addMember(AstSpec* spec, AstDeclarator* declarator){
    string rawType = spec->getLabel();
    int ptrNum = 0;
    string memName;
    if(declarator->hasPointer()){
        AstPointer pointer = declarator->getPointer();
        ptrNum = pointer.getStarNum();
    }
    AstDirectDeclarator *temp = declarator->getDirectDeclarator();
    memName = temp->getIdentifier();
    memRawType.push_back(rawType);
    ptrLevel.push_back(ptrNum);
    memName.push_back(memName);
}

vector<string> AstStructDeclarationList::getMemRawType() const{
    return memRawType;
}

vector<int> AstStructDeclarationList::getPtrLevel() const{
    return ptrLevel;
}

vector<string> AstStructDeclarationList::getMemName() const{
    return memName;
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