#ifndef TINYC_COMPILER_VISUALIZEAST_H
#define TINYC_COMPILER_VISUALIZEAST_H

#include "../ast/Ast.h.h"

class VisualizeAst {
public:
    int visualAstRoot(AstProgram *astRoot);
    int visualAstExternalExpr(AstExternalExpr *astExternalExpr);
    int visualAstDeclaration(AstDeclaration* astDeclaration);
    int visualFunDef(AstFunDef* astFunDef);
    int visualAstDeclarationList(AstDeclarationList* astDeclarationList);
    int visualAstCompoundStmt(AstCompoundStmt* astCompoundStmt);
    int visualAstStmtList(AstStmtList* astStmtList);
    int visualAstStmt(AstStmt *astStmt);
    int visualAstExprList(AstExprList* astExprList);
    int visualAstAssignExpr(AstAssignExpr* astAssignExpr);
    int visualAstAssignOp(AstAssignOp *assign_op);
    int visualAstUnaryExpr(AstUnaryExpr* astUnaryExpr);
    int visualAstCastExpr(AstCastExpr *cast_expr);
    int visualAstTypeName(AstTypeName* astTypeName);
    int visualAstAbsDeclarator(AstAbsDeclarator * abs_decltor);
    int visualAstDirectAbsDeclarator(AstDirectAbsDeclarator* dir_abs_decltor);
    int visualAstParamTypeList(AstParamTypeList* paramtype_list);
    int visualAstParamList(AstParamList *param_list);
    int visualAstParamDecl(AstParamDecl* paramDecl);
    int visualAstPostfixExpr(AstPostfixExpr* postfix_expr);
    int visualAstArgExprList(AstArgExprList* astArgExprList);
    int visualAstPrimaryExpr(AstPrimaryExpr *primary_expr);
    int visualAstSelectStmt(AstSelectStmt* astSelectStmt);
    int visualAstIterStmt(AstIterStmt* astIterStmt);
    int visualAstJmpStmt(AstJmpStmt *astJumpStmt);
    int visualAstLabelStmt(AstLabelStmt * astLabelStmt);
    int visualAstDeclarator(AstDeclarator *astDeclarator);
    int visualAstPointer(AstPointer* astPointer);
    int visualAstDirectDeclarator(AstDirectDeclarator* astDirectDeclarator);
    int visualAstIdList(AstIdList *idlist) ;
    int visualAstCondiExpr(AstCondiExpr* astCondiExpr);
    int visualAstCalcuExpr(AstCalcuExpr* calcu_expr);
    int visualAstSpecList(AstSpecList* astSpecList);
    int visualAstSpec(AstSpec *astSpec);
    int visualAstInitDeclList(AstInitDeclList* astInitDeclList);
    int visualAstInitDeclarator(AstInitDeclarator *astInitDeclarator);
    int visualAstInit(AstInit* astInitializer);
    int visualAstInitList(AstInitList* init_list);

    VisualizeAst(std::string filename);
    void generateGraph();
    void saveGraph();
    int addNodes(std::string label);
    void addEdges(int Aid, int Bid);
    
    
private:
    std::string outFileName;
    long long int id;
    std::vector<std::string> graphNodes;
    std::vector<std::string> graphEdges;
};

#endif
