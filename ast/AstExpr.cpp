//
// Created by Jialiang Chen on 2021/5/24.
//

#include "AstExpr.h"

//class AstExpr;
AstExpr::AstExpr(std::string nodeType)
        :AstBase(nodeType){}

llvm::Value* AstExpr::codegen(CodeGen &context) {
    return nullptr;
}

//class AstExpression;

AstExpression::AstExpression(AstCondiExpr *astCondiExpr)
: AstExpr("expression")
{
    this->astCondiExpr = astCondiExpr;
    this->child_expr = nullptr;
    this->astAssignOp = nullptr;
    this->astUnaryExpr = nullptr;
    this->isCondi = true;
}
AstExpression::AstExpression(AstUnaryExpr *astUnaryExpr, AstAssignOp *astAssignOp, AstExpression *expression)
: AstExpr("expression")
{
    this->isCondi = false;
    this->child_expr = expression;
    this->astAssignOp = astAssignOp;
    this->astUnaryExpr = astUnaryExpr;
    this->astCondiExpr = nullptr;
}
AstUnaryExpr * AstExpression::getUnaryExpr() {
    return this->astUnaryExpr;
}
AstAssignOp * AstExpression::getAssignOp() {
    return this->astAssignOp;
}
AstExpression * AstExpression::getExpression() {
    return this->child_expr;
}
AstCondiExpr * AstExpression::getCondiExpr() {
    return this->astCondiExpr;
}
bool AstExpression::isConditionalExpr() {
    std::cout<<isCondi<<std::endl;
    return isCondi;
}

// class AstCondiExpr;
AstCondiExpr::AstCondiExpr(AstBinaryExpr *binaryExpr)
: AstExpr("conditional_expression")
{
    this->isCondition = false;
    this->binaryExpr_front = nullptr;
    this->astExpression = nullptr;
    this->binaryExpr_back = binaryExpr;
}
AstCondiExpr::AstCondiExpr(AstBinaryExpr *binaryExpr1, AstExpression *astExpression, AstBinaryExpr *binaryExpr2)
: AstExpr("conditional_expression")
{
    this->isCondition = true;
    this->binaryExpr_front = binaryExpr1;
    this->astExpression = astExpression;
    this->binaryExpr_back = binaryExpr2;
}
AstBinaryExpr * AstCondiExpr::getAstBinaryExpr_back() {
    return this->binaryExpr_back;
}
AstBinaryExpr * AstCondiExpr::getAstBinaryExpr_front() {
    return this->binaryExpr_front;
}
AstExpression * AstCondiExpr::getAstExpression() {
    return this->astExpression;
}
bool AstCondiExpr::isExpand() {
    return this->isCondition;
}

//class AstUnaryExpr;
AstUnaryExpr::AstUnaryExpr(std::string op, void *ptr)
: AstExpr("unary_expression")
{
    this->op = op;
    this->ptr = ptr;
}
std::string AstUnaryExpr::getOperator() {
    return this->op;
}
void * AstUnaryExpr::getPtr() {
    return this->ptr;
}

// class AstAssignOp;
AstAssignOp::AstAssignOp(std::string op)
: AstExpr("assignment_operator")
{
    this->Operator = op;
}
std::string AstAssignOp::getOperator() {
    return this->Operator;
}

// class AstArgExprList;
AstArgExprList::AstArgExprList()
: AstExpr("argument_expression_list") {}
void AstArgExprList::addExpression(AstExpression *astExpression) {
    this->astArgExprList.push_back(astExpression);
}
std::vector<AstExpression *> & AstArgExprList::getAstExpression() {
    return this->astArgExprList;
}

// class AstBinaryExpr;
AstBinaryExpr::AstBinaryExpr(AstCastExpr *castExpr)
: AstExpr("binary_expression")
{
    this->isCast = true;
    this->astCastExpr = castExpr;
}
AstBinaryExpr::AstBinaryExpr(AstBinaryExpr *front, std::string op, AstBinaryExpr *back)
: AstExpr("binary_expression")
{
    this->isCast = false;
    this->front_expr = front;
    this->back_expr = back;
    this->op = op;
}
std::string AstBinaryExpr::getOperator() {
    return this->op;
}
AstBinaryExpr * AstBinaryExpr::getBackBinaryExpr() {
    return this->back_expr;
}
AstBinaryExpr * AstBinaryExpr::getFrontBinaryExpr() {
    return this->front_expr;
}
AstCastExpr * AstBinaryExpr::getCastExpr() {
    return this->astCastExpr;
}
bool AstBinaryExpr::isCastExpr() {
    return this->isCast;
}

// class AstCastExpr
AstCastExpr::AstCastExpr(AstUnaryExpr *astUnaryExpr)
: AstExpr("cast_expression")
{
    this->isUnary = true;
    this->astUnaryExpr = astUnaryExpr;
}
AstCastExpr::AstCastExpr(AstTypeName *astTypeName, AstCastExpr *astCastExpr)
:AstExpr("cast_expression")
{
    this->isUnary = false;
    this->astTypeName = astTypeName;
    this->astCastExpr = astCastExpr;
}
AstCastExpr * AstCastExpr::getCastExpr() {
    return this->astCastExpr;
}
AstUnaryExpr * AstCastExpr::getUnaryExpr() {
    return this->astUnaryExpr;
}
AstTypeName * AstCastExpr::getAstTypeName() {
    return this->astTypeName;
}
bool AstCastExpr::isUnaryExpr() {
    return this->isUnary;
}

// class AstPrimaryExpr;
AstPrimaryExpr::AstPrimaryExpr(int type, std::string label)
: AstExpr("primary_expression")
{
    this->type = type;
    this->label = label;
}
AstPrimaryExpr::AstPrimaryExpr(int type, AstExpression *astExpression)
: AstExpr("primary_expression")
{
    this->type = type;
    this->astExpression = astExpression;
}
AstExpression * AstPrimaryExpr::getExpression() {
    return this->astExpression;
}
std::string AstPrimaryExpr::getLabel() {
    return this->label;
}

// class AstPostfixExpr;
AstPostfixExpr::AstPostfixExpr(AstPostfixExpr *astPostfixExpr, std::string op)
: AstExpr("postfix_expression")
{
    this->child_postfix = astPostfixExpr;
    this->op = op;
    this->identifier = "";
    this->ptr = nullptr;
}

AstPostfixExpr::AstPostfixExpr(AstPostfixExpr *astPostfixExpr, std::string op, void *ptr)
: AstExpr("postfix_expression")
{
    this->child_postfix = astPostfixExpr;
    this->op = op;
    this->identifier = "";
    this->ptr = ptr;
}
AstPostfixExpr::AstPostfixExpr(AstPostfixExpr *astPostfixExpr, std::string op, std::string id)
: AstExpr("postfix_expression")
{
    this->child_postfix = astPostfixExpr;
    this->op = op;
    this->identifier = id;
    this->ptr = nullptr;
}
std::string AstPostfixExpr::getOperator() {
    return this->op;
}
void * AstPostfixExpr::getPtr() {
    return ptr;
}
std::string AstPostfixExpr::getIdentifier() {
    return this->identifier;
}
AstPostfixExpr * AstPostfixExpr::getAstPostfixExpr() {
    return this->child_postfix;
}

int AstPrimaryExpr::getType() {
    return this->type;
}

// AstInitializer
AstInitializer::AstInitializer(AstExpression *astExpression, AstInitList *astInitList)
: AstDecl("initializer")
{
    this->astExpression = astExpression;
    this->astInitList = astInitList;
}
AstInitList * AstInitializer::getInitList() {
    return this->astInitList;
}
AstExpression * AstInitializer::getExpression() {
    return this->astExpression;
}

