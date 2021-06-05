//
// Created by Jialiang Chen on 2021/6/5.
//

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
    std::cout << "Save AstGraph to file:" + outFileName + "..."<< std<<endl;

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