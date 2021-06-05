#include "AstStruct.h"

//=====================================================
AstStructDeclarationList::AstStructDeclarationList(){}

void AstStructDeclarationList::addMember(AstSpec* spec, AstDeclarator* declarator){
    string rawType = spec->getLabel();
    int ptrNum = 0;
    string memName2;
    if(declarator->hasPointer()){
        AstPointer *pointer = declarator->getPointer();
        ptrNum = pointer->getStarNum();
    }
    AstDirectDeclarator *temp = declarator->getDirectDeclarator();
    memName2 = temp->getIdentifier();
    memRawType.push_back(rawType);
    ptrLevel.push_back(ptrNum);
    memName.push_back(memName2);
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
    memRawType = structDeclaration->getMemRawType();
    memName = structDeclaration->getMemName();
    ptrLevel = structDeclaration->getPtrLevel();
}

string AstStructSpec::getName() const{
    return name;
}

vector<string> AstStructSpec::getMemRawType() const{
    return memRawType;
}

vector<int> AstStructSpec::getPtrLevel() const{
    return ptrLevel;
}

vector<string> AstStructSpec::getMemName() const{
    return memName;
}