#include "../../ast/AstExpr.h"
#include "CodeGen.h"

// expression : conditional_expression | unary_expression assignment_operator expression
llvm::Value* AstExpression::codegen(CodeGen &context){
    // conditional_expr
    if(this->astCondiExpr) {
        return this->astCondiExpr->codegen(context);
    }
    else {
        // Operator: ">>=" "<<=" "+=" "-=" "*=" "/=" "%=" "&=" "^=" "|=" "="
        std::string op = this->getAssignOp()->getOperator();
        std::cout << "Generate assignment expression...\n op is: " << op << std::endl;

        Value *L = this->getUnaryExpr()->codegen(context);
        std::cout << "lhs type: " << context.typeSystem.getTypeStr(L->getType()) << std::endl;

        Value *R = this->getExpression()->codegen(context);
        std::cout << "rhs type: " << context.typeSystem.getTypeStr(R->getType()) << std::endl;

        if(op=="=") {
            // RValue is variable or not
            if(R->getType()->isPointerTy()){
                Value *tmpv = context.builder.CreateLoad(R);
                // RValue is array or not
                if(tmpv->getType()->isArrayTy()){
                    Type *ptr  = PointerType::get(tmpv->getType()->getArrayElementType(), 0);
                    R = context.builder.CreateBitCast(R, ptr, "castArray2Ptr");
                }
                else R=tmpv;
            }

            if(!L->getType()->isPointerTy()) return LogErrorV("Generate assign expr error: lhs is noy pointer type");
            context.builder.CreateStore(R, L);
        }
        else {
            Value *res;
            Value *Ltmp = L;
            if( context.isIdentifier(L) ) L = context.builder.CreateLoad(L);
            if( context.isIdentifier(R) ) R = context.builder.CreateLoad(R);
            // is float operation or not
            Type *LType = L->getType();
            Type *RType = R->getType();

            bool Lf = LType->isDoubleTy();
            bool Rf = RType->isDoubleTy();

            if (!Lf && !Rf) {
                if (op == "+=") res = context.builder.CreateAdd(L, R, "assign.add");
                else if (op == "-=") res = context.builder.CreateSub(L, R, "assign.sub");
                else if (op == "*=") res = context.builder.CreateMul(L, R, "mul(i)tmp");
                else if (op == "/=") res = context.builder.CreateSDiv(L, R, "div(i)tmp");
                else if (op == "%=") res = LogErrorV("LLVM don't have mod operation: QAQ");  //TODO Mod Opeartion
                else if (op == "&=") res = context.builder.CreateAnd(L, R, "and(i)tmp");
                else if (op == "|=") res = context.builder.CreateOr(L, R, "or(i)tmp");
                else if (op == "^=") res = context.builder.CreateXor(L, R, "xor(i)tmp");
                else if (op == "<<=") res = context.builder.CreateShl(L, R, "shl(i)tmp");
                else if (op == ">>=") res = context.builder.CreateAShr(L, R, "shr(i)tmp");
                else res = LogErrorV("Unknown operator in assignment_expression");
            } else {
                // change L & R to double
                if (!Lf) L = context.builder.CreateUIToFP(L, Type::getDoubleTy(context.llvmContext), "ftmpL");
                if (!Rf) R = context.builder.CreateUIToFP(R, Type::getDoubleTy(context.llvmContext), "ftmpR");

                if (op == "+=") res = context.builder.CreateFAdd(L, R, "add(f)tmp");
                else if (op == "-=") res = context.builder.CreateFSub(L, R, "sub(f)tmp");
                else if (op == "*=") res = context.builder.CreateFMul(L, R, "mul(f)tmp");
                else if (op == "/=") res = context.builder.CreateFDiv(L, R, "div(f)tmp");
                else if (op == "%=") res = LogErrorV("operator's type: 'double', invalid operands '%='");
                else if (op == "&=") res = LogErrorV("operator's type: 'double', invalid operands '&='");
                else if (op == "|=") res = LogErrorV("operator's type: 'double', invalid operands '|='");
                else if (op == "^=") res = LogErrorV("operator's type: 'double', invalid operands '^='");
                else if (op == "<<=") res = LogErrorV("operator's type: 'double', invalid operands '<<='");
                else if (op == ">>=") res = LogErrorV("operator's type: 'double', invalid operands '>>='");
                else res = LogErrorV("Unknown operator in assignment_expression");
            }
            if(res) {
                // if L is int and R is double originally, should change back to int after assignment.
                if(!Lf && Rf) res=context.builder.CreateFPToUI(res, Type::getInt32Ty(context.llvmContext), "itmp");
                context.builder.CreateStore(res, Ltmp);
            }
        }
        return L;
    }
}

// conditional_expression :
// Todo
llvm::Value* AstCondiExpr::codegen(CodeGen &context) {
    if(!this->isExpand()) { // binary_expression
        return this->binaryExpr_back->codegen(context);
    }
    else {
        std::cout << "Generate conditional expression" << std::endl;

        // TODO b_front ? expr : b_back
        AstBinaryExpr *b_front = this->getAstBinaryExpr_front();
        if(b_front== nullptr) return nullptr;

        AstExpression *expr = this->getAstExpression();
        AstBinaryExpr *b_back = this->getAstBinaryExpr_back();

        Value *judge = b_front->codegen(context);
        // compare judge with 0;
        // Value *zero = ConstantInt::get(Type::getInt32Ty(context.llvmContext), 0, true);
        judge = context.CastToBoolean(context, judge);

        Function* theFunction = context.builder.GetInsertBlock()->getParent();      // the function where if statement is in
        BasicBlock *thenBlock = BasicBlock::Create(context.llvmContext, "3then", theFunction);
        BasicBlock *elseBlock = BasicBlock::Create(context.llvmContext, "3else");
        BasicBlock *mergeBlock = BasicBlock::Create(context.llvmContext, "3cont");
        context.builder.CreateCondBr(judge, thenBlock, elseBlock);

        // Emit Then
        context.builder.SetInsertPoint(thenBlock);
        Value *ThenV = expr->codegen(context);
        if (ThenV == 0) return 0;
        context.builder.CreateBr(mergeBlock);
        // Codegen of 'Then' can change the current block, update ThenBB for the PHI.
        thenBlock = context.builder.GetInsertBlock();

        // Emit Else
        theFunction->getBasicBlockList().push_back(elseBlock);
        context.builder.SetInsertPoint(elseBlock);
        context.pushBlock(elseBlock);
        Value *ElseV = b_back->codegen(context);
        context.popBlock();
        if (ElseV == 0) return 0;
        context.builder.CreateBr(mergeBlock);
        // Codegen of 'Else' can change the current block, update ElseBB for the PHI.
        elseBlock = context.builder.GetInsertBlock();


        // Emit merge block.
        theFunction->getBasicBlockList().push_back(mergeBlock);
        context.builder.SetInsertPoint(mergeBlock);
        PHINode *PN = context.builder.CreatePHI(Type::getDoubleTy(context.llvmContext), 2, "iftmp");

        PN->addIncoming(ThenV, thenBlock);
        PN->addIncoming(ElseV, elseBlock);
        return PN;

    }
    return nullptr;
}


// binary_expression
// ->cast_expression
// OR_OP AND_OP
// '|' '^' '&'
// EQ_OP NE_OP '<' '>' LE_OP GE_OP
// LEFT_OP RIGHT_OP
// '+' '-' '*' '/' '%'
llvm::Value *AstBinaryExpr::codegen(CodeGen &context) {
    // cast expression
    if(this->isCastExpr()) {
        return this->astCastExpr->codegen(context);
    }
    // binary operation
    std::cout << "Generate binary expression" << std::endl;

    Value *L = this->front_expr->codegen(context);
    Value *R = this->back_expr->codegen(context);

    std::cout << context.typeSystem.getTypeStr(L->getType()) << std::endl;
    std::cout << context.typeSystem.getTypeStr(R->getType()) << std::endl;

    if(context.isIdentifier(L))
        L = context.builder.CreateLoad(L);
    if(context.isIdentifier(R))
        R = context.builder.CreateLoad(R);

    Type *LType = L->getType();
    Type *RType = R->getType();
    if(RType->isArrayTy()) R = context.builder.CreateBitCast(R, LType, "castR");

    std::cout << context.typeSystem.getTypeStr(LType) << std::endl;
    std::cout << context.typeSystem.getTypeStr(RType) << std::endl;

    bool isFloat = false;
    if( (LType->getTypeID() == Type::DoubleTyID) || (RType->getTypeID() == Type::DoubleTyID) ){  // type upgrade
        isFloat = true;
        if( (RType->getTypeID() != Type::DoubleTyID) ){
            R = context.builder.CreateUIToFP(R, Type::getDoubleTy(context.llvmContext), "ftmp");
        }
        if( (LType->getTypeID() != Type::DoubleTyID) ){
            L = context.builder.CreateUIToFP(L, Type::getDoubleTy(context.llvmContext), "ftmp");
        }
    }

    std::string op = this->getOperator();

    Value *res;
    if(op=="&&") {
        L = context.CastToBoolean(context, L);
        R = context.CastToBoolean(context, R);
        res = context.builder.CreateAnd(L, R, "and(i)tmp");
    }
    else if(op=="||") {
        L = context.CastToBoolean(context, L);
        R = context.CastToBoolean(context, R);
        res = context.builder.CreateOr(L, R, "or(i)tmp");
    }
    else if(op=="&") {
        res = isFloat ? LogErrorV("Double type has no AND operation") : context.builder.CreateAnd(L, R, "andtmp");
    }
    else if(op=="|") {
        res = isFloat ? LogErrorV("Double type has no OR operation") : context.builder.CreateOr(L, R, "ortmp");
    }
    else if(op=="^") {
        res =  isFloat ? LogErrorV("Double type has no XOR operation") : context.builder.CreateXor(L, R, "xortmp");
    }
    else if(op=="==") {
        res =  isFloat ? context.builder.CreateFCmpOEQ(L, R, "cmpftmp") : context.builder.CreateICmpEQ(L, R, "cmptmp");
    } else if(op=="!=") {
        res =  isFloat ? context.builder.CreateFCmpONE(L, R, "cmpftmp") : context.builder.CreateICmpNE(L, R, "cmptmp");
    } else if(op==">=") {
        res =  isFloat ? context.builder.CreateFCmpOGE(L, R, "cmpftmp") : context.builder.CreateICmpSGE(L, R, "cmptmp");
    } else if(op=="<=") {
        res =  isFloat ? context.builder.CreateFCmpOLE(L, R, "cmpftmp") : context.builder.CreateICmpSLE(L, R, "cmptmp");
    } else if(op=="<") {
        res =  isFloat ? context.builder.CreateFCmpULT(L, R, "cmpftmp") : context.builder.CreateICmpULT(L, R, "cmptmp");
    } else if(op==">") {
        res =  isFloat ? context.builder.CreateFCmpOGT(L, R, "cmpftmp") : context.builder.CreateICmpSGT(L, R, "cmptmp");
    } else if(op=="<<") {
        res =  isFloat ? LogErrorV("Double type has no LEFT SHIFT operation") : context.builder.CreateShl(L, R, "shltmp");
    } else if(op==">>") {
        res =  isFloat ? LogErrorV("Double type has no RIGHT SHIFT operation") : context.builder.CreateAShr(L, R, "ashrtmp");
    } else if(op=="+") {
        res =  isFloat ? context.builder.CreateFAdd(L, R, "addftmp") : context.builder.CreateAdd(L, R, "addtmp");
    } else if(op=="-") {
        res =  isFloat ? context.builder.CreateFSub(L, R, "subftmp") : context.builder.CreateSub(L, R, "subtmp");
    } else if(op=="*") {
        res =  isFloat ? context.builder.CreateFMul(L, R, "mulftmp") : context.builder.CreateMul(L, R, "multmp");
    } else if(op=="/") {
        res =  isFloat ? context.builder.CreateFDiv(L, R, "divftmp") : context.builder.CreateSDiv(L, R, "divtmp");
    } else if(op=="%") {
        res =  LogErrorV("LLVM don't have mod operation: QAQ");  //TODO Mod Op Later
    } else {
        res =  LogErrorV("Unknown binary operator");
    }

    std::cout << "Binary codegen success" << std::endl;
    std::cout << "Binary return type:" << context.typeSystem.getTypeStr(res->getType()) << std::endl;
    return res;
}

// cast_expression
// cast_expression : unary_expression | '(' type_name ')' cast_expression
// TODO
llvm::Value* AstCastExpr::codegen(CodeGen &context) {

    if(this->isUnaryExpr()) {
        return this->astUnaryExpr->codegen(context);
    } else {  // cast
        std::cout << "Generate cast expression" << std::endl;

        AstCastExpr *cast_expr = this->getCastExpr();
        std::string type = this->getAstTypeName()->getType();
        int ptrLevel = this->getAstTypeName()->getPtrLevel();

        Type *dstType = context.typeSystem.getType(type, ptrLevel);

        Value *tmp = cast_expr->codegen(context);
        Type *srcType = tmp->getType();

        // return context.builder.CreateCast()
        return nullptr;
    }

    return nullptr;
}

// unary_expression
// postfix | ++unary | --unary | unary_operator unary expr
llvm::Value* AstUnaryExpr::codegen(CodeGen &context) {
    if(this->op.length()==0) {  //op==""
        AstPostfixExpr *post_expr = (AstPostfixExpr *)this->getPtr();
        return post_expr->codegen(context);
    }
    else {
        std::cout << "Generate unary expression" << std::endl;

        if(this->op=="++") { // tmpv += 1; return tmpv; ++a
            AstUnaryExpr *unary_expr = (AstUnaryExpr *)this->getPtr();
            Value *tmpv =unary_expr->codegen(context);      // Var value

            Value *t1 = ConstantInt::get(Type::getInt32Ty(context.llvmContext), 1, true); // num = 1
            LoadInst *inst1 = context.builder.CreateLoad(tmpv);
            Value *add1 = context.builder.CreateAdd(inst1, t1, "add1");
            context.builder.CreateStore(add1, tmpv);
            // the return value cannot be assign -- should not return tmpv;
            return context.builder.CreateLoad(tmpv);
        }
        else if(this->op=="--") { //tmpv -= 1; return tmpv;
            AstUnaryExpr *unary_expr = (AstUnaryExpr *)this->getPtr();
            Value *tmpv =unary_expr->codegen(context);      // Var value

            Value *t1 = ConstantInt::get(Type::getInt32Ty(context.llvmContext), 1, true);
            LoadInst *inst1 = context.builder.CreateLoad(tmpv);
            Value *add1 = context.builder.CreateSub(inst1, t1, "sub1");
            context.builder.CreateStore(add1, tmpv);
            // the return value cannot be assign -- should not return tmpv;
            return context.builder.CreateLoad(tmpv);
        }
        else { // op = & * + - ~ !
            AstCastExpr *cast_expr = (AstCastExpr *)this->getPtr();
            Value *tmpv = cast_expr->codegen(context);      // Var value

            if(op=="+") {
                return tmpv->getType()->isPointerTy()?context.builder.CreateLoad(tmpv):tmpv;;
            }
            else if(op=="-") {
                Value *t1 = ConstantInt::get(Type::getInt32Ty(context.llvmContext), 0, true);
                tmpv = tmpv->getType()->isPointerTy()?context.builder.CreateLoad(tmpv):tmpv;
                return context.builder.CreateSub(t1, tmpv, "negtmp");
            }
            else if(op=="!") {
                tmpv = tmpv->getType()->isPointerTy()?context.builder.CreateLoad(tmpv):tmpv;
                tmpv = context.CastToBoolean(context, tmpv);
                return context.builder.CreateNot(tmpv, "nottmp");
            }
            else if(op=="~") {
                tmpv = tmpv->getType()->isPointerTy()?context.builder.CreateLoad(tmpv):tmpv;
                if(tmpv->getType()->getTypeID() == Type::IntegerTyID){
                    Value *t1 = ConstantInt::get(Type::getInt32Ty(context.llvmContext), 0, true);
                    return context.builder.CreateXor(tmpv, t1, "xortmp");
                }
                else return LogErrorV("~ operator must apply to integer");
            }
            else if(op=="&") { //int *p = &a
                // return value is already pointer which points to the address
                Value *res = context.builder.CreateAlloca(tmpv->getType());
                context.builder.CreateStore(tmpv, res);
                return res;
            }
            else if(op=="*"){ // *p = 1;
                // tmpv is the pointer's address
                // get the base type address
                tmpv = context.builder.CreateLoad(tmpv);
                return tmpv;
            }
        }
    }
    return nullptr;
}


// postfix expr
//postfix_expression
//: primary_expression
//| postfix_expression '[' expression ']'
//| postfix_expression '(' ')'
//| postfix_expression '(' argument_expression_list ')'
//| postfix_expression '.' IDENTIFIER |
// postfix_expression PTR_OP IDENTIFIER |
// postfix_expression INC_OP |
// postfix_expression DEC_OP
llvm::Value* AstPostfixExpr::codegen(CodeGen &context) {
    if(this->op=="") {  // primary expr
        return ((AstPrimaryExpr *)this->getPtr())->codegen(context);
    }

    std::cout << "Generate postfix expression" << std::endl;

    // [] for vector indexing
    if(this->op=="[]") { // a[] pointer dereference
        AstPrimaryExpr *primary_expr = (AstPrimaryExpr *)this->getAstPostfixExpr()->getPtr();
        Value *index = ((AstExpression *)this->getPtr())->codegen(context);
        // load value type
        if(index->getType()->getTypeID()==Type::PointerTyID){
            index = context.builder.CreateLoad(index);
        }

        std::string name = primary_expr->getLabel();
        Value* value = context.getSymbolValue(name);
        Value *tmparray = context.builder.CreateLoad(value);
        if(tmparray->getType()->isArrayTy()) {
            Type *ptr  = PointerType::get(tmparray->getType()->getArrayElementType(), 0);
            value = context.builder.CreateBitCast(value, ptr, "castArray2Ptr");
        }
        else value = tmparray;

        std::cout << context.typeSystem.getTypeStr(value->getType()) << std::endl;

        cout << "Generate array: " << name << endl;
        std::vector<Value *> indexes;   // ArrayRef(std::vector)
        indexes.push_back(index);

        auto arrayPtr = context.builder.CreateInBoundsGEP(value, indexes, "elementPtr");
        return arrayPtr;

    }
    // () for invoking function
    else if(this->op=="()") {
        AstPrimaryExpr *primary_expr = (AstPrimaryExpr *)this->getAstPostfixExpr()->getPtr();
        std::string funcName = primary_expr->getLabel();
        cout << "Generating function call of " << funcName << endl;
        Function * calleeF = context.theModule->getFunction(funcName);

        AstArgExprList* arg_list = (AstArgExprList *)this->getPtr();
        std::vector<AstExpression *> arg_vec;
        if(arg_list) arg_vec = arg_list->getAstExpression();

        if( !calleeF ){
            LogErrorV("Function name not found");
        }
//        if( calleeF->arg_size() != arg_vec.size() ){
//            LogErrorV("Function arguments size not match, calleeF=" + std::to_string(calleeF->size()) +
//                        ", this->arguments=" + std::to_string(arg_vec.size())
//                        );
//        }

        std::vector<Value*> argsv;
        for(auto it=arg_vec.begin(); it!=arg_vec.end(); it++){
            Value *tmp = (*it)->codegen(context);
            std::cout << context.typeSystem.getTypeStr(tmp->getType()) << std::endl;
            if(tmp->getType()->getTypeID()==Type::PointerTyID ) {
                tmp = context.builder.CreateLoad(tmp);
                // if(tmp->getType()->isArrayTy())
                //     tmp = context.builder.CreateBitCast(tmp, tmp->getType()->getArrayElementType(), "ary_cast");
            }
            argsv.push_back(tmp);
            if( !argsv.back() ){        // if any argument codegen fail
                LogErrorV("Error in function call: func args error");
                return nullptr;
            }
        }

        return context.builder.CreateCall(calleeF, argsv, "calltmp");
    }
    // TODO -- struct .
    else if(this->op==".") {
        return nullptr;
    }
    // TODO -- struct ptr
    else if(this->op=="->") {
        return nullptr;
    }
    else if(this->op=="++") {
        // Var value
        Value *tmpv = this->getAstPostfixExpr()->codegen(context);
        Value *t1 = ConstantInt::get(Type::getInt32Ty(context.llvmContext), 1, true);
        // Load to register
        LoadInst *inst1 = context.builder.CreateLoad(tmpv);
        // Add 1 operation
        Value *add1 = context.builder.CreateAdd(inst1, t1, "add1");
        // Write Back to stack
        context.builder.CreateStore(add1, tmpv);
        // return original value
        return inst1;
    }
    else if(this->op=="--") {
        // Var value
        Value *tmpv = this->getAstPostfixExpr()->codegen(context);
        Value *t1 = ConstantInt::get(Type::getInt32Ty(context.llvmContext), 1, true);
        // Load to register
        LoadInst *inst1 = context.builder.CreateLoad(tmpv);
        // Sub 1 operation
        Value *sub1 = context.builder.CreateSub(inst1, t1, "sub1");
        // Write Back to stack
        context.builder.CreateStore(sub1, tmpv);
        // return original value
        return inst1;
    }
    else {
        return LogErrorV("Generate postfix expression error: No operator " + this->op );
    }
}


// primary_expression
//: IDENTIFIER | CONSTANT | STRING_LITERAL | '(' expression ')'
llvm::Value * AstPrimaryExpr::codegen(CodeGen &context) {
    std::cout << "Generate primary expression: " << this->getLabel() << std::endl;
    int primary_type = this->getType();

    if(primary_type==1) { // IDENTIFIER -- name char *
        cout << "Generating identifier " << this->getLabel() << endl;
        Value* value = context.getSymbolValue(this->getLabel());
        if( !value ) return LogErrorV("Unknown variable name " + this->getLabel());

        return value;
    }
    else if(primary_type==2) { //CONSTANT f ll l 什么的先不考虑 就考虑整数
//   16进制 {HP}{H}+{IS}?			{ yylval.str = strdup(yytext); RETURN_TOKEN(CONSTANT); }  0[xX][a-fA-F0-9]+(((u|U)(l|L|ll|LL)?)|((l|L|ll|LL)(u|U)?))
//   10进制 {NZ}{D}*{IS}?			{yylval.str = strdup(yytext); RETURN_TOKEN(CONSTANT); } [1-9][0-9]*
//   8进制  "0"{O}*{IS}?			{ yylval.str = strdup(yytext); RETURN_TOKEN(CONSTANT); } 0[0-7]+
//    {CP}?"'"(\\.|[^\\'])+"'"	{ yylval.str = strdup(yytext); RETURN_TOKEN(CONSTANT); } 'a' 字符
//    {D}+{E}{FS}?				{ yylval.str = strdup(yytext); RETURN_TOKEN(CONSTANT); }
//    {D}*"."{D}+{E}?{FS}?		{ yylval.str = strdup(yytext); RETURN_TOKEN(CONSTANT); } [0-9]* '.' [0-9] e? (f|F|l|L)?
//    {D}+"."{E}?{FS}?			{ yylval.str = strdup(yytext); RETURN_TOKEN(CONSTANT); }
        std::string number = this->getLabel();
        try {
            uint64_t num;
            if(number[0]=='\''){
                num = number[1];
                return ConstantInt::get(Type::getInt8Ty(context.llvmContext), num, true);
            }
            if(number[0]=='0') {
                if(number[1]=='X' || number[1]=='x') num = stoi(number, nullptr, 16);
                else num = stoi(number, nullptr, 8);
            } else {
                num = stoi(number, nullptr, 10);
            }
            return ConstantInt::get(Type::getInt32Ty(context.llvmContext), num, true);
        }
        catch (std::invalid_argument &) {
            return LogErrorV( "Invalid_argument" );
        }
        catch (std::out_of_range &) {
            return LogErrorV( "Number out of range" );
        }
        catch (...) {
            return LogErrorV( "Something else error" );
        }

    }
    else if(primary_type==3) { // STRING_LITERAL ""
        std::cout << "Generate STRING_LITERAL: " << this->getLabel() << std::endl;
        Type *tp = context.typeSystem.getType("char", 1); // tp is char * now
        Value *tmp = context.builder.CreateAlloca(tp);
        Value *str = context.builder.CreateGlobalString(this->getLabel(), "string");
        std::cout << context.typeSystem.getTypeStr(str->getType()) << std::endl;
        context.builder.CreateStore(str, tmp);
        return tmp;
    }
    else if(primary_type==4) { // (expression)
        return this->getExpression()->codegen(context);
    }

    return nullptr;
}
