//==========Todo==============
#include "../../ast/AstExpr.h"
#include "CodeGen.h"

// expression : conditional_expression | unary_expression assignment_operator expression
llvm::Value* AstExpression::codegen(CodeGen &context){
    // conditional_expr
    if(this->astCondiExpr) {
        return this->astCondiExpr->codegen(context);
    }
    else {
        std::cout << "Generate assignment expression" << std::endl;
        Value *L = this->getUnaryExpr()->codegen(context);
        Value *R = this->getExpression()->codegen(context);
        // Operator: ">>=" "<<=" "+=" "-=" "*=" "/=" "%=" "&=" "^=" "|="
        std::string op = this->getAssignOp()->getOperator();
        // is float operation or not
        bool Lf = L->getType()->getTypeID() == Type::DoubleTyID;
        bool Rf = R->getType()->getTypeID() == Type::DoubleTyID;

        Value *res;
        if(!Lf && !Rf) {
            if(op=="+=") res = context.builder.CreateAdd(L, R, "add(i)tmp");
            else if(op=="-=") res = context.builder.CreateSub(L, R, "sub(i)tmp");
            else if(op=="*=") res = context.builder.CreateMul(L, R, "mul(i)tmp");
            else if(op=="/=") res = context.builder.CreateSDiv(L, R, "div(i)tmp");
            else if(op=="%=") res = LogErrorV("LLVM don't have mod operation: QAQ");  //TODO Mod Op Later
            else if(op=="&=") res = context.builder.CreateAnd(L, R, "and(i)tmp");
            else if(op=="|=") res = context.builder.CreateOr(L, R, "or(i)tmp");
            else if(op=="^=") res = context.builder.CreateXor(L, R, "xor(i)tmp");
            else if(op=="<<=") res = context.builder.CreateShl(L, R, "shl(i)tmp");
            else if(op==">>=") res = context.builder.CreateAShr(L, R, "shr(i)tmp");
            else res = LogErrorV("Unknown operator in assignment_expression");
        }
        else {
            // change L & R to double
            if(!Lf) L = context.builder.CreateUIToFP(L, Type::getDoubleTy(context.llvmContext), "ftmpL");
            if(!Rf) R = context.builder.CreateUIToFP(R, Type::getDoubleTy(context.llvmContext), "ftmpR");

            if(op=="+=") res = context.builder.CreateFAdd(L, R, "add(f)tmp");
            else if(op=="-=") res = context.builder.CreateFSub(L, R, "sub(f)tmp");
            else if(op=="*=") res = context.builder.CreateFMul(L, R, "mul(f)tmp");
            else if(op=="/=") res = context.builder.CreateFDiv(L, R, "div(f)tmp");
            else if(op=="%=") res = LogErrorV("operator's type: 'double', invalid operands '%='");
            else if(op=="&=") res = LogErrorV("operator's type: 'double', invalid operands '&='");
            else if(op=="|=") res = LogErrorV("operator's type: 'double', invalid operands '|='");
            else if(op=="^=") res = LogErrorV("operator's type: 'double', invalid operands '^='");
            else if(op=="<<=") res = LogErrorV("operator's type: 'double', invalid operands '<<='");
            else if(op==">>=") res = LogErrorV("operator's type: 'double', invalid operands '>>='");
            else res = LogErrorV("Unknown operator in assignment_expression");
        }

        if(res) {
            // if L is double originally, should change back to int after assignment.
            if(!Lf) res=context.builder.CreateFPToUI(res, Type::getDoubleTy(context.llvmContext), "itmp");
            context.builder.CreateStore(res, L);
        }
        return L;
    }

    return nullptr;
}


// conditional_expression :
llvm::Value* AstCondiExpr::codegen(CodeGen &context) {
    if(!this->isExpand()) { // binary_expression
        return this->binaryExpr_back->codegen(context);
    }
    else {
        // TODO s
        AstBinaryExpr *b_front = this->getAstBinaryExpr_front();
        AstExpression *expr = this->getAstExpression();
        AstBinaryExpr *b_back = this->getAstBinaryExpr_back();

        Value *judge = b_front->codegen(context);
        // compare judge with 0;
        // Value *zero = ConstantInt::get(Type::getInt32Ty(context.llvmContext), 0, true);
        judge = context.CastToBoolean(context, judge)
        context.builder.CreateICmpEQ(judge, zero, "cmp0");


    }
    return nullptr;
}

// binary_expression :
//cast_expression
//binary_expression OR_OP   binary_expression
//binary_expression AND_OP  binary_expression {
//binary_expression '|'     binary_expression {
//binary_expression '^'     binary_expression {
//binary_expression '&'     binary_expression {
//binary_expression EQ_OP   binary_expression {
//binary_expression NE_OP   binary_expression {
//binary_expression '<'     binary_expression {
//binary_expression '>'     binary_expression {
//binary_expression LE_OP   binary_expression {
//binary_expression GE_OP   binary_expression {
//binary_expression LEFT_OP binary_expression {
//binary_expression RIGHT_OP   binary_expression {
//binary_expression '+'     binary_expression {
//binary_expression '-'     binary_expression {
//binary_expression '*'     binary_expression {
//binary_expression '/'     binary_expression {
//binary_expression '%'     binary_expression {

llvm::Value *AstBinaryExpr::codegen(CodeGen &context) {
    // cast expression
    if(this->isCastExpr()) {
        return this->astCastExpr->codegen(context);
    }
    // binary operation
    std::string op = this->getOperator();
    Value *L = this->front_expr->codegen(context);
    Value *R = this->back_expr->codegen(context);
    bool isFloat = false;

    if( (L->getType()->getTypeID() == Type::DoubleTyID) || (R->getType()->getTypeID() == Type::DoubleTyID) ){  // type upgrade
        isFloat = true;
        if( (R->getType()->getTypeID() != Type::DoubleTyID) ){
            R = context.builder.CreateUIToFP(R, Type::getDoubleTy(context.llvmContext), "ftmp");
        }
        if( (L->getType()->getTypeID() != Type::DoubleTyID) ){
            L = context.builder.CreateUIToFP(L, Type::getDoubleTy(context.llvmContext), "ftmp");
        }
    }

    if(op=="&&") {
        L = CastToBoolean(context, L);
        R = CastToBoolean(context, R);
        return context.builder.CreateAnd(L, R, "and(i)tmp");
    } else if(op=="||") {
        L = CastToBoolean(context, L);
        R = CastToBoolean(context, R);
        return context.builder.CreateOr(L, R, "or(i)tmp");
    } else if(op=="&") {
        return isFloat ? LogErrorV("Double type has no AND operation") : context.builder.CreateAnd(L, R, "andtmp");
    } else if(op=="|") {
        return isFloat ? LogErrorV("Double type has no OR operation") : context.builder.CreateOr(L, R, "ortmp");
    } else if(op=="^") {
        return isFloat ? LogErrorV("Double type has no XOR operation") : context.builder.CreateXor(L, R, "xortmp");
    } else if(op=="==") {
        return isFloat ? context.builder.CreateFCmpOEQ(L, R, "cmpftmp") : context.builder.CreateICmpEQ(L, R, "cmptmp");
    } else if(op=="!=") {
        return isFloat ? context.builder.CreateFCmpONE(L, R, "cmpftmp") : context.builder.CreateICmpNE(L, R, "cmptmp");
    } else if(op==">=") {
        return isFloat ? context.builder.CreateFCmpOGE(L, R, "cmpftmp") : context.builder.CreateICmpSGE(L, R, "cmptmp");
    } else if(op=="<=") {
        return isFloat ? context.builder.CreateFCmpOLE(L, R, "cmpftmp") : context.builder.CreateICmpSLE(L, R, "cmptmp");
    } else if(op=="<") {
        return isFloat ? context.builder.CreateFCmpULT(L, R, "cmpftmp") : context.builder.CreateICmpULT(L, R, "cmptmp");
    } else if(op==">") {
        return isFloat ? context.builder.CreateFCmpOGT(L, R, "cmpftmp") : context.builder.CreateICmpSGT(L, R, "cmptmp");
    } else if(op=="<<") {
        return isFloat ? LogErrorV("Double type has no LEFT SHIFT operation") : context.builder.CreateShl(L, R, "shltmp");
    } else if(op==">>") {
        return isFloat ? LogErrorV("Double type has no RIGHT SHIFT operation") : context.builder.CreateAShr(L, R, "ashrtmp");
    } else if(op=="+") {
        return isFloat ? context.builder.CreateFAdd(L, R, "addftmp") : context.builder.CreateAdd(L, R, "addtmp");
    } else if(op=="-") {
        return isFloat ? context.builder.CreateFSub(L, R, "subftmp") : context.builder.CreateSub(L, R, "subtmp");
    } else if(op=="*") {
        return isFloat ? context.builder.CreateFMul(L, R, "mulftmp") : context.builder.CreateMul(L, R, "multmp");
    } else if(op=="/") {
        return isFloat ? context.builder.CreateFDiv(L, R, "divftmp") : context.builder.CreateSDiv(L, R, "divtmp");
    } else if(op=="%") {
        return LogErrorV("LLVM don't have mod operation: QAQ");  //TODO Mod Op Later
    } else {
        return LogErrorV("Unknown binary operator");
    }

    return nullptr;

}

// cast_expression
// cast_expression : unary_expression | '(' type_name ')' cast_expression
llvm::Value* AstCastExpr::codegen(CodeGen &context) {
    if(this->isUnaryExpr()) {
        return this->astUnaryExpr->codegen(context);
    } else {  // cast
        AstCastExpr *cast_expr = this->getCastExpr();
        std::string type = this->getAstTypeName()->getType();
        int ptrLevel = this->getAstTypeName()->getPtrLevel();

        Type *dstType = context.typeSystem.getType(type, ptrLevel);

        Value *tmp = cast_expr->codegen(context);
        Type *srcType = tmp->getType();

        return context.builder.CreateCast()
    }

    return nullptr;
}

// unary_expression
// postfix | ++unary | --unary | unary_operator unaryexpr
llvm::Value* AstUnaryExpr::codegen(CodeGen &context) {
    if(this->op.length()==0) {  //op==""
        AstPostfixExpr *post_expr = (AstPostfixExpr *)this->getPtr();
        return post_expr->codegen(context);
    }
    else {
        AstUnaryExpr *unary_expr = (AstUnaryExpr *)this->getPtr();

        if(this->op=="++") { // tmpv += 1; return tmpv;
            Value *tmpv = unary_expr->codegen(context);
            uint64_t num = 1;
            Value *t1 = ConstantInt::get(Type::getInt32Ty(context.llvmContext), num, true);
            return tmpv = context.builder.CreateAdd(tmpv, t1, "++op");
        } else if(this->op=="--") { tmpv -= 1; return tmpv;
            Value *tmpv = unary_expr->codegen(context);
            uint64_t num = 1;
            Value *t1 = ConstantInt::get(Type::getInt32Ty(context.llvmContext), num, true);
            return tmpv = context.builder.CreateSub(tmpv, t1, "--op");
        } else { // op = % * + - ~ !
            if(op=="+") {return unary_expr->codegen(context)};
            else if(op=="-") {

            }
            else if(op=="!") {
                Value *tmpv = unary_expr->codegen(context);
                tempv = CastToBoolean(context, tempv);
                if(tmpv->getType()->getTypeID() == Type::IntegerTyID){
                    return context.builder.CreateNot(tempv, "nottmp");
                }
                else return LogErrorV("~ operator must apply to numerics");

            }
            else if(op=="~") {
                Value *tmpv = unary_expr->codegen(context);
                if(tmpv->getType()->getTypeID() == Type::IntegerTyID){
                    Value *t1 = ConstantInt::get(Type::getInt32Ty(context.llvmContext), 0, true);
                    return context.builder.CreateXor(tmpv, t1, "xortmp");
                }
                else return LogErrorV("~ operator must apply to integer");
            }
            else if(op=="%") {
                return LogErrorV("Unknown % operator");
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
    else if(this->op=="[]") {

    } else if(this->op=="()") {

    } else if(this->op==".") {

    } else if(this->op=="->") {

    } else if(this->op=="++") {
        
    } else if(this->op=="--") {

    }
    return nullptr;
}


// primary_expression
//: IDENTIFIER | CONSTANT | STRING_LITERAL | '(' expression ')'
llvm::Value * AstPrimaryExpr::codegen(CodeGen &context) {
    int primary_type = this->getType();

    if(primary_type==1) { // IDENTIFIER -- name char *
        this->getLabel();
    }
    else if(primary_type==2) { //CONSTANT f ll l 什么的先不考虑 就考虑整数
//   16进制 {HP}{H}+{IS}?			{ yylval.str = strdup(yytext); RETURN_TOKEN(CONSTANT); }  0[xX][a-fA-F0-9]+(((u|U)(l|L|ll|LL)?)|((l|L|ll|LL)(u|U)?))
//   10进制 {NZ}{D}*{IS}?			{yylval.str = strdup(yytext); RETURN_TOKEN(CONSTANT); } [1-9][0-9]*
//   8进制  "0"{O}*{IS}?			{ yylval.str = strdup(yytext); RETURN_TOKEN(CONSTANT); } 0[0-7]+
//    {CP}?"'"(\\.|[^\\'])+"'"	{ yylval.str = strdup(yytext); RETURN_TOKEN(CONSTANT); }
//    {D}+{E}{FS}?				{ yylval.str = strdup(yytext); RETURN_TOKEN(CONSTANT); }
//    {D}*"."{D}+{E}?{FS}?		{ yylval.str = strdup(yytext); RETURN_TOKEN(CONSTANT); } [0-9]* '.' [0-9] e? (f|F|l|L)?
//    {D}+"."{E}?{FS}?			{ yylval.str = strdup(yytext); RETURN_TOKEN(CONSTANT); }
        std::string number = this->getLabel();
        try {
            uint64_t num;
            if(number[0]=='0') {
                if(number[1]=='X' || number[1]=='x') num = stoi(number, nullptr, 16);
                else num = stoi(number, nullptr, 8);
            } else {
                num = stoi(number, nullptr, 10);
            }
            return ConstantInt::get(Type::getInt32Ty(context.llvmContext), num, true);
        }
        catch (std::invalid_argument &) {
            std::cout << "Invalid_argument" << std::endl;
        }
        catch (std::out_of_range &) {
            std::cout << "Number out of range" << std::endl;
        }
        catch (...) {
            std::cout << "Something else error" << std::endl;
        }
    }
    else if(primary_type==3) { // STRING_LITERAL ""

    }
    else if(primary_type==4) { // (expression)
        return this->getExpression()->codegen(context);
    }

    return nullptr;
}
