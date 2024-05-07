//
// Created by franc on 07/05/2024.
//

#include "TSPAlgorithms.h"
 int main(){
    TSPAlgorithms tspAlgorithm = TSPAlgorithms("tourism");
    tspAlgorithm.loadGraph();
    stack<Node> minPath;
    double minPathDistance = tspAlgorithm.getMinDistWithBackTracking(minPath);
    cout << minPathDistance << endl;
    while(!minPath.empty()){
        cout << minPath.top().getID() << " -> ";
        minPath.pop();
    }
    cout << endl;
    return 0;
}
