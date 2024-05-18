//
// Created by franc on 07/05/2024.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include "TSPAlgorithms.h"
#include "MutablePriorityQueue.h"

Graph TSPAlgorithms::getGraph() const {
    return graph;
}

TSPAlgorithms::TSPAlgorithms(const string &graphName) {
    this->graphName = graphName;
}

string TSPAlgorithms::getGraphName() const {
    return graphName;
}

void TSPAlgorithms::setGraphName(const string &graphName) {
    this->graphName = graphName;
}

bool TSPAlgorithms::isGraphFullyConnected() const {
    return graphIsFullyConnected;
}

void TSPAlgorithms::loadGraphVertexes() {
    string filename;
    if(graphName == "shipping" || graphName == "stadiums" || graphName == "tourism"){
        int numberOfVertexes;
        if(graphName == "shipping"){
            numberOfVertexes = 14;
        }
        else if(graphName == "stadiums"){
            numberOfVertexes = 11;
        }
        else{
            numberOfVertexes = 5;
        }
        for(int i = 0; i < numberOfVertexes; i++){
            Node newVertex = Node(i);
            graph.addVertex(newVertex);
        }
    }
    else if(graphName.find("edges") != string::npos){
        string line, idStr, latitudeStr, longitudeStr;
        int id;
        double latitude,longitude;
        std::fstream newFile;

        filename = "nodes.csv";

        newFile.open(filename);

        int pos1 = graphName.find('_');
        int maxVertexNumber = stoi(graphName.substr(pos1 + 1, graphName.size() - pos1 - 1));
        int vertexNumber = 0;

        if (newFile.fail()) {
            std::cout << "Invalid File - Please insert a valid file in the data folder.";
            exit(0);
        }

        getline(newFile,line);

        while(vertexNumber < maxVertexNumber){

            getline(newFile, line);

            istringstream ss(line);

            try{
                getline(ss,idStr,',');
                id = stoi(idStr);
                getline(ss,latitudeStr,',');
                latitude = stod(latitudeStr);
                getline(ss,longitudeStr,'\r');
                longitude = stod(longitudeStr);
            }
            catch(const std::exception& e){
                cout << "The file " << filename << " was badly formatted. Please try again";
                exit(0);
            }

            Location location = Location(latitude,longitude);

            Node newVertex = Node(id,location);

            graph.addVertex(newVertex);

            vertexNumber++;

        }
    }
    else if(graphName.find("Graph") != string::npos){
        string line, idStr, latitudeStr, longitudeStr;
        int id;
        double latitude,longitude;
        std::fstream newFile;

        filename = graphName + "/nodes.csv";

        newFile.open(filename);

        if (newFile.fail()) {
            std::cout << "Invalid File - Please insert a valid file in the data folder.";
            exit(0);
        }

        getline(newFile,line);

        while(true){

            if(newFile.eof()){
                break;
            }

            getline(newFile, line);

            if(line == ""){
                continue;
            }

            istringstream ss(line);

            try{
                getline(ss,idStr,',');
                id = stoi(idStr);
                getline(ss,latitudeStr,',');
                latitude = stod(latitudeStr);
                getline(ss,longitudeStr,'\r');
                longitude = stod(longitudeStr);
            }

            catch (const std::exception& e) {
                std::cout << "The file " << filename << " is badly formatted. Please fix the file and reopen the program." << std::endl;
                exit(0);
            }

            Location location = Location(latitude,longitude);
            Node node = Node(id,location);
            graph.addVertex(node);

        }
    }
}

void TSPAlgorithms::loadGraphEdges(unsigned int& numberOfGraphEdges) {
    if(graphName != "Graph1" && graphName != "Graph2" && graphName != "Graph3"){
        string filename = graphName + ".csv";

        string line, idSourceStr, idDestinationStr, distanceStr, sourceName, destinationName;
        int idSource, idDestination;
        double distance;
        std::fstream newFile;

        newFile.open(filename);

        if (newFile.fail()) {
            std::cout << "Invalid File - Please insert a valid file in the data folder.";
            exit(0);
        }

        if(filename.find("edges") == string::npos){
            getline(newFile,line);
        }

        while(true){

            if (newFile.eof()){
                break;
            }

            getline(newFile,line);

            if(line == ""){
                continue;
            }

            istringstream ss(line);

            try{
                getline(ss,idSourceStr,',');
                idSource = stoi(idSourceStr);
                getline(ss,idDestinationStr,',');
                idDestination = stoi(idDestinationStr);
                if(graphName != "tourism"){
                    getline(ss,distanceStr,'\r');
                    distance = stod(distanceStr);
                }
                else{
                    getline(ss,distanceStr,',');
                    distance = stod(distanceStr);
                    getline(ss,sourceName,',');
                    getline(ss,destinationName,'\r');
                }
            }

            catch (const std::exception& e) {
                std::cout << "The file " << filename << " is badly formatted. Please fix the file and reopen the program." << std::endl;
                exit(0);
            }

            Node sourceNode = Node(idSource);
            Node destinationNode = Node(idDestination);

            numberOfGraphEdges+=2;
            graph.addBidirectionalEdge(sourceNode,destinationNode,distance);

            if(graphName == "tourism"){
                Vertex* sourceVertex = graph.findVertex(sourceNode);
                sourceVertex->getInfo().setName(sourceName);
                Vertex* destinationVertex = graph.findVertex(destinationNode);
                destinationVertex->getInfo().setName(destinationName);
            }
        }
    }
    else{
        string filename = graphName + "/edges.csv";

        string line, idSourceStr, idDestinationStr, distanceStr;
        int idSource, idDestination;
        double distance;
        std::fstream newFile;

        newFile.open(filename);

        if (newFile.fail()) {
            std::cout << "Invalid File - Please insert a valid file in the data folder.";
            exit(0);
        }

        getline(newFile,line);


        while(true){

            if (newFile.eof()){
                break;
            }

            getline(newFile,line);

            if(line == ""){
                continue;
            }

            istringstream ss(line);

            try{
                getline(ss,idSourceStr,',');
                idSource = stoi(idSourceStr);
                getline(ss,idDestinationStr,',');
                idDestination = stoi(idDestinationStr);
                getline(ss,distanceStr,'\r');
                distance = stod(distanceStr);
            }

            catch (const std::exception& e) {
                std::cout << "The file " << filename << " is badly formatted. Please fix the file and reopen the program." << std::endl;
                exit(0);
            }

            Node sourceNode = Node(idSource);
            Node destinationNode = Node(idDestination);

            numberOfGraphEdges+=2;
            graph.addEdge(sourceNode,destinationNode,distance);
            graph.addEdge(destinationNode, sourceNode, distance);
        }
    }
}

void TSPAlgorithms::loadGraph() {
    unsigned int numberOfVertexes, numberOfEdges;
    loadGraphVertexes();
    numberOfVertexes = graph.getVertexSet().size();
    numberOfEdges = 0;
    loadGraphEdges(numberOfEdges);
    if(numberOfEdges == (numberOfVertexes * (numberOfVertexes - 1))){
        graphIsFullyConnected = true;
    }
    else{
        graphIsFullyConnected = false;
    }
}

void TSPAlgorithms::setAllVertexesAsUnvisited() {
    for(Vertex* vertex : graph.getVertexSet()){
        vertex->setVisited(false);
    }
}

void TSPAlgorithms::setAllVertexPathsNull(){
    for(Vertex* vertex : graph.getVertexSet()){
        vertex->setPath(nullptr);
    }
}

void TSPAlgorithms::DFSBacktracking(Vertex* vertex, double& distance, double &minDistance, stack<Node>& path,stack<Node>& minDistancePath) {
    if(path.size() == graph.getVertexSet().size()){
        double auxDistance;
        bool found_zero = false;
        for(Edge* edge : vertex->getAdj()){
            if(edge->getDest()->getInfo().getID() == 0){
                distance+=edge->getWeight();
                auxDistance = edge->getWeight();
                Node node = Node(0);
                path.push(node);
                found_zero = true;
                break;
            }
        }
        if(distance < minDistance && found_zero){
            minDistance = distance;
            minDistancePath = path;
        }
        distance-=auxDistance;
        path.pop();
        return;
    }
    for(Edge* edge : vertex->getAdj()){
        if(!edge->getDest()->isVisited()){
            vertex->setVisited(true);
            path.push(edge->getDest()->getInfo());
            distance+=edge->getWeight();
            DFSBacktracking(edge->getDest(), distance, minDistance, path, minDistancePath);
            vertex->setVisited(false);
            distance-=edge->getWeight();
            path.pop();
        }
    }
}

double TSPAlgorithms::getMinDistWithBackTracking(stack<Node> &minDistancePath) {
    for(Vertex* vertex : graph.getVertexSet()){
        vertex->setVisited(false);
        vertex->setPath(nullptr);
    }
    Node initialNode = Node(0);
    Vertex* initialVertex = graph.findVertex(initialNode);
    double minDistance = INT_MAX;
    double distance = 0;
    stack<Node> path;
    path.push(initialNode);
    DFSBacktracking(initialVertex,distance,minDistance,path,minDistancePath);
    return minDistance;
}

Vertex* TSPAlgorithms::findMinDistVertex(vector<Vertex *> vertexes) {
    double minDist = INT_MAX;
    Vertex* minDistVertex = nullptr;
    for(Vertex* vertex : vertexes){
        if(!vertex->isVisited() && vertex->getDist() < minDist){
            minDist = vertex->getDist();
            minDistVertex = vertex;
        }
    }
    return minDistVertex;
}

void TSPAlgorithms::primAlgorithm(Vertex* root) {
    vector<Vertex*> vertexes;
    unsigned int numberOfVertexesInTree = 1;

    for(Vertex* vertex :graph.getVertexSet()){
        vertex->setDist(INT_MAX);
        vertex->setPath(nullptr);
        vertexes.push_back(vertex);
    }


    for(Edge* edge : root->getAdj()){
        edge->getDest()->setDist(edge->getWeight());
        edge->getDest()->setPath(edge);
    }

    root->setVisited(true);

    while(numberOfVertexesInTree < graph.getVertexSet().size()){
        Vertex* minDistVertex = findMinDistVertex(vertexes);
        numberOfVertexesInTree++;
        minDistVertex->setVisited(true);
        for(Edge* edge : minDistVertex->getAdj()){
            if(!edge->getDest()->isVisited() && edge->getDest()->getDist() > edge->getWeight()){
                edge->getDest()->setDist(edge->getWeight());
                edge->getDest()->setPath(edge);
            }
        }
    }
}

void TSPAlgorithms::MSTPreOrderVisitDFS(Vertex *root, vector<Vertex*> &minDistancePath) {
    for(Edge* edge : root->getAdj()){
        if(edge->getDest()->getPath() == edge && !edge->getDest()->isVisited()){
            minDistancePath.push_back(edge->getDest());
            edge->getDest()->setVisited(true);
            MSTPreOrderVisitDFS(edge->getDest(),minDistancePath);
        }
    }
}

double TSPAlgorithms::getMinDistWithTriangularInequality(vector<Node> &minDistPath) {
    for(Vertex* vertex : graph.getVertexSet()){
        vertex->setVisited(false);
        vertex->setPath(nullptr);
    }
    Node rootNode = Node(0);
    Vertex* root = graph.findVertex(rootNode);
    primAlgorithm(root);
    for(Vertex* vertex : graph.getVertexSet()){
        if(vertex->getInfo().getID() != 0){
            vertex->setVisited(false);
        }
    }
    double minDistance = 0;
    vector<Vertex*> minDistPathVertexes;
    minDistPathVertexes.push_back(root);
    MSTPreOrderVisitDFS(root,minDistPathVertexes);
    minDistPathVertexes.push_back(root);
    bool foundEdge;
    for(int i = 0; i < minDistPathVertexes.size() - 1; i++){
        foundEdge = false;
        minDistPath.push_back(minDistPathVertexes[i]->getInfo());
        for(Edge* edge : minDistPathVertexes[i]->getAdj()){
            if(edge->getDest()->getInfo() == minDistPathVertexes[i + 1]->getInfo()){
                minDistance+=edge->getWeight();
                foundEdge = true;
                break;
            }
        }
        if(!foundEdge){
            Location defaultLocation = Location(INT_MIN,INT_MIN);
            if(minDistPathVertexes[i]->getInfo().getLocation() != defaultLocation){
                minDistance+=minDistPathVertexes[i]->getInfo().getLocation().getHaversineDistance(minDistPathVertexes[i + 1]->getInfo().getLocation());
            }
        }
    }
    minDistPath.push_back(rootNode);
    for(Edge* edge : root->getAdj()){
        if(edge->getDest()->getInfo() == minDistPathVertexes[minDistPathVertexes.size() - 1]->getInfo()){
            minDistance+=edge->getWeight();
            break;
        }
    }
    return minDistance;
}

double TSPAlgorithms::getNearestNeighbourDist(Vertex *vertex) {
    double minDist = INT_MAX;
    Vertex* selectedNode = nullptr;
    for(Edge* edge : vertex->getAdj()){
        if(!edge->getDest()->isVisited() && edge->getWeight() < minDist){
            minDist = edge->getWeight();
            selectedNode = edge->getDest();
        }
    }
    vertex = selectedNode;
    return minDist;
}

double TSPAlgorithms::getMinDistWithNearestNeighbourAnd2opt(vector<Node> &minDistPath) {
    setAllVertexesAsUnvisited();
    double minDist = 0;
    Node root = Node(0);
    Vertex* rootVertex = graph.findVertex(0);
    minDistPath.push_back(root);
    Vertex* currentVertex = rootVertex;
    currentVertex->setVisited(true);
    while(minDistPath.size() < graph.getVertexSet().size()){
        minDist+= getNearestNeighbourDist(currentVertex);
        currentVertex->setVisited(true);
        minDistPath.push_back(currentVertex->getInfo());
    }
    for(Edge* edge : currentVertex->getAdj()){
        if(edge->getDest()->getInfo() == root){
            minDist += edge->getWeight();
        }
    }
    return minDist;
}

double TSPAlgorithms::findOrCalculateDistanceBetweenVertexes(Vertex *v1, Vertex *v2) {
    Vertex* firstVertex = graph.findVertex(v1->getInfo());
    for(Edge* edge : firstVertex->getAdj()){
        if(edge->getDest()->getInfo() == v2->getInfo()){
            return edge->getWeight();
        }
    }
    Location defaultLocation = Location(INT_MIN, INT_MIN);
    if(v1->getInfo().getLocation() != defaultLocation && v2->getInfo().getLocation() != defaultLocation){
        return v1->getInfo().getLocation().getHaversineDistance(v2->getInfo().getLocation());
    }
    return 0;
}

void TSPAlgorithms::primAlgorithmChristofides(Graph& mstGraph, Vertex *root) {
    vector<Vertex*> vertexes;
    unsigned int numberOfVertexesInTree = 1;

    for(Vertex* vertex :graph.getVertexSet()){
        vertex->setDist(INT_MAX);
        vertex->setPath(nullptr);
        vertexes.push_back(vertex);
        mstGraph.addVertex(vertex->getInfo());
    }


    for(Edge* edge : root->getAdj()){
        edge->getDest()->setDist(edge->getWeight());
        edge->getDest()->setPath(edge);
    }

    root->setVisited(true);

    while(numberOfVertexesInTree < graph.getVertexSet().size()){
        Vertex* minDistVertex = findMinDistVertex(vertexes);
        Edge* pathEdge;
        numberOfVertexesInTree++;
        minDistVertex->setVisited(true);
        for(Edge* edge : minDistVertex->getAdj()){
            if(!edge->getDest()->isVisited() && edge->getDest()->getDist() > edge->getWeight()){
                edge->getDest()->setDist(edge->getWeight());
                edge->getDest()->setPath(edge);
                pathEdge = edge;
            }
        }
    }
    for (Vertex* vertex : vertexes) {
        Edge* pathEdge = vertex->getPath();
        if (pathEdge != nullptr) {
            mstGraph.addEdge(pathEdge->getOrig()->getInfo(), pathEdge->getDest()->getInfo(), pathEdge->getWeight());
            mstGraph.addEdge(pathEdge->getDest()->getInfo(), pathEdge->getOrig()->getInfo(), pathEdge->getWeight());
        }
    }
}

vector<Vertex*> TSPAlgorithms::getOddDegrees(Graph mstGraph) {
    vector<Vertex*> oddDegreeVertexes;
    for(Vertex* vertex : mstGraph.getVertexSet()){
        if(vertex->getAdj().size() % 2 != 0){
            oddDegreeVertexes.push_back(vertex);
        }
    }
    return oddDegreeVertexes;
}

bool TSPAlgorithms::edgeBetweenVertexes(Vertex *v1, Vertex *v2) {
    for(Edge* edge : v1->getAdj()){
        if(edge->getDest()->getInfo() == v2->getInfo()){
            return true;
        }
    }
    return false;
}

void TSPAlgorithms::findPerfectMatching(Graph& mstGraph, vector<Vertex*> oddDegreeVertexes){
    vector<Vertex*> vertexesWithEvenDegree;
    vector<bool> paired;
    for(unsigned int i = 0; i < oddDegreeVertexes.size(); i++){
        paired.push_back(false);
    }
    double minDistance = INT_MAX;
    double distance;
    int pairedVertexIndex;
    while(vertexesWithEvenDegree.size() < oddDegreeVertexes.size()){
        for(unsigned int i = 0; i < oddDegreeVertexes.size(); i++){
            if(paired[i]){
                continue;
            }
            for(unsigned j = i + 1; j < oddDegreeVertexes.size(); j++){
                if(paired[j] || edgeBetweenVertexes(oddDegreeVertexes[i],oddDegreeVertexes[j])){
                    continue;
                }
                distance = findOrCalculateDistanceBetweenVertexes(oddDegreeVertexes[i],oddDegreeVertexes[j]);
                if(minDistance > distance){
                    minDistance = distance;
                    pairedVertexIndex = j;
                }
            }
            vertexesWithEvenDegree.push_back(oddDegreeVertexes[i]);
            vertexesWithEvenDegree.push_back(oddDegreeVertexes[pairedVertexIndex]);
            paired[i] = true;
            paired[pairedVertexIndex] = true;
            mstGraph.addEdge(oddDegreeVertexes[i]->getInfo(), oddDegreeVertexes[pairedVertexIndex]->getInfo(),minDistance);
            mstGraph.addEdge(oddDegreeVertexes[pairedVertexIndex]->getInfo(), oddDegreeVertexes[i]->getInfo(),minDistance);
            minDistance = INT_MAX;
        }
    }
}

void TSPAlgorithms::setReverseEdgeAsTraversed(Edge *edge) {
    Vertex* reverseEdgeOrigin = edge->getDest();
    for(Edge* reverseEdge : reverseEdgeOrigin->getAdj()){
        if(reverseEdge->getDest()->getInfo() == edge->getOrig()->getInfo()){
            reverseEdge->setTraversed(true);
        }
    }
}

void TSPAlgorithms::setReverseEdgeAsUnTraversed(Edge *edge) {
    Vertex* reverseEdgeOrigin = edge->getDest();
    for(Edge* reverseEdge : reverseEdgeOrigin->getAdj()){
        if(reverseEdge->getDest()->getInfo() == edge->getOrig()->getInfo()){
            reverseEdge->setTraversed(false);
        }
    }
}

void TSPAlgorithms::dfsEdgeIsBridge(Vertex* vertex, unsigned int& numberOfReachableEdges){
    vertex->setVisited(true);
    numberOfReachableEdges++;
    for(Edge* edge : vertex->getAdj()){
        if(!edge->getDest()->isVisited() && !edge->isTraversed()){
            dfsEdgeIsBridge(edge->getDest(),numberOfReachableEdges);
        }
    }
}

bool TSPAlgorithms::edgeIsBridge(Edge *edge, Graph &mstGraph) {
    for(Vertex* vertex : mstGraph.getVertexSet()){
        vertex->setVisited(false);
    }
    Vertex* startNode = edge->getOrig();
    unsigned int numberOfUntraversedEdges = 0;
    for(Edge* edge : startNode->getAdj()){
        if(!edge->isTraversed()){
            numberOfUntraversedEdges++;
        }
    }
    if(numberOfUntraversedEdges == 1){
        return false;
    }
    unsigned int numberOfReachableVertexesWithEdge = 0;
    unsigned int numberOfReachableVertexesWithoutEdge = 0;
    dfsEdgeIsBridge(startNode,numberOfReachableVertexesWithEdge);
    for(Vertex* vertex : mstGraph.getVertexSet()){
        vertex->setVisited(false);
    }
    edge->setTraversed(true);
    setReverseEdgeAsTraversed(edge);
    dfsEdgeIsBridge(startNode,numberOfReachableVertexesWithoutEdge);
    edge->setTraversed(false);
    setReverseEdgeAsUnTraversed(edge);
    return numberOfReachableVertexesWithEdge > numberOfReachableVertexesWithoutEdge;
}

void TSPAlgorithms::eulerPathDFS(Vertex *vertex, vector<Vertex*> &eulerPath, Graph &mstGraph) {
    for(Edge* edge : vertex->getAdj()){
        if(!edge->isTraversed()){
            if(!edgeIsBridge(edge,mstGraph)){
                edge->setTraversed(true);
                setReverseEdgeAsTraversed(edge);
                eulerPath.push_back(edge->getDest());
                eulerPathDFS(edge->getDest(),eulerPath,mstGraph);
            }
        }
    }
}

vector<Vertex *> TSPAlgorithms::findEulerPath(Graph &mstGraph) {
    Node root = Node(0);
    Vertex* rootVertex = mstGraph.findVertex(root);
    vector<Vertex*> eulerPath;
    for(Vertex* vertex : mstGraph.getVertexSet()){
        vertex->setVisited(false);
        for(Edge* edge : vertex->getAdj()){
            edge->setTraversed(false);
        }
    }
    rootVertex->setVisited(true);
    unordered_set<Edge*> edges = rootVertex->getAdj();
    eulerPath.push_back(rootVertex);
    eulerPathDFS(rootVertex,eulerPath,mstGraph);
    return eulerPath;
}

vector<Vertex *> TSPAlgorithms::buildHamiltonianPath(vector<Vertex *> eulerPath) {
    vector<Vertex*> hamiltonianPath;
    for(Vertex* vertex : eulerPath){
        if(!vertex->isVisited()){
            vertex->setVisited(true);
            hamiltonianPath.push_back(vertex);
        }
    }
    if(eulerPath[eulerPath.size() - 1]->getInfo().getID() == 0){
        hamiltonianPath.push_back(eulerPath[eulerPath.size() - 1]);
    }
    return hamiltonianPath;
}

double TSPAlgorithms::getMinDistWithChristofidesAlgorithm(vector<Node> &minDistPath) {
    double minDistance = 0;
    for(Vertex* vertex : graph.getVertexSet()){
        vertex->setVisited(false);
        vertex->setPath(nullptr);
        for(Edge* edge : vertex->getAdj()){
            edge->setTraversed(false);
        }
    }
    Node rootNode = Node(0);
    Vertex* root = graph.findVertex(rootNode);
    Graph mstGraph;
    primAlgorithmChristofides(mstGraph,root);
    vector<Vertex*> vertexesWithOddDegrees;
    vertexesWithOddDegrees = getOddDegrees(mstGraph);
    findPerfectMatching(mstGraph,vertexesWithOddDegrees);
    vector<Vertex*> eulerPath = findEulerPath(mstGraph);
    for(Vertex* vertex :mstGraph.getVertexSet()){
        vertex->setVisited(false);
    }
    vector<Vertex*> hamiltonianPath = buildHamiltonianPath(eulerPath);
    for(unsigned int i = 0; i < hamiltonianPath.size() - 1; i++){
        minDistPath.push_back(hamiltonianPath[i]->getInfo());
        minDistance+=findOrCalculateDistanceBetweenVertexes(hamiltonianPath[i],hamiltonianPath[i + 1]);
    }
    minDistPath.push_back(hamiltonianPath[hamiltonianPath.size() - 1]->getInfo());
    return minDistance;
}


