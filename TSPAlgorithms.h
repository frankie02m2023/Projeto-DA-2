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
    void resetGraph();
    void DFSBacktracking(Vertex<Node>* vertex, double& distance, double &minDistance, stack<Node>& path, stack<Node>& minDistPath);
    Vertex<Node>* findMinDistVertex(vector<Vertex<Node>*> vertexes);
    void primAlgorithm(Vertex<Node>* root);
    void MSTPreOrderVisitDFS(Vertex<Node>* root, vector<Vertex<Node>*>& minDistancePath);
    double getNearestNeighbourDist(Vertex<Node>* vertex);
    double findOrCalculateDistanceBetweenVertexes(Vertex<Node>* v1, Vertex<Node>* v2);
    void primAlgorithmChristofides(Graph<Node>& mstGraph, Vertex<Node>* vertex);
    vector<Vertex<Node>*> getOddDegrees(Graph<Node> mstGraph);
    bool edgeBetweenVertexes(Vertex<Node>* v1, Vertex<Node>* v2);
    void findPerfectMatching(Graph<Node>& mstGraph,vector<Vertex<Node>*> vertex);
    void setReverseEdgeAsTraversed(Edge<Node>* edge);
    void setReverseEdgeAsUnTraversed(Edge<Node>* edge);
    bool edgeIsBridge(Edge<Node>* edge, Graph<Node> &mstGraph);
    void dfsEdgeIsBridge(Vertex<Node>* vertex, unsigned int& numberOfReachableEdges);
    void eulerPathDFS(Vertex<Node>* vertex, vector<Vertex<Node>*>& eulerPath, Graph<Node> &mstGraph);
    vector<Vertex<Node>*> findEulerPath(Graph<Node>& mstGraph);
    vector<Vertex<Node>*> buildHamiltonianPath(vector<Vertex<Node>*> eulerPath);
public:
    TSPAlgorithms(const string& graphName);
    string getGraphName() const;
    Graph<Node> getGraph() const;
    bool isGraphFullyConnected() const;
    void setGraphName(const string& graphName);
    void loadGraph();
    double getMinDistWithBackTracking(stack<Node>& minDistPath);
    double getMinDistWithTriangularInequality(vector<Node>& minDistPath);
    double getMinDistWithNearestNeighbourAnd2opt(vector<Node>& minDistPath);
    double getMinDistWithChristofidesAlgorithm(vector<Node>& minDistPath);
};
