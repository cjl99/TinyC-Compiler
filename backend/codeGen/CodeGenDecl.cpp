#include "CodeGen.h"
#include "../../ast/AstDecl.h"

// TODO
// declaration: type_specifier {init_declarator}*n ';'
// init_declarator: declarator  | declarator '=' initializer | direct_declarator
// direct_declarator: IDENTIFIER | IDENTIFIER[CONSTANT] | IDENTIFIER[] | IDENTIFIER(identifier_list)
llvm::Value* AstDeclaration::codegen(CodeGen &context) {

    std::cout << "Generate declaration" << std::endl;

    AstInitDeclList *init_decl_list = this->getInitDeclList();
    if(init_decl_list) {
        std::vector < AstInitDeclarator * > init_decl_vec = init_decl_list->getInitDeclList();
        for (auto init_decl : init_decl_vec) {
            bool hasInitializer = init_decl->hasEqual();  // int a = 1 vs. int a

            AstDeclarator *decl = init_decl->getDeclarator();
            AstDirectDeclarator *dd = decl->getDirectDeclarator();

            bool isPointerTy = decl->hasPointer(); // int *a vs. int a
            bool isArrayTy = dd->getArraySize().size()!=0;   // int a[10] vs. int a
            std::string varName = dd->getIdentifier();       // Get variable name
            std::string varType = this->getTypeSpec()->getLabel();  // Get variable type

            Type *tp;
            Value* inst = nullptr;

            // don't have initialization
            if(isPointerTy) {
                int ptrLevel = decl->getPointer()->getStarNum();
                tp = context.typeSystem.getType(varType, ptrLevel);
            }
            else if(isArrayTy){
                vector<int> arraySize = dd->getArraySize();
                int totalSize = 1;
                for(int i=0; i<arraySize.size(); ++i) {
                    totalSize *= arraySize[i];
                }
                if(totalSize<0) tp = context.typeSystem.getType(varType, 1);
                else tp = context.typeSystem.getType(varType, 0, totalSize);

                Type* element_type = context.typeSystem.getType(varType);

                context.theModule->getOrInsertGlobal("array"+varName, ArrayType::get(element_type, totalSize) );
                GlobalVariable* GArray = context.theModule->getNamedGlobal("array"+varName);
                // GArray->setLinkage(GlobalValue::LinkageTypes::ExternalLinkage);
                //GArray->setAlignment(4);

                // std::vector<Constant *> vec_init;
                std::vector<Constant *> vec_init(totalSize, ConstantInt::get(Type::getInt32Ty(context.llvmContext), 0, true));

                if(hasInitializer) {
                    AstInitializer *initializer = init_decl->getInitializer();
                    int count = 0;

                    for (AstInitializer *init: initializer->getInitList()->getInitializerList()) {
                        if (init->isExpression()) {
                            Value *tmp_init = init->getExpression()->codegen(context);
                            if (tmp_init->getType()->isPointerTy())
                                tmp_init = context.builder.CreateLoad(tmp_init);
                            vec_init[count++] = dyn_cast<ConstantInt>(tmp_init);
                        } else {
                            //  vec_init.push_back(init->getInitList()->codegen(context)); //TODO
                        }
                    }
                }
                Constant *ct = ConstantArray::get(ArrayType::get(element_type, totalSize), vec_init);
                GArray->setInitializer(ct);

//                    inst = context.builder.CreateAlloca(tp);
//                    inst = context.builder.CreateStore(GArray, inst);
//                   // Store inst to our SymbolTable
                context.setSymbolType(varName, tp);
                context.setSymbolValue(varName, GArray);
                context.setValueType(GArray, tp);

                continue;



            }
            else {  // not vector -- example: a;
                tp = context.typeSystem.getType(varType);
            }

            // Create a space in stack
            inst = context.builder.CreateAlloca(tp);
            // Store inst to our SymbolTable
            context.setSymbolType(varName, tp);
            context.setSymbolValue(varName, inst);
            context.setValueType(inst, tp);

            // have initialization in declaration
            // example: int a=1; | int a[5] = {1,2,3,4,5};

            if(hasInitializer && !isArrayTy){
                // initializer : expression | '{' initializer_list '}'  | '{' initializer_list ',' '}'
                AstInitializer *initializer = init_decl->getInitializer();
                // codegen(expression)
                Value *exp;
                if (initializer->getExpression()) {
                    exp = initializer->getExpression()->codegen(context);
                }
                else if (initializer->getInitList()) {
//                    std::vector<Value *> valueArray;
//                    for(AstInitializer *init: initializer->getInitList()->getInitializerList()) {
//                        if(init->isExpression()) {
//                            // TODO only constant type now
//                            valueArray.push_back(init->getExpression()->codegen(context));
//                        }
//                        else {
//                            valueArray.push_back(init->getInitList()->codegen(context)); //TODO
//                        }
//                    }
//                    exp = initializer->getInitList()->codegen(context);
                }
                else {
                    std::cout << "Error in initializer: no child!" << std::endl;
                }

                // TODO 类型检查
                // create store
                // cast to correct type
                // context.typeSystem.cast(exp, context.typeSystem.getVarType(dstTypeStr), context.currentBlock());
                // RValue is variable or not
                if(exp->getType()->isPointerTy()){
                    Value *tmpv = context.builder.CreateLoad(exp);
                    // RValue is array or not
                    if(tmpv->getType()->isArrayTy()){
                        Type *ptr  = PointerType::get(tmpv->getType()->getArrayElementType(), 0);
                        exp = context.builder.CreateBitCast(exp, ptr, "castArray2Ptr");
                    }
                    else exp=tmpv;
                }

                context.builder.CreateStore(exp, inst);
            }
        }
    }
    return nullptr;

}

