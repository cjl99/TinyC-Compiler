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
    AstInitDeclList *init_decl_list = this->getInitDeclList();
    if(init_decl_list) {
        std::vector < AstInitDeclarator * > init_decl_vec = init_decl_list->getInitDeclList();
        for (auto init_decl : init_decl_vec) {
            if (!init_decl->hasEqual()) { // example: int (*)a
                AstDeclarator *decl = init_decl->getDeclarator();
                if (!decl->hasPointer()) {   // int a;
                    AstDirectDeclarator *dd = decl->getDirectDeclarator();
                    std::string name = dd->getIdentifier();

                    inst = context.builder.CreateAlloca(tp);
                    context.setSymbolType(name, tp);
                    context.setSymbolValue(name, inst);
                } else {  //  int *a;

                }
            } else {  // example: int a=1
                AstDeclarator *decl = init_decl->getDeclarator();
                AstInitializer *initializer = init_decl->getInitializer();
                // initializer : expression | '{' initializer_list '}'  | '{' initializer_list ',' '}'
                // int a[5] = {1,2,3,4,5};   int a[5] = {1,2,3,4,5,}
                // int a = 1;
                if(!decl->hasPointer()) {
                    AstDirectDeclarator *dd = decl->getDirectDeclarator();
                    std::string name = dd->getIdentifier();
                    // create alloca
                    inst = context.builder.CreateAlloca(tp);
                    // set symbol table
                    context.setSymbolType(name, tp);
                    context.setSymbolValue(name, inst);
                    // codegen(expression)
                    Value * exp;
                    if(initializer->getExpression()) {
                        exp = initializer->getExpression()->codegen(context);
                    }
                    // TODO 类型检查
                    else if(initializer->getInitList()) {
                        exp = initializer->getInitList()->codegen(context);
                    }
                    else {
                        std::cout << "Error in initializer: no child!" << std::endl;
                    }
                    // cast to correct type
                    // context.typeSystem.cast(exp, context.typeSystem.getVarType(dstTypeStr), context.currentBlock());

                    // create store
                    context.builder.CreateStore(exp, inst);
                }
            }
        }
    }

    return inst;
}
