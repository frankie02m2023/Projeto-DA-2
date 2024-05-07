//
// Created by franc on 07/05/2024.
//

#include "graph.h"
#include "Node.h"
#include <stack>

class TSPAlgorithms{
private:
    Graph<Node> graph;
    string graphName;
    void loadGraphVertexes();
    void loadGraphEdges();
    void setAllVertexesAsUnvisited();
    void setAllVertexPathsNull();
    void DFSBacktracking(Vertex<Node>* vertex, double& distance, double &minDistance, stack<Node>& path, stack<Node>& minDistPath);
public:
    TSPAlgorithms(const string& graphName);
    string getGraphName() const;
    Graph<Node> getGraph() const;
    void setGraphName(const string& graphName);
    void loadGraph();
    double getMinDistWithBackTracking(stack<Node>& minDistPath);
};
