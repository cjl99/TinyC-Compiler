#define DEBUG_VISUALIZE
#include "VisualizeAst.h"

VisualizeAst::VisualizeAst(std::string filename) {
    this->outFileName = filename;
    this->id = 0;
}

void VisualizeAst::generateGraph() {
    std::cout << "Generate AstGraph..." << std::endl;
    visualAstRoot((AstProgram *)astRoot);
    std::cout << "Generate AstGraph success!" << std::endl;
}

void VisualizeAst::saveGraph() {
    std::cout << "Save AstGraph to file:" + outFileName + "..."<< std::endl;

    std::ofstream f(outFileName);
    f << "digraph G {" << std::endl;
    for (auto e : graphNodes) f << "\t" << e << std::endl;
    f<<std::endl;
    for (auto n : graphEdges) f << "\t" << n << std::endl;
    f << "}";
    f.close();

    std::cout << "Save AstGraph success!" << std::endl;
}

int VisualizeAst::addNodes(std::string label) {
    std::stringstream node("");
    node << "node_" << id++ << "[";
    node << "label = \"" << label << "\"];";
    std::string node_str = node.str();

    #ifdef DEBUG_VISUALIZE
    std::cout << node_str << std::endl;
    #endif

    graphNodes.push_back(node_str);
    return id-1;
}

void VisualizeAst::addEdges(int Aid, int Bid) {
    std::stringstream edge("");
    edge << "node_" << Aid << " -> " << "node_" << Bid << ";";
    std::string edge_str = edge.str();

    graphEdges.push_back(edge_str);
}

int VisualizeAst::visualAstRoot(AstProgram *astRoot) {
    std::string type = astRoot->getNodeType();
    int pid = addNodes(type);
    for(auto externalExpr: astRoot->getExternalExpr()) {
        int cid = visualAstExternalExpr(externalExpr);
        addEdges(pid, cid);
    }

    return pid;
}

int VisualizeAst::visualAstExternalExpr(AstExternalExpr *astExternalExpr) {
    std::string type = astExternalExpr->getNodeType();
    int pid = addNodes(type);

    AstDeclaration *astD = astExternalExpr->getDeclaration();
    AstFunDef * astF = astExternalExpr->getFunDef();
    if(astD != nullptr) {
        int cid = visualAstDeclaration(astD);
        addEdges(pid, cid);
    }
    if (astF!=nullptr){
        int cid = visualAstFunDef(astF);
        addEdges(pid, cid);
    }
    return pid;
}

int VisualizeAst::visualAstDeclaration(AstDeclaration* astDeclaration) {
    std::string type = astDeclaration->getNodeType();
    int pid = addNodes(type);

    AstSpec* astSpec = astDeclaration->getTypeSpec();
    AstInitDeclList* astInitDeclList = astDeclaration->getInitDeclList();
    if(astSpec== nullptr || astInitDeclList== nullptr) {
        std::cout << "visualAstDeclaration error" << std::endl;
    }
    int cid1 = visualAstSpec(astSpec);
    addEdges(pid, cid1);
    int cid2 = visualAstInitDeclList(astInitDeclList);
    addEdges(pid, cid2);

    return pid;
}

int VisualizeAst::visualAstInitDeclList(AstInitDeclList* astInitDeclList) {
    std::string type = astInitDeclList->getNodeType();
    int pid = addNodes(type);

    for(auto astInitDeclarator: astInitDeclList->getInitDeclList()) {
        int cid = viusalAstInitDeclarator(astInitDeclarator);
        addEdges(pid, cid);
    }

    return pid;
}


int VisualizeAst::viusalAstInitDeclarator(AstInitDeclarator* astInitDeclarator) {
    std::string type = astInitDeclarator->getNodeType();
    int pid = addNodes(type);

    AstDeclarator* astDeclarator = astInitDeclarator->getDeclarator();
    addEdges(pid, visualAstDeclarator(astDeclarator));
    if(astInitDeclarator->hasEqual()) {
        AstInitializer* initial= astInitDeclarator->getInitializer();
        addEdges(pid, visualInitializer(initial));
    }

    return pid;
}

int VisualizeAst::visualInitializer(AstInitializer* astInitializer) {
    std::string nodetype = astInitializer->getNodeType();
    int pid = addNodes(nodetype);

    AstExpression *astexpr = astInitializer->getExpression();
    if(astexpr) {
        int cid = visualAstExpression(astexpr);
        addEdges(pid, cid);
    }
    else {
        AstInitList *initlist = astInitializer->getInitList();
        addEdges(pid, visualAstInitList(initlist));
    }
    return pid;
}

int VisualizeAst::visualAstInitList(AstInitList* init_list) {
    std::string nodetype = init_list->getNodeType();
    int pid = addNodes(nodetype);

    for(AstInitializer * initializer: init_list->getInitializerList()) {
        addEdges(pid, visualInitializer(initializer));
    }
    return pid;
}

int VisualizeAst::visualAstDeclarator(AstDeclarator* astDeclarator) {
    std::string type = astDeclarator->getNodeType();
    int pid = addNodes(type);

    if(astDeclarator->hasPointer()) {
        int cid = addNodes(astDeclarator->getPointer()->getStars());
        addEdges(pid, cid);
    }
    int cid = visualAstDirectDeclarator(astDeclarator->getDirectDeclarator());
    addEdges(pid, cid);
    
    return pid;    
}

int VisualizeAst::visualAstDirectDeclarator(AstDirectDeclarator* astDirectDeclarator){
    std::string type = astDirectDeclarator->getNodeType();
    int pid = addNodes(type);
    
    int cid1 = addNodes("INDENTIFIER: " + astDirectDeclarator->getIdentifier());
    addEdges(pid, cid1);

    std::string arraySize = "";
    vector<int> arraySizes = astDirectDeclarator->getArraySize();
    for(int i=0; i<arraySizes.size(); ++i) {
        arraySize += "[";
        if(arraySizes[i]!=-1) arraySize += to_string(arraySizes[i]);
        arraySize += "]";
    }

    int cid2 = addNodes(arraySize);
    addEdges(pid, cid2);

    vector<AstIdList *> id_list = astDirectDeclarator->getIdList();
    for(int i=0; i<id_list.size(); ++i) {
        int cid3 = visualAstIdList(id_list[i]);
        addEdges(pid, cid3);
    }

//    for(auto it: astDirectDeclarator->getDirectDeclaratorPair()) {
//        if(it.first==1) {
//            // bugs may exists here!
//            string str = std::string((const char *)it.second);
//            addEdges(pid, addNodes("CONSTANT: " + str));
//        }
//        else if(it.first==2) {
//            addEdges(pid, addNodes("[]"));
//        }
//        else if(it.first==3) {
//            addEdges(pid, addNodes("()"));
//            int cid = visualAstIdList((AstIdList *)it.second);
//            addEdges(pid, cid);
//        }
//    }
    return pid;
}


int VisualizeAst::visualAstFunDef(AstFunDef* astFunDef) {
    std::string type = astFunDef->getNodeType();
    int pid = addNodes(type);

    std::string ret_type = astFunDef->getReturnType();
    int cid1 = addNodes("Return_Type: " + ret_type);
    addEdges(pid, cid1);

    std::string func_name = astFunDef->getFuncName();
    int cid2 = addNodes("Func_Name: " + func_name);
    addEdges(pid, cid2);

    int pointer_num = astFunDef->getReturnPtrLevel();
    if(pointer_num!=0) {
        std::string pointer_str = "";
        for (int i = 0; i < pointer_num; ++i) pointer_str += "*";
        int cid3 = addNodes("Pointer: " + pointer_str);
        addEdges(pid, cid3);
    }

    AstParamList* astParamList = astFunDef->getAstParamList();
    int cid4 = visualAstParamList(astParamList);
    addEdges(pid, cid4);

    AstCompoundStmt* compound_statement = astFunDef->getCompound_statement();
    if(compound_statement!= nullptr){
        int cid5 = visualAstCompoundStmt(compound_statement);
        addEdges(pid, cid5);
    }

    return pid;
}


int VisualizeAst::visualAstSpec(AstSpec* astSpec) {
    std::string type = astSpec->getNodeType();
    std::string label = astSpec->getLabel();
    return addNodes(type+" " + label);
}

int VisualizeAst::visualAstParamList(AstParamList *param_list) {
    std::string nodetype = param_list->getNodeType();
    int pid = addNodes(nodetype);

    for(auto paramDecl: param_list->getParamList()) {
        int cid1 = visualAstSpec(paramDecl.first);
        int cid2 = visualAstDeclarator(paramDecl.second);
        addEdges(pid, cid1);
        addEdges(pid, cid2);
        addEdges(cid1, cid2);
    }
    return pid;    
}

int VisualizeAst::visualAstIdList(AstIdList *idlist) {
    std::string nodetype = idlist->getNodeType();
    int pid = addNodes(nodetype);

    for(std::string str: idlist->getIdentifiers()) {
        addEdges(pid, addNodes(str));
    }
    return pid;
}

int VisualizeAst::visualAstExpression(AstExpression* astExpression) {
    std::string nodetype = astExpression->getNodeType();
    bool iscondi = astExpression->getCondiExpr() != nullptr;
    std::string condi = (iscondi) ? "conditional" : "assignment_expr";
    int pid = addNodes(nodetype + " " + condi);
    
    if(astExpression->getCondiExpr()) {
        std::cout << astExpression->getCondiExpr() << std::endl;
        int cid1 = visualAstCondiExpr(astExpression->getCondiExpr());
        addEdges(pid, cid1);
    }
    else {
        std::cout << " here " << std::endl;

        int cid1 = visualAstUnaryExpr(astExpression->getUnaryExpr());
        addEdges(pid, cid1);

        int cid2 = visualAssignOp(astExpression->getAssignOp());
        addEdges(pid, cid2);

        int cid3 = visualAstExpression(astExpression->getExpression());
        addEdges(pid, cid3);
    }
    return pid;
}

int VisualizeAst::visualAstCondiExpr(AstCondiExpr *condi_expr) {

    std::string nodetype = "conditional_expression";
    int pid = addNodes(nodetype);

    if(condi_expr->getAstExpression()==nullptr) {
        AstBinaryExpr* back = condi_expr->getAstBinaryExpr_back();
        std::cout << condi_expr << std::endl;
        int cid1 = visualAstBinaryExpr(back);
        addEdges(pid, cid1);
    }
    else {
        int cid1 = visualAstBinaryExpr(condi_expr->getAstBinaryExpr_front());
        addEdges(pid, cid1);

        int cid2 = visualAstExpression(condi_expr->getAstExpression());
        addEdges(pid, cid2);

        int cid3 = visualAstBinaryExpr(condi_expr->getAstBinaryExpr_back());
        addEdges(pid, cid3);
    }

    return pid;
}

int VisualizeAst::visualAssignOp(AstAssignOp *assign_op) {
    std::string nodetype = assign_op->getNodeType();
    std::string optype = assign_op->getOperator();

    return addNodes(nodetype + " " + optype);
}


int VisualizeAst::visualAstUnaryExpr(AstUnaryExpr* astUnaryExpr) {
    std::string nodetype = astUnaryExpr->getNodeType();
    std::string op = astUnaryExpr->getOperator();
    int pid = addNodes(nodetype + " " + op);
    
    if(op=="") { // postfixExpr
        AstPostfixExpr* postExpr = (AstPostfixExpr *)astUnaryExpr->getPtr();
        int cid = visualAstPostfixExpr(postExpr);
        addEdges(pid, cid);
    }
    else {
        if(op=="++" || op=="--" ) {
            AstUnaryExpr* unaryExpr = (AstUnaryExpr *)astUnaryExpr->getPtr();
            int cid = visualAstUnaryExpr(unaryExpr);
            addEdges(pid, cid);
        }
        else {
            AstCastExpr *cast_expr = (AstCastExpr *)astUnaryExpr->getPtr();
            int cid = visualAstCastExpr(cast_expr);
            addEdges(pid, cid);
        }
    }

    return pid;
}

int VisualizeAst::visualAstBinaryExpr(AstBinaryExpr* binary_expr) {
    std::string nodetype = binary_expr->getNodeType();
    std::string op = binary_expr->getOperator();
    int pid = addNodes(nodetype + " op:" + op);

    bool iscast = binary_expr->isCastExpr();
    if(iscast) {
        int cid = visualAstCastExpr(binary_expr->getCastExpr());
        addEdges(pid, cid);
    }
    else {
        int cid1 = visualAstBinaryExpr(binary_expr->getFrontBinaryExpr());
        addEdges(pid, cid1);
        int cid2 = visualAstBinaryExpr(binary_expr->getFrontBinaryExpr());
        addEdges(pid, cid2);
    }

    return pid;
}

int VisualizeAst::visualAstPostfixExpr(AstPostfixExpr* postfix_expr) {
    std::string nodetype = postfix_expr->getNodeType();
    int pid = addNodes(nodetype);

    std::string op = postfix_expr->getOperator();
    if(op=="") {
        AstPrimaryExpr *primary_expr =  (AstPrimaryExpr *)postfix_expr->getPtr();
        int cid = visualAstPrimaryExpr(primary_expr);
        addEdges(pid, cid);
    }
    else {
        AstPostfixExpr *post_child = postfix_expr->getAstPostfixExpr();
        int cid1 = visualAstPostfixExpr(post_child);
        addEdges(pid, cid1);

        // add operator nodes
        int cid2 = addNodes(op);
        addEdges(pid, cid2);
        if(op=="()") {
            AstArgExprList *arg_expr_list = (AstArgExprList *)postfix_expr->getPtr();
            if(arg_expr_list) {
                int cid3 = visualAstArgExprList(arg_expr_list);
                addEdges(pid, cid3);
            }
        }
        else if(op=="[]") {
            AstExpression *astexpr = (AstExpression *)postfix_expr->getPtr();
            if(astexpr) {
                int cid3 = visualAstExpression(astexpr);
                addEdges(pid, cid3);
            }
        }
        else if(op=="." || op=="->") {
            std::string identifier = postfix_expr->getIdentifier();
            int cid3 = addNodes(identifier);
            addEdges(pid, cid3);
        }
    }
    return pid;
}

int VisualizeAst::visualAstCastExpr(AstCastExpr* cast_expr) {
    std::string nodetype = cast_expr->getNodeType();
    int pid = addNodes(nodetype);

    if(cast_expr->isUnaryExpr()) {
        AstUnaryExpr *unary_expr = cast_expr->getUnaryExpr();
        addEdges(pid, visualAstUnaryExpr(unary_expr));
    }
    else{
        int cid1 = visualAstTypeName(cast_expr->getAstTypeName());
        addEdges(pid, cid1);
        int cid2 = visualAstCastExpr(cast_expr->getCastExpr());
        addEdges(pid, cid2);
    }

    return pid;
}

int VisualizeAst::visualAstPrimaryExpr(AstPrimaryExpr *primary_expr) {
    std::string nodetype = primary_expr->getNodeType();
    int pid = addNodes(nodetype);

    int type = primary_expr->getType();
    std::string label = primary_expr->getLabel();
    if(label[0]=='\"') label = label.substr(1,label.length()-2);
    if(type==1) {
        addEdges(pid, addNodes("INDENTIFIER: " + label));
    } else if(type==2) {
        addEdges(pid, addNodes("CONSTANT: " + label));
    } else if(type==3) {
        addEdges(pid, addNodes("STRING_LITERAL: " + label));
    } else if(type==4) {
        int cid = visualAstExpression(primary_expr->getExpression());
        addEdges(pid, cid);
    }

    return pid;
}

int VisualizeAst::visualAstTypeName(AstTypeName* type_name) {
    std::string nodetype = type_name->getNodeType();
    int pid = addNodes(nodetype);

    std::string type= type_name->getType();
    int cid = addNodes("Type: " + type);
    addEdges(pid, cid);

    int num = type_name->getPtrLevel();
    std::string str = "";
    for(int i=0; i<num; ++i) str+="*";
    addEdges(pid, addNodes("pointer: " + str));

    return pid;
}


int VisualizeAst::visualAstArgExprList(AstArgExprList* arg_expr_list) {
    std::string nodetype = arg_expr_list->getNodeType();
    int pid = addNodes(nodetype);

    for(auto expr: arg_expr_list->getAstExpression()) {
        addEdges(pid, visualAstExpression(expr));
    }
    return pid;
}


int VisualizeAst::visualAstCompoundStmt(AstCompoundStmt* astCompoundStmt) {
    std::string type = astCompoundStmt->getNodeType();
    int pid = addNodes(type);

    AstDeclarationList *dl = astCompoundStmt->getAstDeclarationList();
    AstStmtList *sl = astCompoundStmt->getAstStmtList();

    if(dl==nullptr && sl==nullptr) {
        int cid = addNodes("{}");
        addEdges(pid, cid);
    } 
    else if(dl!=nullptr && sl==nullptr) {
        int cid = visualAstDeclarationList(dl);
        addEdges(pid, cid);
    }
    else if(dl==nullptr && sl!=nullptr) {
        int cid = visualAstStmtList(sl);
        addEdges(pid, cid);
    }
    else {
        int cid1 = visualAstDeclarationList(dl);
        addEdges(pid, cid1);
        int cid = visualAstStmtList(sl);
        addEdges(pid, cid);
    }

    return pid;
}

int VisualizeAst::visualAstDeclarationList(AstDeclarationList* astDeclarationList) {
    std::string type = astDeclarationList->getNodeType();
    int pid = addNodes(type);

    for(AstDeclaration *astDeclaration : astDeclarationList->getDeclarationVector()) {
        int cid = visualAstDeclaration(astDeclaration);
        addEdges(pid, cid);
    }

    return pid;    
}

int VisualizeAst::visualAstStmtList(AstStmtList* astStmtList) {
    std::string type = astStmtList->getNodeType();
    int pid = addNodes(type);

    for(AstStmt *astStmt: astStmtList->getStmtList()) {
        int cid = visualAstStmt(astStmt);
        addEdges(pid, cid);
    }
    return pid;
}

int VisualizeAst::visualAstStmt(AstStmt* astStmt) {
    std::string type = astStmt->getNodeType(); 
    int pid = addNodes(type);

    AstBase *astBase = astStmt->getStmt();
    int tp = astStmt->getType();

    int cid = 0;
    if(tp==1) {
        cid = visualAstCompoundStmt((AstCompoundStmt *)astBase);
    } else if(tp==2) { 
        cid = visualAstExprStmt((AstExprStmt *)astBase);
    } else if(tp==3) {
        cid = visualAstSelectStmt((AstSelectStmt *)astBase);
    } else if(tp==4) {
        cid = visualAstIterStmt((AstIterStmt *)astBase);
    } else if(tp==5) {
        cid = visualAstJmpStmt((AstJmpStmt *)astBase);
    }
    if(cid!=0) addEdges(pid, cid);

    return pid;    
}

int VisualizeAst::visualAstSelectStmt(AstSelectStmt* astSelectStmt) {
    std::string type = astSelectStmt->getNodeType();
    int pid = addNodes(type);

    AstStmt *astStmt_then = astSelectStmt->getThenClause();
    AstStmt *astStmt_else = astSelectStmt->getElseClause();
    AstExpression *astExpr = astSelectStmt->getExpr();

    int cid1 = visualAstExpression(astExpr);
    addEdges(pid, cid1);
    int cid2 = visualAstStmt(astStmt_then);
    addEdges(pid, cid2);
    if(astStmt_else) { 
        int cid3 = visualAstStmt(astStmt_else);
        addEdges(pid, cid3);
    }

    return pid;
}

int VisualizeAst::visualAstIterStmt(AstIterStmt *astIterStmt) {
    std::string nodetype = astIterStmt->getNodeType();
    int tp = astIterStmt->getType();
    std::string strtp = tp==1 ? "while" : "for";
    int pid = addNodes(nodetype + "\t" + strtp);

    AstStmt *block = astIterStmt->getBlock();
    AstExpression *InitialExpr = astIterStmt->getInitialExpr();
    AstExpression *JudgeExpr = astIterStmt->getJudgeExpr();
    AstExpression *UpdateExpr = astIterStmt->getUpdateExpr();

    if(tp==1) { // "while"
        int cid1 = visualAstExpression(JudgeExpr);
        addEdges(pid, cid1);
        int cid2 = visualAstStmt(block);
        addEdges(pid, cid2);
    }
    else if(tp==2){ // for
        if(InitialExpr) {
            int cid1 = visualAstExpression(InitialExpr);
            addEdges(pid, cid1);
        }
        if(JudgeExpr) {
            int cid2 = visualAstExpression(JudgeExpr);
            addEdges(pid, cid2);
        }
        if(UpdateExpr) {
            int cid3 = visualAstExpression(UpdateExpr);
            addEdges(pid, cid3);
        }
        if(block) {
            int cid4 = visualAstStmt(block);
            addEdges(pid, cid4);
        }
    }

    return pid;    
}

int VisualizeAst::visualAstJmpStmt(AstJmpStmt* astJmpStmt) {
    std::string type = astJmpStmt->getNodeType();
    std::string tp = astJmpStmt->getType();

    int pid = addNodes(type + "\t" + tp);


    AstExpression* ast_expr = astJmpStmt->getExpr();
    if(ast_expr) {
        int cid = visualAstExpression(ast_expr);
        addEdges(pid, cid);
    }
    
    return pid;
}

int VisualizeAst::visualAstExprStmt(AstExprStmt* exprStmt) {
    std::string nodetype = exprStmt->getNodeType();
    int pid = addNodes(nodetype);

    AstExpression *expr = exprStmt->getExpr();
    int cid = visualAstExpression(expr);
    addEdges(pid, cid);

    return pid;
}

// VisualizeAst