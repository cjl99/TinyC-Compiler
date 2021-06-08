//
// Created by Jialiang Chen & Xiaoye Zheng on 2021/5/23.
//

#ifndef OUR_C_COMPILER_ASTTYPE_H
#define OUR_C_COMPILER_ASTTYPE_H

#include "AstBase.h"

class AstSpec;
class AstSpec: public AstBase{
private:
    std::string label;

public:
    AstSpec(std::string label);
    std::string getLabel() const;

    virtual llvm::Value *codegen(CodeGen& context) override {
        // TODO
            return nullptr;
    }
};


#endif //OUR_C_COMPILER_ASTTYPE_H
