//
// Created by Jialiang Chen on 2021/5/24.
//

#ifndef OUR_C_COMPILER_ASTEXPR_H
#define OUR_C_COMPILER_ASTEXPR_H

#include "AstBase.h"
#include "AstDecl.h"
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
class AstInitializer;

class AstExpr :public AstBase {
public:
    AstExpr(std::string nodeType);
    virtual llvm::Value* codegen(CodeGen &context) override;
};

class AstExpression : public AstExpr {
public:
    AstExpression(AstCondiExpr* astCondiExpr);
    AstExpression(AstUnaryExpr* astUnaryExpr, AstAssignOp* astAssignOp, AstExpression* expression);

    AstCondiExpr* getCondiExpr();
    AstUnaryExpr* getUnaryExpr();
    AstAssignOp* getAssignOp();
    AstExpression* getExpression();
    bool isConditionalExpr();
    virtual llvm::Value* codegen(CodeGen &context) override;
private:
    bool isCondi;
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

    virtual llvm::Value* codegen(CodeGen &context) override;
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
    std::vector<AstExpression*>& getAstExpression();
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

    virtual llvm::Value* codegen(CodeGen &context) override;

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

    virtual llvm::Value* codegen(CodeGen &context) override;

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
    bool isUnaryExpr();

    virtual llvm::Value* codegen(CodeGen &context) override;

private:
    bool isUnary;
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
    int getType();

    virtual llvm::Value* codegen(CodeGen &context) override;

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

    virtual llvm::Value* codegen(CodeGen &context) override;

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


class AstInitializer: public AstDecl {
public:
    AstInitializer(AstExpression *astExpression, AstInitList *astInitList);
    AstExpression *getExpression();
    AstInitList *getInitList();
    bool isExpression();

private:
    AstExpression *astExpression;
    AstInitList *astInitList;
};




#endif //OUR_C_COMPILER_ASTEXPR_H
