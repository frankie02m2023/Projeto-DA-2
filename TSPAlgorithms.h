//
// Created by franc on 07/05/2024.
//

#include "graph.h"
#include "Node.h"

class TSPAlgorithms{
private:
    Graph<Node> graph;
    string graphName;
    void loadGraphVertexes();
    void loadGraphEdges();
public:
    TSPAlgorithms(const string& graphName);
    string getGraphName() const;
    Graph<Node> getGraph() const;
    void setGraphName(const string& graphName);
    void loadGraph();
};
