#include "CodeGen.h"
#include "../../ast/AstDecl.h"

// TODO
// declaration: type_specifier {init_declarator}*n ';'
// init_declarator: declarator  | declarator '=' initializer | direct_declarator
// direct_declarator: IDENTIFIER | IDENTIFIER[CONSTANT] | IDENTIFIER[] | IDENTIFIER(identifier_list)
llvm::Value* AstDeclaration::codegen(CodeGen &context) {

    std::cout << "[LLVM] Generate declaration" << std::endl;

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
                if(totalSize<0) {//  int a[]
                    tp = context.typeSystem.getType(varType, 1);
                }
                else{
                    tp = context.typeSystem.getType(varType, 0, totalSize);
                }
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

            if(hasInitializer){
                // initializer : expression | '{' initializer_list '}'  | '{' initializer_list ',' '}'
                AstInitializer *initializer = init_decl->getInitializer();
                // codegen(expression)
                Value *exp;
                if (initializer->getExpression()) {
                    exp = initializer->getExpression()->codegen(context);
                } else if (initializer->getInitList()) {
                    exp = initializer->getInitList()->codegen(context);
                } else {
                    LogErrorV("Error in initializer: no child!");
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

