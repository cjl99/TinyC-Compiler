//
// Created by Jialiang Chen on 2021/5/23.
//

#include "AstType.h"

AstSpec::AstSpec(std::string label)
        :AstBase("specifier"),label(label){}

std::string AstSpec::getLabel() const{
    return label;
}

AstSpecList::AstSpecList()
            :AstBase("specifier_list"){}

void AstSpecList::addSpecifier(AstSpec *spec){
    spec_list.push_back(spec);
}

const std::vector<AstSpec *> &AstSpecList::getSpecList() const{
    return spec_list;
}

