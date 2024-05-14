//
// Created by franc on 07/05/2024.
//

#include "TSPAlgorithms.h"
 int main(){
    TSPAlgorithms tspAlgorithm = TSPAlgorithms("stadiums");
    tspAlgorithm.loadGraph();
    stack<Node> minPathStack;
    vector<Node> minPathVector;
    double minPathDistance1 = tspAlgorithm.getMinDistWithTriangularInequity(minPathVector);
    for(Node node : minPathVector){
        cout << node.getID() << " -> ";
    }
    cout << endl;
    cout << minPathDistance1 << endl;
    cout << endl;
    return 0;
}
