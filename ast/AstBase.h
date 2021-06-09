#ifndef OUR_C_COMPILER_ASTBASE_H
#define OUR_C_COMPILER_ASTBASE_H

#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <string>

#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>

//#include "../backend/codeGen/CodeGen.h"
//#include "../backend/TypeSystem//TypeSystem.h"

// base class of all ASTs
class CodeGen;

class AstBase {
public:
    AstBase() = default;
    AstBase(std::string nodeType);
    std::string getNodeType() const;

    virtual llvm::Value *codegen(CodeGen& context) = 0;

private:
    std::string nodeType;
};

#endif //OUR_C_COMPILER_ASTBASE_H
