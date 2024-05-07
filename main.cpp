//
// Created by franc on 07/05/2024.
//

#include "TSPAlgorithms.h"
 int main(){
    TSPAlgorithms tspAlgorithm = TSPAlgorithms("edges_500");
    tspAlgorithm.loadGraph();
    for(Vertex<Node>* vertex : tspAlgorithm.getGraph().getVertexSet()){
        for(Edge<Node>* edge : vertex->getAdj()){
            cout << vertex->getInfo().getID() << " -> " << edge->getDest()->getInfo().getID() << "  " << edge->getWeight() << endl;
        }
    }
    return 0;
}
