//
// Created by Jialiang Chen on 2021/5/23.
//

#include "AstType.h"

AstSpec::AstSpec(std::string label)
        :AstBase("specifier"),label(label){}

std::string AstSpec::getLabel() const{
    return label;
}

