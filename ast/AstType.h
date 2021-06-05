//
// Created by Jialiang Chen & Xiaoye Zheng on 2021/5/23.
//

#ifndef OUR_C_COMPILER_ASTTYPE_H
#define OUR_C_COMPILER_ASTTYPE_H

#include "AstBase.h"

class AstSpec;
class AstTypeName;
class AstIdList;

class AstSpec: public AstBase{
private:
    std::string label;

public:
    AstSpec(std::string label);

    std::string getLabel() const;
};

class AstTypeName: public AstBase{
private:
    string type;
    int ptrLevel;
public:
    AstTypeName(AstSpec *spec, AstPointer *pointer);

    string getType();

    int getPtrLevel();
};

class AstIdList: public AstBase{
private:
   std::vector<string> identifiers;
public:
    AstIdList();

    void addId(string id);

    std::vector<string> getIdentifiers();
};
#endif //OUR_C_COMPILER_ASTTYPE_H
