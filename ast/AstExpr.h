//
// Created by Jialiang Chen on 2021/5/24.
//

#ifndef OUR_C_COMPILER_ASTEXPR_H
#define OUR_C_COMPILER_ASTEXPR_H

#include "AstBase.h"
#include "AstType.h"
#include <string>

class AstExpr;
class AstExpression;
class AstCondiExpr;
class AstUnaryExpr;
class AstAssignOp;
class AstArgExprList;
class AstBinaryExpr;
class AstCastExpr;
class AstPrimaryExpr;
class AstPostfixExpr;

class AstExpr :public AstBase {
public:
    AstExpr(std::string nodeType);
};

class AstExpression : public AstExpr {
public:
    AstExpression(AstCondiExpr* astCondiExpr);
    AstExpression(AstUnaryExpr* astUnaryExpr, AstAssignOp* astAssignOp, AstExpression* astAssignExpr);

    AstCondiExpr* getCondiExpr();
    AstUnaryExpr* getUnaryExpr();
    AstAssignOp* getAssignOp();
    AstExpression* getExpression();
    bool isConditionalExpr();
    llvm::Value* codeGen(CodeGen &context);
private:
    bool isCondi = true;
    AstCondiExpr* astCondiExpr;
    AstUnaryExpr* astUnaryExpr;
    AstAssignOp* astAssignOp;
    AstExpression* child_expr;
};
class AstAssignOp: public AstExpr {
public:
    AstAssignOp(std::string op);
    std::string getOperator();
private:
    std::string Operator;
};

class AstUnaryExpr : public AstExpr {
public:
    AstUnaryExpr(std::string op, void *ptr);
    std::string getOperator();
    void * getPtr();

private:
    // op = ""  <--> AstPostfixExpr;
    // INC <--> AstUnaryExpr;
    // DEC <--> AstUnaryExpr
    // op(&|*...) <---> AstCastExpr;
    std::string op;
    void *ptr;
};

class AstArgExprList : public AstExpr {
public:
    AstArgExprList();
    void addExpression(AstExpression* astExpression);
    std::vector<AstExpression*>& getAstAssignExprList();
private:
    std::vector<AstExpression*> astArgExprList;
};

class AstCondiExpr: public AstExpr {
public:
    AstCondiExpr(AstBinaryExpr* binaryExpr);
    AstCondiExpr(AstBinaryExpr* binaryExpr1, AstExpression* astExpression, AstBinaryExpr* binaryExpr2);

    AstBinaryExpr* getAstBinaryExpr_front();
    AstExpression* getAstExpression();
    AstBinaryExpr* getAstBinaryExpr_back();
    bool isExpand();

private:
    bool isCondition;
    AstBinaryExpr* binaryExpr_front;
    AstBinaryExpr* binaryExpr_back;
    AstExpression* astExpression;
};

class AstBinaryExpr : public AstExpr {
public:
    AstBinaryExpr(AstCastExpr *castExpr);
    AstBinaryExpr(AstBinaryExpr *front, std::string op, AstBinaryExpr *back);
    AstCastExpr *getCastExpr();
    AstBinaryExpr* getFrontBinaryExpr();
    AstBinaryExpr* getBackBinaryExpr();
    std::string getOperator();
    bool isCastExpr();

private:
    bool isCast;
    std::string op;
    AstBinaryExpr *front_expr;
    AstBinaryExpr *back_expr;
    AstCastExpr *astCastExpr;
};

class AstCastExpr: public AstExpr {
public:
    AstCastExpr(AstUnaryExpr* astUnaryExpr);
    AstCastExpr(AstTypeName* astTypeName, AstCastExpr* astCastExpr);

    AstUnaryExpr* getUnaryExpr();
    AstCastExpr* getCastExpr();
    AstTypeName* getAstTypeName();
private:
    bool isUnaryExpr;
    AstUnaryExpr* astUnaryExpr;
    AstTypeName* astTypeName;
    AstCastExpr* astCastExpr;
};


class AstPrimaryExpr : public AstExpr {
public:
    AstPrimaryExpr(int type, std::string label);
    AstPrimaryExpr(int type, AstExpression *astExpression);
    AstExpression* getExpression();
    std::string getLabel();

private:
    int type;
    std::string label;
    AstExpression* astExpression;
};

class AstPostfixExpr : public AstExpr {
public:
    AstPostfixExpr(AstPostfixExpr* astPostfixExpr, std::string op);
    AstPostfixExpr(AstPostfixExpr* astPostfixExpr, std::string op, std::string id);
    AstPostfixExpr(AstPostfixExpr* astPostfixExpr, std::string op, void *ptr);

    std::string getOperator();
    void *getPtr();
    AstPostfixExpr *getAstPostfixExpr();
    std::string getIdentifier();
private:
    // op <--> ptr
    // ""   --  primary_expr
    // "[]" --  exprlist
    // "()" --  argument_expr_list
    void* ptr;
    AstPostfixExpr* child_postfix;
    std::string identifier;
    std::string op;
};


#endif //OUR_C_COMPILER_ASTEXPR_H
