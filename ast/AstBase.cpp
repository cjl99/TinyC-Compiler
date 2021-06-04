#include "AstBase.h"

AstBase::AstBase(std::string nodeType):
        nodeType(nodeType){}
std::string AstBase::getNodeType() const{
        return nodeType;
}
