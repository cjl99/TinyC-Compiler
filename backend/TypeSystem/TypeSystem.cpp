#include "TypeSystem.h"

// mStructType

//mStructType::mStructType(LLVMContext& llvmContext, TypeSystem &typeSystem, std::string name)
//            :llvmContext(llvmContext), typeSystem(typeSystem), name(name){}
//
//void mStructType::addStructMember(std::string memType, string memName){
//    members.push_back(std::make_pair(memType, memName));
//}
//llvm::StructType* mStructType::createStructType(){
//    vector<Type*> llvmMemType;
//    for(std::pair<std::string, string> member : members){
//        llvmMemType.push_back(typeSystem.getType(member.first));
//    }
//    StructType *llvmStruct = StructType::create(llvmContext, name);
//    llvmStruct->setBody(llvmMemType);
//
//    typeSystem.structMap[name] = llvmStruct;
//    return llvmStruct;
//}

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


//unique_ptr<Type> TypeSystem::getPtrType(Type* type){
//    unique_ptr<Type> item = ptrMap[type];
//    if(!item.get()){
//        ptrMap[type] = PointerType::get(type);
//    }
//    return ptrMap[type].get();
//}
//
//unique_ptr<Type> TypeSystem::getStructType(string name){
//    unique_ptr<StructType> item = structMap[name];
//    if(!item.get()){
//        return nullptr;
//    }
//    return structMap[name].get();
//}
//

// =============Todo=======================
Type* TypeSystem::getType(string specifiers, int ptrLevel, int arraySize){

    // Error
    if(getBuiltInType(specifiers)== nullptr){
//        cout << "TypeSystem::getType Error: Type undefined!" << endl;
        return nullptr;
    }
    // array
    if(arraySize!=0){
        Type* tp = getType(specifiers, 0);
        return ArrayType::get(tp, arraySize);
    }
    // pointer
    if(ptrLevel!=0){
        Type *pointeeType = getBuiltInType(specifiers);
        while(ptrLevel>0){
            pointeeType = PointerType::get(pointeeType, 0);
            ptrLevel--;
        }
        return pointeeType;
    }
    // built-in
    return getBuiltInType(specifiers);

}

TypeSystem::TypeSystem(LLVMContext& llvmContext)
            :llvmContext(llvmContext){

}
