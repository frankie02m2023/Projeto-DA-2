//
// Created by franc on 07/05/2024.
//

#include "CustomGraph.h"
#include <stack>

class TSPAlgorithms{
private:
    Graph graph;
    string graphName;
    bool graphIsFullyConnected;
    void loadGraphVertexes();
    void loadGraphEdges(unsigned int& numberOfGraphEdges);
    void setAllVertexesAsUnvisited();
    void setAllVertexPathsNull();
    void resetGraph();
    void DFSBacktracking(Vertex* vertex, double& distance, double &minDistance, stack<Node>& path, stack<Node>& minDistPath);
    Vertex* findMinDistVertex(vector<Vertex*> vertexes);
    void primAlgorithm(Vertex* root);
    void MSTPreOrderVisitDFS(Vertex* root, vector<Vertex*>& minDistancePath);
    double getNearestNeighbourDist(Vertex* vertex);
    double findOrCalculateDistanceBetweenVertexes(Vertex* v1, Vertex* v2);
    void primAlgorithmChristofides(Graph& mstGraph, Vertex* vertex);
    vector<Vertex*> getOddDegrees(Graph mstGraph);
    bool edgeBetweenVertexes(Vertex* v1, Vertex* v2);
    void findPerfectMatching(Graph& mstGraph,vector<Vertex*> vertex);
    void setReverseEdgeAsTraversed(Edge* edge);
    void setReverseEdgeAsUnTraversed(Edge* edge);
    bool edgeIsBridge(Edge* edge, Graph &mstGraph);
    void dfsEdgeIsBridge(Vertex* vertex, unsigned int& numberOfReachableEdges);
    void eulerPathDFS(Vertex* vertex, vector<Vertex*>& eulerPath, Graph &mstGraph);
    vector<Vertex*> findEulerPath(Graph& mstGraph);
    vector<Vertex*> buildHamiltonianPath(vector<Vertex*> eulerPath);
public:
    TSPAlgorithms(const string& graphName);
    string getGraphName() const;
    Graph getGraph() const;
    bool isGraphFullyConnected() const;
    void setGraphName(const string& graphName);
    void loadGraph();
    double getMinDistWithBackTracking(stack<Node>& minDistPath);
    double getMinDistWithTriangularInequality(vector<Node>& minDistPath);
    double getMinDistWithNearestNeighbourAnd2opt(vector<Node>& minDistPath);
    double getMinDistWithChristofidesAlgorithm(vector<Node>& minDistPath);
};
