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

    /**
     * @brief Loads the vertices of the graph from different data sources based on the graph name.
     *
     * Complexity: O(V) where V is the number of vertices.
     */
    void loadGraphVertexes();

    /**
     * @brief Loads the edges of the graph and calculates the number of edges.
     *
     * @param numberOfGraphEdges The reference to store the number of graph edges.
     *
     * Complexity: O(E) where E is the number of edges.
     */
    void loadGraphEdges(unsigned int& numberOfGraphEdges);

    /**
     * @brief Sets all vertices in the graph as unvisited.
     *
     * Complexity: O(V) where V is the number of vertices.
     */
    void setAllVertexesAsUnvisited();

    /**
     * @brief Sets the path of all vertices to null.
     *
     * Complexity: O(V) where V is the number of vertices.
     */
    void setAllVertexPathsNull();

    void resetGraph();

    /**
     * @brief Recursive function to perform DFS for the backtracking algorithm.
     *
     * @param vertex The current vertex.
     * @param distance The current distance.
     * @param minDistance The minimum distance found.
     * @param path The current path.
     * @param minDistancePath The path with the minimum distance.
     *
     * Complexity: O((V+E)!) where V is the number of vertices and E is the number of edges.
     */
    void DFSBacktracking(Vertex<Node>* vertex, double& distance, double &minDistance, stack<Node>& path, stack<Node>& minDistPath);

    /**
     * @brief Finds the vertex with the minimum distance that has not been visited.
     *
     * @param vertexes The list of vertices.
     * @return The vertex with the minimum distance.
     *
     * Complexity: O(V) where V is the number of vertices.
     */
    Vertex<Node>* findMinDistVertex(vector<Vertex<Node>*> vertexes);

    /**
     * @brief Performs Prim's algorithm to create an MST starting from the root vertex.
     *
     * @param root The root vertex.
     *
     * Complexity: O(V^2) where V is the number of vertices.
     */
    void primAlgorithm(Vertex<Node>* root);

    /**
     * @brief Performs a pre-order DFS visit of the MST.
     *
     * @param root The root vertex.
     * @param minDistancePath The path with the minimum distance.
     *
     * Complexity: O(V + E) where V is the number of vertices and E is the number of edges.
     */
    void MSTPreOrderVisitDFS(Vertex<Node>* root, vector<Vertex<Node>*>& minDistancePath);

    /**
     * @brief Gets the nearest neighbour distance for the current vertex.
     *
     * @param vertex The current vertex.
     * @return The nearest neighbour distance.
     *
     * Complexity: O(V) where V is the number of vertices.
     */
    double getNearestNeighbourDist(Vertex<Node>* vertex);

    /**
     * @brief Finds or calculates the distance between two vertices.
     *
     * @param v1 The first vertex.
     * @param v2 The second vertex.
     * @return The distance between the two vertices.
     *
     * Complexity: O(E) where E is the number of edges.
     */
    double findOrCalculateDistanceBetweenVertexes(Vertex<Node>* v1, Vertex<Node>* v2);

    /**
     * @brief Performs Prim's algorithm for Christofides to create an MST.
     *
     * @param mstGraph The MST graph to be created.
     * @param root The root vertex.
     *
     * Complexity: O(V^2) where V is the number of vertices.
     */
    void primAlgorithmChristofides(Graph<Node>& mstGraph, Vertex<Node>* vertex);

    /**
     * @brief Gets the vertices with odd degrees in the MST.
     *
     * @param mstGraph The MST graph.
     * @return The vertices with odd degrees.
     *
     * Complexity: O(V) where V is the number of vertices.
     */
    vector<Vertex<Node>*> getOddDegrees(Graph<Node> mstGraph);

    /**
     * @brief Checks if there is an edge between two vertices.
     *
     * @param v1 The first vertex.
     * @param v2 The second vertex.
     * @return True if there is an edge, false otherwise.
     *
     * Complexity: O(E) where E is the number of edges.
     */
    bool edgeBetweenVertexes(Vertex<Node>* v1, Vertex<Node>* v2);

    /**
     * @brief Finds a perfect matching for the vertices with odd degrees.
     *
     * @param mstGraph The MST graph.
     * @param oddDegreeVertexes The vertices with odd degrees.
     *
     * Complexity: O(V^2) where V is the number of vertices.
     */
    void findPerfectMatching(Graph<Node>& mstGraph,vector<Vertex<Node>*> vertex);

    /**
     * @brief Sets the reverse edge of the given edge as traversed.
     *
     * @param edge The edge.
     *
     * Complexity: O(E) where E is the number of edges.
     */
    void setReverseEdgeAsTraversed(Edge<Node>* edge);

    /**
     * @brief Sets the reverse edge of the given edge as untraversed.
     *
     * @param edge The edge.
     *
     * Complexity: O(E) where E is the number of edges.
     */
    void setReverseEdgeAsUnTraversed(Edge<Node>* edge);

    /**
      * @brief Checks if an edge is a bridge.
      *
      * @param edge The edge.
      * @param mstGraph The MST graph.
      * @return True if the edge is a bridge, false otherwise.
      *
      * Complexity: O(V + E) where V is the number of vertices and E is the number of edges.
      */
    bool edgeIsBridge(Edge<Node>* edge, Graph<Node> &mstGraph);

    /**
     * @brief Performs a DFS to check if an edge is a bridge.
     *
     * @param vertex The current vertex.
     * @param numberOfReachableEdges The number of reachable edges.
     *
     * Complexity: O(V + E) where V is the number of vertices and E is the number of edges.
     */
    void dfsEdgeIsBridge(Vertex<Node>* vertex, unsigned int& numberOfReachableEdges);

    /**
     * @brief Performs a Depth-First Search (DFS) to find the Eulerian path in the MST.
     *
     * @param vertex The current vertex being visited.
     * @param eulerPath The vector to store the Eulerian path.
     * @param mstGraph The MST graph.
     *
     * Complexity: O(V + E) where V is the number of vertices and E is the number of edges.
     */
    void eulerPathDFS(Vertex<Node>* vertex, vector<Vertex<Node>*>& eulerPath, Graph<Node> &mstGraph);

    /**
     * @brief Finds the Eulerian path in the MST.
     *
     * @param mstGraph The MST graph.
     * @return The vector of vertices representing the Eulerian path.
     *
     * Complexity: O(V + E) where V is the number of vertices and E is the number of edges.
     */
    vector<Vertex<Node>*> findEulerPath(Graph<Node>& mstGraph);

    /**
     * @brief Builds the Hamiltonian path from the given Eulerian path.
     *
     * @param eulerPath The Eulerian path.
     * @return The vector of vertices representing the Hamiltonian path.
     *
     * Complexity: O(V) where V is the number of vertices.
     */
    vector<Vertex<Node>*> buildHamiltonianPath(vector<Vertex<Node>*> eulerPath);

public:

    /**
     * @brief Constructor for TSPAlgorithms, sets the graph name.
     *
     * @param graphName The name of the graph.
     *
     * Complexity: O(1)
     */
    TSPAlgorithms(const string& graphName);

    /**
     * @brief Gets the name of the graph.
     *
     * @return The name of the graph.
     *
     * Complexity: O(1)
     */
    string getGraphName() const;

    /**
     * @brief Retrieves the graph.
     *
     * @return The graph of nodes.
     *
     * Complexity: O(1)
     */
    Graph<Node> getGraph() const;

    /**
     * @brief Checks if the graph is fully connected.
     *
     * @return True if the graph is fully connected, false otherwise.
     *
     * Complexity: O(1)
     */
    bool isGraphFullyConnected() const;

    /**
     * @brief Sets the name of the graph.
     *
     * @param graphName The new name of the graph.
     *
     * Complexity: O(1)
     */
    void setGraphName(const string& graphName);


    /**
     * @brief Loads the graph by first loading the vertices and then the edges.
     *
     * Complexity: O(V + E) where V is the number of vertices and E is the number of edges.
     */
    void loadGraph();

    /**
     * @brief Finds the minimum distance using the backtracking algorithm.
     *
     * @param minDistancePath The path with the minimum distance.
     * @return The minimum distance.
     *
     * Complexity: O((V+E)!) where V is the number of vertices and E is the number of edges.
     */
    double getMinDistWithBackTracking(stack<Node>& minDistPath);

    /**
     * @brief Finds the minimum distance using the triangular inequality and MST.
     *
     * @param minDistPath The path with the minimum distance.
     * @return The minimum distance.
     *
     * Complexity: O(V^2) where V is the number of vertices.
     */
    double getMinDistWithTriangularInequality(vector<Node>& minDistPath);

    /**
     * @brief Finds the minimum distance using the nearest neighbour and 2-opt algorithms.
     *
     * @param minDistPath The path with the minimum distance.
     * @return The minimum distance.
     *
     * Complexity: O(V^2) where V is the number of vertices.
     */
    double getMinDistWithNearestNeighbourAnd2opt(vector<Node>& minDistPath);

    /**
     * @brief Finds the minimum distance using the Christofides algorithm.
     *
     * @param minDistPath The path with the minimum distance.
     * @return The minimum distance.
     *
     * Complexity: O(V^3) where V is the number of vertices.
     */
    double getMinDistWithChristofidesAlgorithm(vector<Node>& minDistPath);
};
