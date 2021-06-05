//===========AstDeclarationList_CodeGen=============
llvm::Value* AstDeclarationList::codeGen(CodeGen &context){
    std::vector<AstDeclaration*>& declarationList = this->getDeclarationList();
    for(auto declaration: declarationList){
        declaration->codeGen(context);
    }
}

//===========Todo=============
//declaration:type_specifier {init_declarator}*n ';'
//init_declarator: declarator
//                | declarator '=' initializer
//declarator: {'*'}*n direct_declarator
//            | direct_declarator
//direct_declarator: IDENTIFIER | IDENTIFIER[CONSTANT] | IDENTIFIER[] | IDENTIFIER(identifier_list)
llvm::Value* AstDeclaration::codeGen(CodeGen &context){

}
