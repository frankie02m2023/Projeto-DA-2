//
// Created by franc on 18/05/2024.
//

#ifndef DA2324_P03_STUDENT_COSTUMGRAPH_H
#define DA2324_P03_STUDENT_COSTUMGRAPH_H

#include <vector>
#include <unordered_set>
#include <queue>
#include "Node.h"

class Edge; // Forward declaration of Edge

/********************** Vertex  ****************************/

class Vertex {
public:
    Vertex(Node info);

    Node getInfo() const;
    std::unordered_set<Edge*, std::hash<Edge*>, std::equal_to<Edge*>> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge* getPath() const;
    std::unordered_set<Edge*, std::hash<Edge*>, std::equal_to<Edge*>> getIncoming() const;

    void setInfo(Node info);
    void setVisited(bool visited);
    void setProcessing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge* path);
    Edge* addEdge(Vertex* dest, double w);
    bool removeEdge(Node in);
    void removeOutgoingEdges();
    bool operator==(const Vertex& vertex) const;
    size_t hash() const;

protected:
    Node info; // info node
    std::unordered_set<Edge*, std::hash<Edge*>, std::equal_to<Edge*>> adj; // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    double dist = 0;
    Edge* path = nullptr;

    std::unordered_set<Edge*, std::hash<Edge*>, std::equal_to<Edge*>> incoming; // incoming edges
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

namespace std {
    template <>
    struct hash<Edge> {
        size_t operator()(const Edge* edge) const {
            return edge->hash();
        }
    };

    template <>
    struct equal_to<Edge> {
        bool operator()(const Edge* e1, const Edge* e2) const {
            return *e1 == *e2;
        }
    };
}

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

/********************** Vertex  ****************************/

Vertex::Vertex(Node in) : info(in) {}

Edge* Vertex::addEdge(Vertex* d, double w) {
    auto newEdge = new Edge(this, d, w);
    adj.insert(newEdge);
    d->incoming.insert(newEdge);
    return newEdge;
}

bool Vertex::removeEdge(Node in) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge* edge = *it;
        Vertex* dest = edge->getDest();
        if (dest->getInfo() == in) {
            it = adj.erase(it);
            deleteEdge(edge);
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

void Vertex::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}

Node Vertex::getInfo() const {
    return this->info;
}

std::unordered_set<Edge*, std::hash<Edge*>, std::equal_to<Edge*>> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

bool Vertex::isProcessing() const {
    return this->processing;
}

unsigned int Vertex::getIndegree() const {
    return this->indegree;
}

double Vertex::getDist() const {
    return this->dist;
}

Edge* Vertex::getPath() const {
    return this->path;
}

std::unordered_set<Edge*, std::hash<Edge*>, std::equal_to<Edge*>> Vertex::getIncoming() const {
    return this->incoming;
}

void Vertex::setInfo(Node in) {
    this->info = in;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setProcessing(bool processing) {
    this->processing = processing;
}

void Vertex::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

void Vertex::setDist(double dist) {
    this->dist = dist;
}

void Vertex::setPath(Edge* path) {
    this->path = path;
}

void Vertex::deleteEdge(Edge *edge) {
    Vertex *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getInfo() == info) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete edge;
}

bool Vertex::operator==(const Vertex &vertex) const {
    return this->getInfo() == vertex.getInfo();
}

size_t Vertex::hash() const {
    return std::hash<Node>()(info) >> 1;
}

/********************** Edge  ****************************/


Edge::Edge(Vertex *orig, Vertex *dest, double w): orig(orig), dest(dest), weight(w) {}

Vertex * Edge::getDest() const {
    return this->dest;
}

double Edge::getWeight() const {
    return this->weight;
}

Vertex * Edge::getOrig() const {
    return this->orig;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}

bool Edge::isSelected() const {
    return this->selected;
}

bool Edge::isTraversed() const {
    return traversed;
}

double Edge::getFlow() const {
    return flow;
}

void Edge::setSelected(bool selected) {
    this->selected = selected;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

void Edge::setFlow(double flow) {
    this->flow = flow;
}

void Edge::setWeight(double weight) {
    this->weight = weight;
}

void Edge::setTraversed(bool traversed) {
    this->traversed = traversed;
}

bool Edge::operator==(const Edge &edge) const {
    return this->orig == edge.orig && this->dest == edge.dest && this->weight == edge.weight;
}

size_t Edge::hash() const {
    size_t origHash = std::hash<Vertex*>()(orig);
    size_t destHash = std::hash<Vertex*>()(dest);
    size_t weightHash = std::hash<double>()(weight);
    return (origHash ^ destHash ^ weightHash) << 1;
}


/********************** Graph  ****************************/


int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::unordered_set<Vertex *, hashVertex, vertexEquality> Graph::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex * Graph::findVertex(const Node &in) const {
    Vertex vertex(in);
    Vertex* vertex1 = &vertex;
    auto it = vertexSet.find(vertex1);
    if(it == nullptr){
        return nullptr;
    }
    return *it;
}

/*
 * Finds the index of the vertex with a given content.
 */

int Graph::findVertexIdx(const Node &in) const {
    Vertex vertex(in);
    Vertex* vertex1 = &vertex;
    auto it = vertexSet.find(vertex1);
    Vertex *vertex2 = *it;
    if(it == nullptr){
        return -1;
    }
    return vertex2->getInfo().getID();
}
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */

bool Graph::addVertex(const Node &in) {
    if (findVertex(in) != nullptr)
        return false;
    vertexSet.insert(new Vertex(in));
    return true;
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */

bool Graph::removeVertex(const Node &in) {
    if (findVertex(in) != nullptr)
        return false;
    Vertex* vertex = findVertex(in);
    vertexSet.erase(vertex);
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */

bool Graph::addEdge(const Node &sourc, const Node &dest, double w) {
    Vertex* v1 = findVertex(sourc);
    Vertex* v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    return true;
}

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */

bool Graph::removeEdge(const Node &sourc, const Node &dest) {
    Vertex * srcVertex = findVertex(sourc);
    if (srcVertex == nullptr) {
        return false;
    }
    return srcVertex->removeEdge(dest);
}

bool Graph::addBidirectionalEdge(const Node &sourc, const Node &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

/****************** DFS ********************/

/*
 * Performs a depth-first search (dfs) traversal in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 */

std::vector<Node> Graph::dfs() const {
    std::vector<Node> res;
    for (auto v : vertexSet)
        v->setVisited(false);
    for (auto v : vertexSet)
        if (!v->isVisited())
            dfsVisit(v, res);
    return res;
}

/*
 * Performs a depth-first search (dfs) in a graph (this) from the source node.
 * Returns a vector with the contents of the vertices by dfs order.
 */

std::vector<Node> Graph::dfs(const Node & source) const {
    std::vector<Node> res;
// Get the source vertex
    auto s = findVertex(source);
    if (s == nullptr) {
        return res;
    }
// Set that no vertex has been visited yet
    for (auto v : vertexSet) {
        v->setVisited(false);
    }
// Perform the actual DFS using recursion
    dfsVisit(s, res);

    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */

void Graph::dfsVisit(Vertex *v, std::vector<Node> & res) const {
    v->setVisited(true);
    res.push_back(v->getInfo());
    for (auto & e : v->getAdj()) {
        auto w = e->getDest();
        if (!w->isVisited()) {
            dfsVisit(w, res);
        }
    }
}

/****************** BFS ********************/
/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 */

std::vector<Node> Graph::bfs(const Node & source) const {
    std::vector<Node> res;
// Get the source vertex
    auto s = findVertex(source);
    if (s == nullptr) {
        return res;
    }

// Set that no vertex has been visited yet
    for (auto v : vertexSet) {
        v->setVisited(false);
    }

// Perform the actual BFS using a queue
    std::queue<Vertex *> q;
    q.push(s);
    s->setVisited(true);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->getInfo());
        for (auto & e : v->getAdj()) {
            auto w = e->getDest();
            if ( ! w->isVisited()) {
                q.push(w);
                w->setVisited(true);
            }
        }
    }
    return res;
}

/****************** isDAG  ********************/
/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

/****************** toposort ********************/
//=============================================================================
// Exercise 1: Topological Sorting
//=============================================================================
// TODO
/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

std::vector<Node> Graph::topsort() const {
    std::vector<Node> res;

    for (auto v : vertexSet) {
        v->setIndegree(0);
    }
    for (auto v : vertexSet) {
        for (auto e : v->getAdj()) {
            unsigned int indegree = e->getDest()->getIndegree();
            e->getDest()->setIndegree(indegree + 1);
        }
    }

    std::queue<Vertex *> q;
    for (auto v : vertexSet) {
        if (v->getIndegree() == 0) {
            q.push(v);
        }
    }

    while( !q.empty() ) {
        Vertex * v = q.front();
        q.pop();
        res.push_back(v->getInfo());
        for(auto e : v->getAdj()) {
            auto w = e->getDest();
            w->setIndegree(w->getIndegree() - 1);
            if(w->getIndegree() == 0) {
                q.push(w);
            }
        }
    }

    if ( res.size() != vertexSet.size() ) {
//std::cout << "Impossible topological ordering!" << std::endl;
        res.clear();
        return res;
    }

    return res;
}

inline void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

inline void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}

#endif // DA2324_P03_STUDENT_COSTUMGRAPH_H

