//
// Created by franc on 07/05/2024.
//

#include "TSPAlgorithms.h"
 int main(){
    TSPAlgorithms tspAlgorithm = TSPAlgorithms("edges_800");
    tspAlgorithm.loadGraph();
    cout << tspAlgorithm.getGraph().getVertexSet().size() << endl;
    cout << tspAlgorithm.isGraphFullyConnected() << endl;
    stack<Node> minPathStack;
    vector<Node> minPathVector;
    double minPathDistance = tspAlgorithm.getMinDistWithBackTracking(minPathStack);
    double minPathDistance1 = tspAlgorithm.getMinDistWithTriangularInequity(minPathVector);
    cout << minPathDistance << endl;
    while(!minPathStack.empty()){
        cout << minPathStack.top().getID() << " <- ";
        minPathStack.pop();
    }
    cout << endl;
    for(Node node : minPathVector){
        cout << node.getID() << " -> ";
    }
    cout << endl;
    cout << minPathDistance1 << endl;
    cout << endl;
    return 0;
}
