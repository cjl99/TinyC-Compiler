#ifndef TINYC_COMPILER_VISUALIZEAST_H
#define TINYC_COMPILER_VISUALIZEAST_H

#include "../ast/Ast.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class VisualizeAst {
public:
    VisualizeAst(std::string filename);
    void generateGraph();
    void saveGraph();
    int addNodes(std::string label);
    void addEdges(int Aid, int Bid);

    int visualAstRoot(AstProgram *astRoot);
    int visualAstExternalExpr(AstExternalExpr *astExternalExpr);
    int visualAstDeclaration(AstDeclaration* astDeclaration);
    int visualAstFunDef(AstFunDef* astFunDef);

    int visualAstParamList(AstParamList* astParamList);
    int visualAstInitDeclList(AstInitDeclList* astInitDeclList);
    int viusalAstInitDeclarator(AstInitDeclarator* astInitDeclarator);
    int visualAstDeclarator(AstDeclarator* astDeclarator);
    int visualInitializer(AstInitializer* astinit);
    int visualAstInitList(AstInitList* init_list);
    int visualAstDirectDeclarator(AstDirectDeclarator* astDirectDeclarator);
    int visualAstDeclarationList(AstDeclarationList* astDeclarationList);

    int visualAstExpression(AstExpression *astExpression);
    int visualAstCondiExpr(AstCondiExpr *astCondiExpr);
    int visualAssignOp(AstAssignOp* assign_op);
    int visualAstUnaryExpr(AstUnaryExpr* astUnaryExpr);
    int visualAstBinaryExpr(AstBinaryExpr* binary_expr);
    int visualAstPostfixExpr(AstPostfixExpr* postfix_expr);
    int visualAstCastExpr(AstCastExpr* cast_expr);
    int visualAstPrimaryExpr(AstPrimaryExpr* primary_expr);
    int visualAstArgExprList(AstArgExprList* arg_expr_list);

    int visualAstTypeName(AstTypeName* type_name);
    int visualAstIdList(AstIdList* idlist);
    int visualAstSpec(AstSpec* astSpec);

    int visualAstCompoundStmt(AstCompoundStmt* astCompoundStmt);
    int visualAstStmtList(AstStmtList* astStmtList);
    int visualAstStmt(AstStmt* astStmt);

    int visualAstSelectStmt(AstSelectStmt* astSelectStmt);
    int visualAstIterStmt(AstIterStmt *astIterStmt);
    int visualAstJmpStmt(AstJmpStmt* astJmpStmt);


private:
    std::string outFileName;
    long long int id;
    std::vector<std::string> graphNodes;
    std::vector<std::string> graphEdges;
};

#endif
