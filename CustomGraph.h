//
// Created by franc on 18/05/2024.
//

#ifndef DA2324_P03_STUDENT_CUSTOMGRAPH_H
#define DA2324_P03_STUDENT_CUSTOMGRAPH_H

#include <vector>
#include <unordered_set>
#include <queue>
#include "Node.h"

class Vertex; // Forward declaration of Vertex

/********************** Vertex  ****************************/
class Edge {
public:
    Edge(Vertex* orig, Vertex* dest, double w);

    Vertex* getDest() const;
    double getWeight() const;
    bool isSelected() const;
    Vertex* getOrig() const;
    Edge* getReverse() const;
    double getFlow() const;
    bool isTraversed() const;

    void setSelected(bool selected);
    void setReverse(Edge* reverse);
    void setFlow(double flow);
    void setWeight(double weight);
    void setTraversed(bool traversed);
    bool operator==(const Edge& edge) const;
    size_t hash() const;

protected:
    Vertex* dest; // destination vertex
    double weight; // edge weight, can also be used for capacity

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex* orig;
    Edge* reverse = nullptr;

    double flow; // for flow-related problems

    // used for Christofides algorithm
    bool traversed = false;
};


struct edgeHash {
    size_t operator()(const Edge* edge) const {
        return edge->hash();
    }
};

struct edgeEquality {
    bool operator()(const Edge* e1, const Edge* e2) const {
        return *e1 == *e2;
    }
};

class Vertex {
public:
    Vertex(Node info);

    Node getInfo() const;
    std::unordered_set<Edge*, edgeHash, edgeEquality> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge* getPath() const;
    std::unordered_set<Edge*, edgeHash, edgeEquality> getIncoming() const;

    void setInfo(Node info);
    void setVisited(bool visited);
    void setProcessing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge* path);
    Edge* addEdge(Vertex* dest, double w);
    Edge* findEdge(Vertex* dest);
    bool removeEdge(Node in);
    void removeOutgoingEdges();
    bool operator==(const Vertex& vertex) const;
    size_t hash() const;

protected:
    Node info; // info node
    std::unordered_set<Edge*, edgeHash, edgeEquality> adj; // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    double dist = 0;
    Edge* path = nullptr;

    std::unordered_set<Edge*, edgeHash, edgeEquality> incoming; // incoming edges
    void deleteEdge(Edge* edge);
};

struct hashVertex {
    size_t operator()(const Vertex* vertex) const {
        return vertex->hash();
    }
};

struct vertexEquality {
    bool operator()(const Vertex* v1, const Vertex* v2) const {
        return *v1 == *v2;
    }
};

/********************** Edge  ****************************/



/********************** Graph  ****************************/

class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a vertex with a given the content.
    */
    Vertex* findVertex(const Node& in) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const Node& in);
    bool removeVertex(const Node& in);
    /* Auxiliary function to find a vertex with a given the content.
    */
    Edge* findEdge(const Node& sourc, const Node& dest) const;
    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const Node& sourc, const Node& dest, double w);
    bool removeEdge(const Node& source, const Node& dest);
    bool addBidirectionalEdge(const Node& sourc, const Node& dest, double w);

    int getNumVertex() const;
    std::unordered_set<Vertex*, hashVertex, vertexEquality> getVertexSet() const;

    std::vector<Node> dfs() const;
    std::vector<Node> dfs(const Node& source) const;
    void dfsVisit(Vertex* v, std::vector<Node>& res) const;
    std::vector<Node> bfs(const Node& source) const;

    bool isDAG() const;
    bool dfsIsDAG(Vertex* v) const;
    std::vector<Node> topsort() const;

protected:
    std::unordered_set<Vertex*, hashVertex, vertexEquality> vertexSet; // vertex set

    double** distMatrix = nullptr; // dist matrix for Floyd-Warshall
    int** pathMatrix = nullptr; // path matrix for Floyd-Warshall

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const Node& in) const;
};



#endif // DA2324_P03_STUDENT_CUSTOMGRAPH_H

