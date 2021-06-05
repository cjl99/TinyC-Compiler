#ifndef OUR_C_COMPILER_ASTBASE_H
#define OUR_C_COMPILER_ASTBASE_H

#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <string>

// #include <llvm/IR/Constants.h>
// #include <llvm/IR/Function.h>


// base class of all ASTs
class AstBase {
public:
    AstBase() = default;
    AstBase(std::string nodeType);
    std::string getNodeType() const;
    virtual Value *codegen() = 0;

private:
    std::string nodeType;
};

#endif //OUR_C_COMPILER_ASTBASE_H
