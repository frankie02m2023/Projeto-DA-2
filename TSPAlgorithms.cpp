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
}

void TSPAlgorithms::loadGraphEdges(unsigned int& numberOfGraphEdges) {
    if(graphName != "graph1" && graphName != "graph2" && graphName != "graph3"){
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


    for(Edge<Node>* edge : root->getAdj()){
        edge->getDest()->setDist(edge->getWeight());
        edge->getDest()->setPath(edge);
        vertexes.push_back(edge->getDest());
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

double TSPAlgorithms::getMinDistWithTriangularInequity(vector<Node> &minDistPath) {
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
    for(int i = 0; i < minDistPathVertexes.size() - 1; i++){
        minDistPath.push_back(minDistPathVertexes[i]->getInfo());
        for(Edge<Node>* edge : minDistPathVertexes[i]->getAdj()){
            if(edge->getDest()->getInfo() == minDistPathVertexes[i + 1]->getInfo()){
                minDistance+=edge->getWeight();
                break;
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


