//
// Created by franc on 07/05/2024.
//

#include <fstream>
#include <sstream>
#include "TSPAlgorithms.h"

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

void TSPAlgorithms::loadGraphVertexes() {
    string filename;
    if(graphName == "shipping" || graphName == "stadium" || graphName == "tourism"){
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
        int pos2 = graphName.find('.');
        int maxVertexNumber = stoi(graphName.substr(pos1 + 1, pos2 - pos1 - 1));
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

void TSPAlgorithms::loadGraphEdges() {
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

            graph.addEdge(sourceNode,destinationNode,distance);

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
    loadGraphVertexes();
    loadGraphEdges();
}
