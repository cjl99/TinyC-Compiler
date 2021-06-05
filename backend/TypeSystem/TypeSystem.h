//
// Created by 郑小叶 on 2021/6/5.
//

#ifndef TINYC_COMPILER_TYPESYSTEM_H
#define TINYC_COMPILER_TYPESYSTEM_H


#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

using TypeNamePair = std::pair<std::string, std::string>;

class TypeSystem;
class StructType;

class StructType{
private:
    LLVMContext &llvmContext;
    TypeSystem &typeSystem;
    string name;
    std::vector<std::pair<std::string, string> > members;

public:
    StructType(LLVMContext& llvmContext, TypeSystem &typeSystem, string name);
    void addStructMember(string memType, string memName);
    llvm::StructType* createStructType();

};

class TypeSystem {
private:
    LLVMContext& llvmContext;

public:
    TypeSystem(LLVMContext& llvmContext);
    // built-in type
    Type* voidTy = Type::getVoidTy(llvmContext);
    Type* charTy = Type::getInt8Ty(llvmContext);
    Type* shortTy = Type::getInt16Ty(llvmContext);
    Type* intTy = Type::getInt32Ty(llvmContext);
    Type* longTy = Type::getInt64Ty(llvmContext);
    Type* floatTy = Type::getFloatTy(llvmContext);
    Type* doubleTy = Type::getDoubleTy(llvmContext);

    // array types
    // https://stackoverflow.com/questions/35228471/how-to-create-llvm-array-type-using-allocainst
    map<pair<Type*, uint64_t>, unique_ptr<Type> > arrMap;
    // pointer types
    map<Type*, unique_ptr<Type> > ptrMap;
    // user types
    map<string, unique_ptr<StructType> > structMap;

    //=============================================================
    Type* getBuiltInType(string specifier);

    unique_ptr<Type> getArrayType(Type* type, uint64_t size);

    unique_ptr<Type> getPtrType(Type* type);

    unique_ptr<Type> getStructType(string name);

    Type* getType(string specifiers, int ptrLevel=0);

};

#endif //TINYC_COMPILER_TYPESYSTEM_H
