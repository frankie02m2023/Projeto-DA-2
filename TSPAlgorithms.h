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
    bool graphIsFullyConnected;
    void loadGraphVertexes();
    void loadGraphEdges(unsigned int& numberOfGraphEdges);
    void setAllVertexesAsUnvisited();
    void setAllVertexPathsNull();
    void DFSBacktracking(Vertex<Node>* vertex, double& distance, double &minDistance, stack<Node>& path, stack<Node>& minDistPath);
    Vertex<Node>* findMinDistVertex(vector<Vertex<Node>*> vertexes);
    void primAlgorithm(Vertex<Node>* root);
    void MSTPreOrderVisitDFS(Vertex<Node>* root, vector<Vertex<Node>*>& minDistancePath);
    void makeGraphFullyConnected();
public:
    TSPAlgorithms(const string& graphName);
    string getGraphName() const;
    Graph<Node> getGraph() const;
    bool isGraphFullyConnected() const;
    void setGraphName(const string& graphName);
    void loadGraph();
    double getMinDistWithBackTracking(stack<Node>& minDistPath);
    double getMinDistWithTriangularInequity(vector<Node>& minDistPath);
};
