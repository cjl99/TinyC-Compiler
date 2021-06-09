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

    }
    return nullptr;
}


// conditional_expression : binary_expression  | binary_expression '?' expression ':' binary_expression
llvm::Value* AstCondiExpr::codegen(CodeGen &context) {
    if(!this->isExpand()) {
        return this->binaryExpr_back->codegen(context);
    }
    else {

    }
    return nullptr;
}

// binary_expression
//binary_expression : cast_expression {
//binary_expression    binary_expression
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
    if(this->isCastExpr()) {
        return this->astCastExpr->codegen(context);
    }
    else {

    }

    return nullptr;
}

// cast_expression
// cast_expression : unary_expression | '(' type_name ')' cast_expression
llvm::Value* AstCastExpr::codegen(CodeGen &context) {
    if(this->isUnaryExpr()) {
        return this->astUnaryExpr->codegen(context);
    } else {  // cast

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
        if(this->op=="++") {
            Value *tmpv =unary_expr->codegen(context);
            // tmpv += 1; return tmpv;
        } else if(this->op=="--") {

        } else {

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
