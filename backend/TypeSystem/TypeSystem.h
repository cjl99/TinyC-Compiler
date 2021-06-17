#ifndef TINYC_COMPILER_TYPESYSTEM_H
#define TINYC_COMPILER_TYPESYSTEM_H

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

using namespace llvm;

using TypeNamePair = std::pair<std::string, std::string>;
using std::string;
using std::vector;
using std::unique_ptr;

class TypeSystem;
//class mtructType;
//
//class mStructType{
//private:
//    LLVMContext &llvmContext;
//    TypeSystem &typeSystem;
//    std::string name;
//    std::vector<std::pair<std::string, std::string> > members;
//
//public:
//    mStructType(LLVMContext& llvmContext, TypeSystem &typeSystem, std::string name);
//    void addStructMember(std::string memType, std::string memName);
//    StructType* createStructType();
//};

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
    Type* stringTy = Type::getInt8PtrTy(llvmContext);


    // array types
    // https://stackoverflow.com/questions/35228471/how-to-create-llvm-array-type-using-allocainst
    // std::map<std::pair<Type*, uint64_t>, Type* > arrMap;
    // pointer types
    // std::map<Type*, Type* > ptrMap;
    // user types
    // std::map<std::string, StructType* > structMap;

    //=============================================================
    Type* getBuiltInType(std::string specifier);

     std::unique_ptr<Type> getArrayType(std::string baseType, uint64_t size);

    // std::unique_ptr<Type> getPtrType(Type* type);

    // std::unique_ptr<Type> getStructType(std::string name);

    Type* getType(std::string specifiers, int ptrLevel=0, int arraySize=0);

};

#endif //TINYC_COMPILER_TYPESYSTEM_H
