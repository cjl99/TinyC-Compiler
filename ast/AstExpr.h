//
// Created by Jialiang Chen on 2021/5/24.
//

#ifndef OUR_C_COMPILER_ASTEXPR_H
#define OUR_C_COMPILER_ASTEXPR_H

#include "AstBase.h"
#include "AstType.h"
#include "AstDecl.h"

class AstExpr;
class AstPrimaryExpr;
class AstPostfixExpr;
class AstAssignExpr;
class AstArgExprList;
class AstUnaryExpr;
class AstCastExpr;
class AstCalcuExpr;
class AstCondiExpr;
class AstAssignOp;
class AstExprList;


class AstExpr : public AstBase {
public:
    AstExpr(std::string nodeType);
};

class AstPrimaryExpr : public AstExpr {
public:
    AstPrimaryExpr(std::string label, AstExprList* astExpr);
    AstExprList* getExpr() const;
    std::string getLabel() const;
private:
    AstExprList* astExpr;
    std::string label;
};

class AstPostfixExpr : public AstExpr {
public:

    AstPostfixExpr(std::string op, AstPostfixExpr* astPostfixExpr);
    AstPostfixExpr(std::string op, AstPostfixExpr* astPostfixExpr, std::string id);
    AstPostfixExpr(std::string op, AstPostfixExpr* astPostfixExpr, void *ptr);
    // op <--> ptr
    // ""       primary_expr
    // "[]" --  exprlist
    // "()" --  argument_expr_list 

    std::string getOperator();
    void *getPtr();
    AstPostfixExpr *getAstPostfixExpr();
    std::string getIdentifier();
private:
    void* ptr;
    AstPostfixExpr* astPostfixExpr;
    std::string id;
    std::string op;
};

class AstArgExprList : public AstExpr {
public:
    AstArgExprList();
    void addAssignExpr(AstAssignExpr* astAssignExpr);
    std::vector<AstAssignExpr*>& getAstAssignExprList();
private:
    std::vector<AstAssignExpr*> astArgExprList;
};

class AstUnaryExpr : public AstExpr {
public:
    AstUnaryExpr(std::string op, void *ptr);
    AstUnaryExpr(std::string op, void *ptr, std::string type);
    std::string getOperator();
    void * getPtr();
    std::string getType();

private:
    std::string op;
    void *ptr;
    std::string type;
    // op = ""  <--> AstPostfixExpr;
    // INC <--> AstUnaryExpr;
    // DEC <--> AstUnaryExpr
    // op(&|*...) <---> AstCastExpr;
    // SIZEOF <--> UnaryExpr | type_name;
};


class AstAssignExpr : public AstExpr {
public:
    AstAssignExpr(AstCondiExpr* astCondiExpr1);
    AstAssignExpr(AstUnaryExpr* astUnaryExpr1, AstAssignOp* astAssignOp1, AstAssignExpr* astAssignExpr1);
    bool isCondi = true;

    AstCondiExpr* getAstCondiExpr();
    AstUnaryExpr* getAstUnaryExpr();
    AstAssignOp* getAstAssignOp();
    AstAssignExpr* getAstAssignExpr();

private:
    AstCondiExpr* astCondiExpr;
    AstUnaryExpr* astUnaryExpr;
    AstAssignOp* astAssignOp;
    AstAssignExpr* child_AssignExpr;
};

class AstAssignOp: public AstExpr {
public:
    AstAssignOp(std::string op);
    std::string getOperator();
private:
    std::string Operator;
};


class AstCastExpr: public AstExpr {
public:
    AstCastExpr(AstUnaryExpr* astUnaryExpr);
    AstCastExpr(AstTypeName* astTypeName, AstCastExpr* astCastExpr);
    int getType();
    AstCastExpr* getAstCastExpr();
    AstTypeName* getAstTypeName();
    AstUnaryExpr* getAstUnaryExpr();
    // type 0 -- unaryExpr
    // type 1 -- typename + astcastexpr
private:
    int type = 0;
    AstTypeName* astTypeName;
    AstUnaryExpr* astUnaryExpr;
    AstCastExpr* astCastExpr;
};

class AstCalcuExpr: public AstExpr {
public:
    AstCalcuExpr();
    AstCalcuExpr(std::string type);
    void addCalcuExpr(AstCalcuExpr* astCalcuExpr1);
    void addCastExpr(AstCastExpr* astCastExpr);
    void addOperator(std::string op);
    std::vector<AstCalcuExpr*>& getCalcuExprList();
    std::vector<AstCastExpr *>& getCastExprList();
    std::vector<std::string>& getOpList();
    std::string getExprtype();
    bool isCorrect();
private:
    std::vector<AstCalcuExpr*> astCalcuExprList;
    std::vector<AstCastExpr *> astCastExpr;
    std::vector<std::string> opList;
    std::string exprType;
    // cast -- use astCastExpr;
    // else -- use astCalcuExprList
};

class AstCondiExpr: public AstExpr {
public:
    AstCondiExpr(AstCalcuExpr* astCalcuExpr);
    AstCondiExpr(AstCalcuExpr* astCalcuExpr, AstExprList* astExpr, AstCondiExpr* astCondiExpr);
    bool isLow;
    AstCalcuExpr* getAstCalcuExpr();
    AstExprList* getAstExpr();
    AstCondiExpr* getAstCondiExpr();

private:
    AstCalcuExpr* astCalcuExpr = nullptr;
    AstExprList* astExpr = nullptr;
    AstCondiExpr* astCondiExpr = nullptr;
};

class AstExprList: public AstExpr {
public:
    AstExprList();
    void addAssignExpr2(AstAssignExpr* assignExpr);
    std::vector<AstAssignExpr *> getAstAssignExprList();
private:
    std::vector<AstAssignExpr *> AstAssignExprList;
};



#endif //OUR_C_COMPILER_ASTEXPR_H
