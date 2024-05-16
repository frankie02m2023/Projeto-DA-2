//
// Created by franc on 07/05/2024.
//

#include <fstream>
#include <sstream>
#include "TSPAlgorithms.h"
#include "MutablePriorityQueue.h"

Graph<Node> TSPAlgorithms::getGraph() const {
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
            graph.addEdge(sourceNode,destinationNode,distance);
            graph.addEdge(destinationNode, sourceNode, distance);

            if(graphName == "tourism"){
                Vertex<Node>* sourceVertex = graph.findVertex(sourceNode);
                sourceVertex->getInfo().setName(sourceName);
                Vertex<Node>* destinationVertex = graph.findVertex(destinationNode);
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
    for(Vertex<Node>* vertex : graph.getVertexSet()){
        vertex->setVisited(false);
    }
}

void TSPAlgorithms::setAllVertexPathsNull(){
    for(Vertex<Node>* vertex : graph.getVertexSet()){
        vertex->setPath(nullptr);
    }
}

void TSPAlgorithms::DFSBacktracking(Vertex<Node>* vertex, double& distance, double &minDistance, stack<Node>& path,stack<Node>& minDistancePath) {
    if(path.size() == graph.getVertexSet().size()){
        double auxDistance;
        bool found_zero = false;
        for(Edge<Node>* edge : vertex->getAdj()){
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
    for(Edge<Node>* edge : vertex->getAdj()){
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
    setAllVertexesAsUnvisited();
    setAllVertexPathsNull();
    Node initialNode = Node(0);
    Vertex<Node>* initialVertex = graph.findVertex(initialNode);
    double minDistance = INT_MAX;
    double distance = 0;
    stack<Node> path;
    path.push(initialNode);
    DFSBacktracking(initialVertex,distance,minDistance,path,minDistancePath);
    return minDistance;
}

Vertex<Node> *TSPAlgorithms::findMinDistVertex(vector<Vertex<Node> *> vertexes) {
    double minDist = INT_MAX;
    Vertex<Node>* minDistVertex = nullptr;
    for(Vertex<Node>* vertex : vertexes){
        if(!vertex->isVisited() && vertex->getDist() < minDist){
            minDist = vertex->getDist();
            minDistVertex = vertex;
        }
    }
    return minDistVertex;
}

void TSPAlgorithms::primAlgorithm(Vertex<Node>* root) {
    vector<Vertex<Node>*> vertexes;
    unsigned int numberOfVertexesInTree = 1;

    for(Vertex<Node>* vertex :graph.getVertexSet()){
        vertex->setDist(INT_MAX);
        vertex->setPath(nullptr);
        vertexes.push_back(vertex);
    }


    for(Edge<Node>* edge : root->getAdj()){
        edge->getDest()->setDist(edge->getWeight());
        edge->getDest()->setPath(edge);
    }

    root->setVisited(true);

    while(numberOfVertexesInTree < graph.getVertexSet().size()){
        Vertex<Node>* minDistVertex = findMinDistVertex(vertexes);
        numberOfVertexesInTree++;
        minDistVertex->setVisited(true);
        for(Edge<Node>* edge : minDistVertex->getAdj()){
            if(!edge->getDest()->isVisited() && edge->getDest()->getDist() > edge->getWeight()){
                edge->getDest()->setDist(edge->getWeight());
                edge->getDest()->setPath(edge);
            }
        }
    }
}

void TSPAlgorithms::MSTPreOrderVisitDFS(Vertex<Node> *root, vector<Vertex<Node>*> &minDistancePath) {
    for(Edge<Node>* edge : root->getAdj()){
        if(edge->getDest()->getPath() == edge && !edge->getDest()->isVisited()){
            minDistancePath.push_back(edge->getDest());
            edge->getDest()->setVisited(true);
            MSTPreOrderVisitDFS(edge->getDest(),minDistancePath);
        }
    }
}

double TSPAlgorithms::getMinDistWithTriangularInequality(vector<Node> &minDistPath) {
    for(Vertex<Node>* vertex : graph.getVertexSet()){
        vertex->setVisited(false);
        vertex->setPath(nullptr);
    }
    Node rootNode = Node(0);
    Vertex<Node>* root = graph.findVertex(rootNode);
    primAlgorithm(root);
    for(Vertex<Node>* vertex : graph.getVertexSet()){
        if(vertex->getInfo().getID() != 0){
            vertex->setVisited(false);
        }
    }
    double minDistance = 0;
    vector<Vertex<Node>*> minDistPathVertexes;
    minDistPathVertexes.push_back(root);
    MSTPreOrderVisitDFS(root,minDistPathVertexes);
    minDistPathVertexes.push_back(root);
    bool foundEdge;
    for(int i = 0; i < minDistPathVertexes.size() - 1; i++){
        foundEdge = false;
        minDistPath.push_back(minDistPathVertexes[i]->getInfo());
        for(Edge<Node>* edge : minDistPathVertexes[i]->getAdj()){
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
    for(Edge<Node>* edge : root->getAdj()){
        if(edge->getDest()->getInfo() == minDistPathVertexes[minDistPathVertexes.size() - 1]->getInfo()){
            minDistance+=edge->getWeight();
            break;
        }
    }
    return minDistance;
}

double TSPAlgorithms::getNearestNeighbourDist(Vertex<Node> *vertex) {
    double minDist = INT_MAX;
    Vertex<Node>* selectedNode = nullptr;
    for(Edge<Node>* edge : vertex->getAdj()){
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
    Vertex<Node>* rootVertex = graph.findVertex(0);
    minDistPath.push_back(root);
    Vertex<Node>* currentVertex = rootVertex;
    currentVertex->setVisited(true);
    while(minDistPath.size() < graph.getVertexSet().size()){
        minDist+= getNearestNeighbourDist(currentVertex);
        currentVertex->setVisited(true);
        minDistPath.push_back(currentVertex->getInfo());
    }
    for(Edge<Node>* edge : currentVertex->getAdj()){
        if(edge->getDest()->getInfo() == root){
            minDist += edge->getWeight();
        }
    }
    return minDist;
}

double TSPAlgorithms::findOrCalculateDistanceBetweenVertexes(Vertex<Node> *v1, Vertex<Node> *v2) {
    Vertex<Node>* firstVertex = graph.findVertex(v1->getInfo());
    for(Edge<Node>* edge : firstVertex->getAdj()){
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

void TSPAlgorithms::primAlgorithmChristofides(Graph<Node>& mstGraph, Vertex<Node> *root) {
    vector<Vertex<Node>*> vertexes;
    unsigned int numberOfVertexesInTree = 1;

    for(Vertex<Node>* vertex :graph.getVertexSet()){
        vertex->setDist(INT_MAX);
        vertex->setPath(nullptr);
        vertexes.push_back(vertex);
        mstGraph.addVertex(vertex->getInfo());
    }


    for(Edge<Node>* edge : root->getAdj()){
        edge->getDest()->setDist(edge->getWeight());
        edge->getDest()->setPath(edge);
    }

    root->setVisited(true);

    while(numberOfVertexesInTree < graph.getVertexSet().size()){
        Vertex<Node>* minDistVertex = findMinDistVertex(vertexes);
        Edge<Node>* pathEdge;
        numberOfVertexesInTree++;
        minDistVertex->setVisited(true);
        for(Edge<Node>* edge : minDistVertex->getAdj()){
            if(!edge->getDest()->isVisited() && edge->getDest()->getDist() > edge->getWeight()){
                edge->getDest()->setDist(edge->getWeight());
                edge->getDest()->setPath(edge);
                pathEdge = edge;
            }
        }
    }
    for (Vertex<Node>* vertex : vertexes) {
        Edge<Node>* pathEdge = vertex->getPath();
        if (pathEdge != nullptr) {
            mstGraph.addEdge(pathEdge->getOrig()->getInfo(), pathEdge->getDest()->getInfo(), pathEdge->getWeight());
            mstGraph.addEdge(pathEdge->getDest()->getInfo(), pathEdge->getOrig()->getInfo(), pathEdge->getWeight());
        }
    }
}

vector<Vertex<Node>*> TSPAlgorithms::getOddDegrees(Graph<Node> mstGraph) {
    vector<Vertex<Node>*> oddDegreeVertexes;
    for(Vertex<Node>* vertex : mstGraph.getVertexSet()){
        if(vertex->getAdj().size() % 2 != 0){
            oddDegreeVertexes.push_back(vertex);
        }
    }
    return oddDegreeVertexes;
}

bool TSPAlgorithms::edgeBetweenVertexes(Vertex<Node> *v1, Vertex<Node> *v2) {
    for(Edge<Node>* edge : v1->getAdj()){
        if(edge->getDest()->getInfo() == v2->getInfo()){
            return true;
        }
    }
    return false;
}

void TSPAlgorithms::findPerfectMatching(Graph<Node>& mstGraph, vector<Vertex<Node>*> oddDegreeVertexes){
    vector<Vertex<Node>*> vertexesWithEvenDegree;
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

void TSPAlgorithms::setReverseEdgeAsTraversed(Edge<Node> *edge) {
    Vertex<Node>* reverseEdgeOrigin = edge->getDest();
    for(Edge<Node>* reverseEdge : reverseEdgeOrigin->getAdj()){
        if(reverseEdge->getDest()->getInfo() == edge->getOrig()->getInfo()){
            reverseEdge->setTraversed(true);
        }
    }
}

void TSPAlgorithms::eulerPathDFS(Vertex<Node> *vertex, vector<Vertex<Node>*> &eulerPath) {
    for(Edge<Node>* edge : vertex->getAdj()){
        if(!edge->isTraversed()){
            edge->setTraversed(true);
            setReverseEdgeAsTraversed(edge);
            eulerPath.push_back(edge->getDest());
            eulerPathDFS(edge->getDest(),eulerPath);
        }
    }
}

vector<Vertex<Node> *> TSPAlgorithms::findEulerPath(Graph<Node> &mstGraph) {
    Node root = Node(0);
    Vertex<Node>* rootVertex = mstGraph.findVertex(root);
    vector<Vertex<Node>*> eulerPath;
    for(Vertex<Node>* vertex : mstGraph.getVertexSet()){
        vertex->setVisited(false);
        for(Edge<Node>* edge : vertex->getAdj()){
            edge->setTraversed(false);
        }
    }
    rootVertex->setVisited(true);
    vector<Edge<Node>*> edges = rootVertex->getAdj();
    Vertex<Node>* testVertex = edges[edges.size() - 1]->getDest();
    eulerPath.push_back(rootVertex);
    eulerPathDFS(rootVertex,eulerPath);
    return eulerPath;
}

vector<Vertex<Node> *> TSPAlgorithms::buildHamiltonianPath(vector<Vertex<Node> *> eulerPath) {
    vector<Vertex<Node>*> hamiltonianPath;
    unsigned int rootCount = 0;
    for(Vertex<Node>* vertex : eulerPath){
        if(!vertex->isVisited()){
            vertex->setVisited(true);
            if(vertex->getInfo().getID() == 0  && rootCount == 0){
                rootCount++;
                vertex->setVisited(false);
            }
            hamiltonianPath.push_back(vertex);
        }
    }
    return hamiltonianPath;
}

double TSPAlgorithms::getMinDistWithChristofidesAlgorithm(vector<Node> &minDistPath) {
    double minDistance = 0;
    for(Vertex<Node>* vertex : graph.getVertexSet()){
        vertex->setVisited(false);
        vertex->setPath(nullptr);
    }
    Node rootNode = Node(0);
    Vertex<Node>* root = graph.findVertex(rootNode);
    Graph<Node> mstGraph;
    primAlgorithmChristofides(mstGraph,root);
    vector<Vertex<Node>*> vertexesWithOddDegrees;
    vertexesWithOddDegrees = getOddDegrees(mstGraph);
    findPerfectMatching(mstGraph,vertexesWithOddDegrees);
    vector<Vertex<Node>*> eulerPath = findEulerPath(mstGraph);
    for(Vertex<Node>* vertex :mstGraph.getVertexSet()){
        vertex->setVisited(false);
    }
    vector<Vertex<Node>*> hamiltonianPath = buildHamiltonianPath(eulerPath);
    for(unsigned int i = 0; i < hamiltonianPath.size() - 1; i++){
        minDistPath.push_back(hamiltonianPath[i]->getInfo());
        minDistance+=findOrCalculateDistanceBetweenVertexes(hamiltonianPath[i],hamiltonianPath[i + 1]);
    }
    minDistPath.push_back(hamiltonianPath[hamiltonianPath.size() - 1]->getInfo());
    return minDistance;
}


