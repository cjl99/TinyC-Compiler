//
// Created by Jialiang Chen on 2021/5/24.
//

#include "AstExpr.h"

AstExpr::AstExpr(std::string nodeType)
        :AstBase(nodeType){}

AstExprList *AstPrimaryExpr::getExpr() const{
    return astExpr;
}

AstPrimaryExpr::AstPrimaryExpr(std::string label, AstExprList* astExpr) 
                :AstExpr("primary_expression")
{
    this->astExpr = astExpr;
    this->label = label;
    // printf("%s\n", (this->label).c_str());
}
std::string AstPrimaryExpr::getLabel() const{
    return label;
}

/*
 * class AstPostfixExpr
 * */
AstPostfixExpr::AstPostfixExpr(std::string op, AstPostfixExpr* postfix):AstExpr("postfix_expression")
{
    this->op = op;
    this->astPostfixExpr = postfix;;
    this->ptr = nullptr;
    this->id = "";
}

AstPostfixExpr::AstPostfixExpr(std::string op, AstPostfixExpr* astPostfixExpr, std::string id):AstExpr("postfix_expression")
{
    this->op = op;
    this->astPostfixExpr = astPostfixExpr;
    this->ptr = nullptr;
    this->id = id;
}

AstPostfixExpr::AstPostfixExpr(std::string op, AstPostfixExpr* astPostfixExpr, void *ptr) :AstExpr("postfix_expression")
{
    this->op = op;
    this->astPostfixExpr = astPostfixExpr;
    this->ptr = ptr;
    this->id = "";
}

std::string AstPostfixExpr::getOperator() {
    return this->op;
}
void* AstPostfixExpr::getPtr() {
    return this->ptr;
}
AstPostfixExpr* AstPostfixExpr::getAstPostfixExpr() {
    return this->astPostfixExpr;
}
std::string AstPostfixExpr::getIdentifier() {
    return this->id;
}

AstArgExprList::AstArgExprList() :AstExpr("argument_expression_list")
{}

void AstArgExprList::addAssignExpr(AstAssignExpr *astAssignExpr1) {
    this->astArgExprList.push_back(astAssignExpr1);
}

std::vector<AstAssignExpr*>& AstArgExprList::getAstAssignExprList() {
    return this->astArgExprList;
}

AstUnaryExpr::AstUnaryExpr(std::string op, void *ptr) :AstExpr("unary_expression")
{
    this->op = op;
    this->ptr = ptr;
    this->type = "";
}

AstUnaryExpr::AstUnaryExpr(std::string op, void *ptr, std::string type) :AstExpr("unary_expression")
{
    this->op = op;
    this->ptr = ptr;
    this->type = type;
}
std::string AstUnaryExpr::getOperator() {
    return this->op;
}
void * AstUnaryExpr::getPtr() {
    return this->ptr;
}
std::string AstUnaryExpr::getType() {
    return this->type;
}

AstCastExpr::AstCastExpr(AstUnaryExpr *astUnaryExpr) :AstExpr("cast_expression")
{
    this->astUnaryExpr = astUnaryExpr;
    this->type = 0;
}

AstCastExpr::AstCastExpr(AstTypeName *astTypeName, AstCastExpr* astCastExpr) :AstExpr("cast_expression")
{
    this->astTypeName = astTypeName;
    this->astCastExpr = astCastExpr;
    this->type = 1;
}

int AstCastExpr::getType() {
    return this->type;
}
AstCastExpr* AstCastExpr::getAstCastExpr() {
    return this->astCastExpr;
}
AstTypeName* AstCastExpr::getAstTypeName() {
    return this->astTypeName;
}
AstUnaryExpr* AstCastExpr::getAstUnaryExpr() {
    return this->astUnaryExpr;
}

// AstCalcuExpr
AstCalcuExpr::AstCalcuExpr() 
            :AstExpr("calculate_expression")
{
    // use default
    this->exprType = "calcu";
}

AstCalcuExpr::AstCalcuExpr(std::string type) 
            :AstExpr("calculate_expression")
{
    this->exprType = type;
}

void AstCalcuExpr::addCalcuExpr(AstCalcuExpr *astCalcuExpr1) {
    this->astCalcuExprList.push_back(astCalcuExpr1);
}

void AstCalcuExpr::addCastExpr(AstCastExpr* astCastExpr) {
    this->astCastExpr.push_back(astCastExpr);
}

void AstCalcuExpr::addOperator(std::string op) {
    this->opList.push_back(op);
}

std::string AstCalcuExpr::getExprtype() {
    return this->exprType;
}

std::vector<AstCalcuExpr *>& AstCalcuExpr::getCalcuExprList() {
    return this->astCalcuExprList;
}

std::vector<AstCastExpr *>& AstCalcuExpr::getCastExprList() {
    return this->astCastExpr;
}

std::vector<std::string>& AstCalcuExpr::getOpList() {
    return this->opList;
}

bool AstCalcuExpr::isCorrect() {
    int exprSize = this->astCalcuExprList.size();
    int opSize = this->opList.size();
    if(exprSize-opSize==1) return true;
    return false;
}

AstCondiExpr::AstCondiExpr(AstCalcuExpr *astCalcuExpr) 
            :AstExpr("conditional_expression")
{
    this->astCalcuExpr = astCalcuExpr;
    this->isLow = true;
}

AstCondiExpr::AstCondiExpr(AstCalcuExpr *astCalcuExpr, AstExprList *astExpr, AstCondiExpr *astCondiExpr) 
            :AstExpr("conditional_expression")
{
    this->astCondiExpr = astCondiExpr;
    this->astExpr = astExpr;
    this->astCalcuExpr = astCalcuExpr;
    this->isLow = false;
}

AstCalcuExpr* AstCondiExpr::getAstCalcuExpr() {
    return this->astCalcuExpr;
}
AstExprList* AstCondiExpr::getAstExpr(){
    return this->astExpr;
}
AstCondiExpr* AstCondiExpr::getAstCondiExpr(){
    return this->astCondiExpr;
}


AstAssignExpr::AstAssignExpr(AstCondiExpr *astCondiExpr1) 
            :AstExpr("assignment_expression")
{
    this->child_AssignExpr = nullptr;
    this->astCondiExpr = astCondiExpr1;
    this->astAssignOp = nullptr;
    this->astUnaryExpr = nullptr;
    this->isCondi = true;
}

AstAssignExpr::AstAssignExpr(AstUnaryExpr *astUnaryExpr1, AstAssignOp *astAssignOp1, AstAssignExpr *astAssignExpr1) 
                :AstExpr("assignment_expression")
{
    this->child_AssignExpr = astAssignExpr1;
    this->astCondiExpr = nullptr;
    this->astAssignOp = astAssignOp1;
    this->astUnaryExpr = astUnaryExpr1;
    this->isCondi = false;
}

AstCondiExpr* AstAssignExpr::getAstCondiExpr() {
    return this->astCondiExpr;
}
AstUnaryExpr* AstAssignExpr::getAstUnaryExpr() {
    return this->astUnaryExpr;
}
AstAssignOp* AstAssignExpr::getAstAssignOp() {
    return this->astAssignOp;
}
AstAssignExpr* AstAssignExpr::getAstAssignExpr() {
    return this->child_AssignExpr;
}


AstAssignOp::AstAssignOp(std::string op) 
            :AstExpr("assignment_operator")
{
    this->Operator = op;
}

std::string AstAssignOp::getOperator() {
    return this->Operator;
}

AstExprList::AstExprList() 
            :AstExpr("expression"){}

void AstExprList::addAssignExpr2(AstAssignExpr *assignExpr) {
    this->AstAssignExprList.push_back(assignExpr);
}

std::vector<AstAssignExpr *> AstExprList::getAstAssignExprList() {
    return this->AstAssignExprList;
}