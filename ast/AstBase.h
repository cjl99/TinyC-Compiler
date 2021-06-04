#ifndef OUR_C_COMPILER_ASTBASE_H
#define OUR_C_COMPILER_ASTBASE_H

#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <tuple>
#include <string>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>


// base class of all ASTs
class AstBase {
public:
    AstBase() = default;
    AstBase(std::string nodeType);
    std::string getNodeType() const;
    virtual Value *codeGen() = 0;

private:
    std::string nodeType;

//    virtual std::optional<int> Eval(Interpreter &intp) const = 0;
//    virtual ValPtr GenerateIR(IRGenerator &gen) const = 0;
};

#endif //OUR_C_COMPILER_ASTBASE_H
