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

std::string TypeSystem::getTypeStr(Type *type) {
    switch(type->getTypeID()) {
        case Type::VoidTyID: return "VoidTyID";
        case Type::HalfTyID: return "HalfTyID";
        case Type::FloatTyID: return "FloatTyID";
        case Type::DoubleTyID: return "DoubleTyID";
        case Type::IntegerTyID:  return "int";
        case Type::FunctionTyID: return "FunctionTyID";
        case Type::StructTyID: return "StructTyID";
        case Type::ArrayTyID: return "ArrayTyID";
        case Type::PointerTyID: return "PointerTyID";
        case Type::FixedVectorTyID: return "FixedVectorTyID";
        case Type::ScalableVectorTyID: return "ScalableVectorTyID";
        case Type::TokenTyID: return "TokenTyID";
        default: return "UnknownTyID";
    }
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
    addCast(intTy, floatTy, llvm::CastInst::SIToFP);
    addCast(intTy, doubleTy, llvm::CastInst::SIToFP);
    addCast(floatTy, doubleTy, llvm::CastInst::FPExt);
    addCast(floatTy, intTy, llvm::CastInst::FPToSI);
    addCast(doubleTy, intTy, llvm::CastInst::FPToSI);
    addCast(intTy, intTy, llvm::CastInst::SExt);
}

bool TypeSystem::checkType(Type *LType, Type *RType){
    return RType->getPointerTo() == LType;
}


void TypeSystem::addCast(Type *from, Type *to, CastInst::CastOps op) {
    if( _castTable.find(from) == _castTable.end() ){
        _castTable[from] = std::map<Type*, CastInst::CastOps>();
    }
    _castTable[from][to] = op;
}

Value* TypeSystem::castType(Value *value, Type *type, BasicBlock *block) {
    Type* from = value->getType();
    if( from == type )
        return value;
    if( _castTable.find(from) == _castTable.end() ){
        LogWarningV("Type has no cast");
        return value;
    }
    if( _castTable[from].find(type) == _castTable[from].end() ){
        string error = "Unable to cast from ";
        error += getTypeStr(from) + " to " + getTypeStr(type);
        LogWarningV(error);
        return value;
    }

    return CastInst::Create(_castTable[from][type], value, type, "cast", block);
}