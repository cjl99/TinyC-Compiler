//
// Created by Jialiang Chen on 2021/5/23.
//

#include "AstType.h"

AstSpec::AstSpec(std::string label)
        :AstBase("specifier"),label(label){}

std::string AstSpec::getLabel() const{
    return label;
}

//==============================================
AstTypeName::AstTypeName(AstSpec *spec, AstPointer *pointer){
    type = spec->getLabel();
    if(pointer!= nullptr)
        ptrLevel = pointer->getStarNum();
    else ptrLevel = 0;
}

string AstTypeName::getType(){
    return type;
}

int AstTypeName::getPtrLevel(){
    return ptrLevel;
}

//==============================================
AstIdList::AstIdList(){}

void AstIdList::addId(string id){
    identifiers.push_back(id);
}

std::vector<string> AstIdList::getIdentifiers(){
    return identifiers
}