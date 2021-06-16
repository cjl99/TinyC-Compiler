#include "CodeGen.h"
#include "../../ast/AstDecl.h"

//===========DeclarationList codegen=============
// llvm::Value* AstDeclarationList::codegen(CodeGen &context) {
//     std::cout << "Generate declaration_list" << std::endl;
    
//     std::vector<AstDeclaration*> declarationList = this->getDeclarationList();
    
//     for(auto declaration: declarationList){
//         declaration->codegen(context);
//     }
//     return nullptr;
// }

// TODO
// declaration: type_specifier {init_declarator}*n ';'
// init_declarator: declarator  | declarator '=' initializer | direct_declarator
// direct_declarator: IDENTIFIER | IDENTIFIER[CONSTANT] | IDENTIFIER[] | IDENTIFIER(identifier_list)
llvm::Value* AstDeclaration::codegen(CodeGen &context) {
    std::cout << "Generate declaration" << std::endl;
    Type* tp = context.typeSystem.getType(this->getTypeSpec()->getLabel(), 0);
    Value* inst = nullptr;
    AstInitDeclList *init_decl_list = this->getInitDeclList();
    if(init_decl_list) {
        std::vector < AstInitDeclarator * > init_decl_vec = init_decl_list->getInitDeclList();
        for (auto init_decl : init_decl_vec) {
            // don't have initialization
            if (!init_decl->hasEqual()) {
                AstDeclarator *decl = init_decl->getDeclarator();
                // Basic Type -- example: int a;
                if (!decl->hasPointer()) {
                    // Get variable name
                    AstDirectDeclarator *dd = decl->getDirectDeclarator();
                    std::string name = dd->getIdentifier();
                    vector<int> arraySize = dd->getArraySize();
                    // vector type
                    if( arraySize.size()!=0 ){ // example a[4][6];
                        int totalSize = 1;
                        for(int i=0; i<arraySize.size(); ++i) {
                            totalSize *= arraySize[i];
                        }
                        if(totalSize==-1) { // int a[]
                            tp = context.typeSystem.getType(this->getTypeSpec()->getLabel(), 1);
                            inst = context.builder.CreateAlloca(tp);
                        } else {
                            //context.setArraySize(name, totalSize);
                            Value *arraySizeValue = ConstantInt::get(Type::getInt32Ty(context.llvmContext), totalSize,
                                                                     true);
                            // tp ?= PointerType::get(getVarType(type.name), 0);
                            ArrayType *arrayType = ArrayType::get(tp, totalSize);
                            inst = context.builder.CreateAlloca(arrayType, arraySizeValue, "arraytmp");
                            tp = arrayType;
                        }
                        // Store inst to our SymbolTable
                        context.setSymbolType(name, tp);
                        context.setSymbolValue(name, inst);
                        context.setValueType(inst, tp);
                    }
                    // not vector -- example: a;
                    else {
                        inst = context.builder.CreateAlloca(tp);
                        // Store inst to our SymbolTable
                        context.setSymbolType(name, tp);
                        context.setSymbolValue(name, inst);
                        context.setValueType(inst, tp);
                    }

                }
                // Pointer Type -- example: int *a;
                else {
                    AstDirectDeclarator *dd = decl->getDirectDeclarator();
                    std::string name = dd->getIdentifier();
                    AstPointer* pointer = decl->getPointer();
                    tp = context.typeSystem.getType(this->getTypeSpec()->getLabel(), pointer->getStarNum());
                    // Create a space in stack
                    inst = context.builder.CreateAlloca(tp);
                    // Store it to our SymbolTable
                    context.setSymbolType(name, tp);
                    context.setSymbolValue(name, inst);
                    context.setValueType(inst, tp);
                }


            }
            // have initialization in declaration
            else {  // example: int a=1; | int a[5] = {1,2,3,4,5};
                AstDeclarator *decl = init_decl->getDeclarator();
                AstInitializer *initializer = init_decl->getInitializer();
                // initializer : expression | '{' initializer_list '}'  | '{' initializer_list ',' '}'
                if(!decl->hasPointer()) {
                    AstDirectDeclarator *dd = decl->getDirectDeclarator();
                    std::string name = dd->getIdentifier();
                    vector<int> arraySize = dd->getArraySize();
                    if(arraySize.size()!=0) { // int a[5] = {1,2,3,4,5};
                        int totalSize = 1;
                        for(int i=0; i<arraySize.size(); ++i) {
                            totalSize *= arraySize[i];
                        }
                        if(totalSize==-1) { // int a[]
                            tp = context.typeSystem.getType(this->getTypeSpec()->getLabel(), 1);
                            inst = context.builder.CreateAlloca(tp);
                        } else {
                            //context.setArraySize(name, totalSize);
                            Value *arraySizeValue = ConstantInt::get(Type::getInt32Ty(context.llvmContext), totalSize,
                                                                     true);
                            // tp ?= PointerType::get(getVarType(type.name), 0);
                            ArrayType * arrayType = ArrayType::get(tp, totalSize);
                            inst = context.builder.CreateAlloca(arrayType, arraySizeValue, "arraytmp");
                            tp = arrayType;
                        }
                        // set symbol table
                        context.setSymbolType(name, tp);
                        context.setSymbolValue(name, inst);
                        context.setValueType(inst, tp);

                        //ConstantAggregateZero* const_array_2 = ConstantAggregateZero::get(tp);
                        //inst->setInitializer(const_array_2);


                    }
                    else {
                        inst = context.builder.CreateAlloca(tp);
                        // create alloca
                        // set symbol table
                        context.setSymbolType(name, tp);
                        context.setSymbolValue(name, inst);
                        context.setValueType(inst, tp);
                    }

                }
                else{ // char *str = "abc";
                    AstDirectDeclarator *dd = decl->getDirectDeclarator();
                    std::string name = dd->getIdentifier();
                    AstPointer* pointer = decl->getPointer();
                    tp = context.typeSystem.getType(this->getTypeSpec()->getLabel(), pointer->getStarNum());
                    // Create a space in stack
                    inst = context.builder.CreateAlloca(tp);
                    // Store it to our SymbolTable
                    context.setSymbolType(name, tp);
                    context.setSymbolValue(name, inst);
                    context.setValueType(inst, tp);
                }

                // codegen(expression)
                Value *exp;
                // TODO 类型检查
                if (initializer->getExpression()) {
                    exp = initializer->getExpression()->codegen(context);
                } else if (initializer->getInitList()) {
                    exp = initializer->getInitList()->codegen(context);
                } else {
                    std::cout << "Error in initializer: no child!" << std::endl;
                }
                // cast to correct type
                // context.typeSystem.cast(exp, context.typeSystem.getVarType(dstTypeStr), context.currentBlock());

                // create store
                context.builder.CreateStore(exp, inst);
            }
        }
    }

    return inst;
}

