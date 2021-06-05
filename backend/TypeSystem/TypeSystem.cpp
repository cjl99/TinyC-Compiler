//
// Created by 郑小叶 on 2021/6/4.
//

#include "TypeSystem.h"

StructType::StructType(LLVMContext& llvmContext, TypeSystem &typeSystem, string name)
            :llvmContext(llvmContext), typeSystem(typeSystem), name(name){}

void StructType::addStructMember(string memType, string memName){
    members.push_back(std::make_pair(memType, memName));
}
llvm::StructType* StructType::createStructType(){
    vector<Type*> llvmMemType;
    for(std::pair<std::string, string> member : members){
        llvmMemType.push_back(typeSystem.getType(member.first));
    }
    StructType *llvmStruct = StructType::create(llvmContext, name);
    llvmStruct->setBody(llvmMemType);

    typeSystem.structMap[name] = llvmStruct;
    return llvmStruct;
}

//=======================================================

Type *TypeSystem::getBuiltInType(string specifier) {

    if( specifier.compare("char") == 0 )  { return this->charTy; }
    if( specifier.compare("short") == 0 ) { return this->shortTy; }
    if( specifier.compare("int") == 0 )   { return this->intTy;}
    if( specifier.compare("long") == 0 )  { return this->longTy;}
    if( specifier.compare("float") == 0 ) { return this->floatTy;}
    if( specifier.compare("double") == 0 ){ return this->doubleTy;}
    if( specifier.compare("void") == 0 )  { return this->voidTy;}
    return nullptr;
}

unique_ptr<Type> TypeSystem::getArrayType(Type* type, uint64_t size){
    unique_ptr<Type> item = arrMap[make_pair(type, size)];
    if(!item.get()){
        arrMap[make_pair(vecType, size)] = ArrayType::get(type, size);
    }
    return arrMap[make_pair(vecType, size)].get();
}

unique_ptr<Type> TypeSystem::getPtrType(Type* type){
    unique_ptr<Type> item = ptrMap[type];
    if(!item.get()){
        ptrMap[type] = PointerType::get(type);
    }
    return ptrMap[type].get();
}

unique_ptr<Type> TypeSystem::getStructType(string name){
    unique_ptr<StructType> item = structMap[name];
    if(!item.get()){
        return nullptr;
    }
    return structMap[name].get();
}

// =============Todo=======================
Type* TypeSystem::getType(string specifiers, int ptrLevel){
    if(getBuiltInType(specifiers)!= nullptr)
        return getBuiltInType(specifiers);
    if(getStructType(specifiers)!= nullptr){
        return getStructType(specifiers);
    }
    if(specifiers.find("*") != std::string::npos){

    }
    if(specifiers.find("[") != std::string::npos){

    }
}

TypeSystem::TypeSystem(LLVMContext& llvmContext)
            :llvmContext(llvmContext){}