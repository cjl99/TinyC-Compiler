#include "AstStruct.h"
AstComplexSpec::AstComplexSpec(string nodeType, string type, string id)
                :AstBase(nodeType),type(type),id(id){}

string AstComplexSpec::getType() const{
    return type;
}

string AstComplexSpec::getId() const{
    return id;
}

// ===============================================
AstStructOrUnionSpec::AstStructOrUnionSpec(string label, string id, AstStructDeclList *structList)
                    :AstComplexSpec("struct_or_union_specifier",label, id), structList(structList) {}

AstStructDeclList *AstStructOrUnionSpec::getStructList() const{
    return structList;
}

// ===============================================
AstEnumSpec::AstEnumSpec(string type, string id, AstEnumList *enumList)
            :AstComplexSpec("enum_specifier",type, id), enumList(enumList){}

AstEnumList *AstEnumSpec::getEnumList() const{
    return enumList;
}

// ===============================================
AstEnumList::AstEnumList()
            :AstBase("enumerator_list"){}

void AstEnumList::addEnumerator(AstEnumerator *astEnumerator){
    enumList.push_back(astEnumerator);
}

const std::vector<AstEnumerator *> &AstEnumList::getEnumList() const{
    return enumList;
}

// ===============================================
AstEnumerator::AstEnumerator(string label, AstCondiExpr *constExpr)
            :label(label), constExpr(constExpr){}

AstExpr *AstEnumerator::getConstExpr() const{
    return constExpr;
}

string AstEnumerator::getLabel() const{
    return label;
}

// ===============================================
AstTypeSpec::AstTypeSpec(std::string label, AstComplexSpec *complexSpec) 
            :AstSpec(label), complexSpec(complexSpec){}

AstComplexSpec *AstTypeSpec::getComplexSpec() const {
    return this->complexSpec;
}
