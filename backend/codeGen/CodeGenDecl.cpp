#include "../../ast/AstDecl.h"
#include "CodeGen.h"

//===========AstDeclarationList_CodeGen=============
//llvm::Value* AstDeclarationList::codegen(CodeGen &context){
//    std::vector<AstDeclaration*>& declarationList = this->getDeclarationList();
//    for(auto declaration: declarationList){
//        declaration->codeGen(context);
//    }
//    return nullptr;
//}

//===========Todo=============
//declaration:type_specifier {init_declarator}*n ';'
//init_declarator: declarator
//                | declarator '=' initializer
//declarator: {'*'}*n direct_declarator
//            | direct_declarator
//direct_declarator: IDENTIFIER | IDENTIFIER[CONSTANT] | IDENTIFIER[] | IDENTIFIER(identifier_list)
llvm::Value* AstDeclaration::codegen(CodeGen &context) {
    std::cout << "Generate declaration" << std::endl;
    Type* tp = context.typeSystem.getType(this->getTypeSpec()->getLabel(), 0);
    Value* inst;
    std::vector<AstInitDeclarator *> init_decl_list = this->getInitDeclList()->getInitDeclList();
    for(auto init_decl : init_decl_list) {
        if(!init_decl->hasEqual()) { // example: int (*)a
            AstDeclarator *decl = init_decl->getDeclarator();
            if(!decl->hasPointer()) {   // int a;
                AstDirectDeclarator *dd = decl->getDirectDeclarator();
                std::string name = dd->getIdentifier();

                inst = context.builder.CreateAlloca(tp);
                context.setSymbolType(name, tp);
                context.setSymbolValue(name, inst);
            }
            else {  //  int *a;

            }
        }
        else {  // example: int a=1

        }
    }

    return inst;
}

