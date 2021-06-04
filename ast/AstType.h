//
// Created by Jialiang Chen & Xiaoye Zheng on 2021/5/23.
//

#ifndef OUR_C_COMPILER_ASTTYPE_H
#define OUR_C_COMPILER_ASTTYPE_H

#include "AstBase.h"

class AstSpec;
class AstSpecList;
class AstTypeQualList;

class AstSpec: public AstBase{
private:
    std::string label;

public:
    AstSpec(std::string label);

    std::string getLabel() const;
};

class AstSpecList : public AstBase {
private:
    std::vector<AstSpec *> spec_list;

public:
    AstSpecList();

    void addSpecifier(AstSpec *);

    const std::vector<AstSpec *> &getSpecList() const;
};

// AstTypeQualifier = AstSpec
class AstTypeQualList: public AstSpecList{
    
};

#endif //OUR_C_COMPILER_ASTTYPE_H
