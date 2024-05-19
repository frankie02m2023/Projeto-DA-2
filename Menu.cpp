//
// Created by Beatriz Pereira on 15/05/2024.
//

#include <iostream>
#include <vector>
#include <string>
#include "Menu.h"

using namespace std;

Menu::Menu() {}

void Menu::graphMenu() {
    int choice = 0;
    while (true) {
        cout << "\n******************************  Travelling Salesperson Problem  *******************************\n";

        cout << "*** Select the number of the option that corresponds to the type of graph you wish to load: ***" << '\n';

        cout << "****** 1.";
        cout << " Toy Graphs                                                                     ";
        cout << "******\n";

        cout << "****** 2.";
        cout << " Real-World Graphs                                                              ";
        cout << "******\n";

        cout << "****** 3.";
        cout << " Extra Medium-Size Graphs                                                       ";
        cout << "******\n";

        cout << "******";
        cout << " 4. Exit                                                                           ";
        cout << "******\n";

        cout << "***********************************************************************************************\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        if (choice == 4) { break; }
        handleGraphMenu(choice);
        break;
    }
}

void Menu::handleGraphMenu(int choice) {
    while (true) {
        switch (choice) {
            case 1:
                cout << "Loading Toy Graphs..." << endl;
                toyGraphs();
                break;
            case 2:
                cout << "Loading Real-world Graphs..." << endl;
                realWorldGraphs();
                break;
            case 3:
                cout << "Loading Extra Medium-Size Graphs..." << endl;
                mediumGraphs();
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }
}

void Menu::toyGraphs() {
    int choice = 0;
    while (true) {
        cout << "\n******************************  Travelling Salesperson Problem  *******************************\n";

        cout << "****** 1.";
        cout << " Shipping                                                                       ";
        cout << "******\n";

        cout << "****** 2.";
        cout << " Stadiums                                                                       ";
        cout << "******\n";

        cout << "****** 3.";
        cout << " Tourism                                                                        ";
        cout << "******\n";

        cout << "******";
        cout << " 4. Back                                                                           ";
        cout << "******\n";

        cout << "******";
        cout << " 5. Exit                                                                           ";
        cout << "******\n";

        cout << "***********************************************************************************************\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        if (choice == 5) { break; }
        handleToyGraphs(choice);
        break;
    }
}

void Menu::handleToyGraphs(int choice) {
    while (true) {
        switch (choice) {
            case 1:
                cout << "Loading Shipping Toy Graph..." << endl;
                {
                    string GraphName1 = "shipping";
                    TSPAlgorithms tspAlgorithm1(GraphName1);
                    auto start = chrono::high_resolution_clock::now();
                    tspAlgorithm1.loadGraph();
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double> duration = end - start;
                    cout << "Loading time: " << duration.count() << " seconds" << endl;
                    algorithmMenu(tspAlgorithm1);
                }
                break;
            case 2:
                cout << "Loading Stadiums Toy Graph..." << endl;
                {
                    string GraphName2 = "stadiums";
                    TSPAlgorithms tspAlgorithm2(GraphName2);
                    auto start = chrono::high_resolution_clock::now();
                    tspAlgorithm2.loadGraph();
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double> duration = end - start;
                    cout << "Loading time: " << duration.count() << " seconds" << endl;
                    algorithmMenu(tspAlgorithm2);
                }
                break;
            case 3:
                cout << "Loading Tourism Toy Graph..." << endl;
                {
                    string GraphName3 = "tourism";
                    TSPAlgorithms tspAlgorithm3(GraphName3);
                    auto start = chrono::high_resolution_clock::now();
                    tspAlgorithm3.loadGraph();
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double> duration = end - start;
                    cout << "Loading time: " << duration.count() << " seconds" << endl;
                    algorithmMenu(tspAlgorithm3);
                }
                break;
            case 4:
                graphMenu();
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
        break;
    }
}

void Menu::mediumGraphs() {
    int choice = 0;
    while (true) {
        cout << "\n******************************  Travelling Salesperson Problem  *******************************\n";

        cout << "****** 1.";
        cout << " Medium - 25 nodes                                                              ";
        cout << "******\n";

        cout << "****** 2.";
        cout << " Medium - 50 nodes                                                              ";
        cout << "******\n";

        cout << "****** 3.";
        cout << " Medium - 75 nodes                                                              ";
        cout << "******\n";

        cout << "****** 4.";
        cout << " Medium - 100 nodes                                                             ";
        cout << "******\n";

        cout << "****** 5.";
        cout << " Medium - 200 nodes                                                             ";
        cout << "******\n";

        cout << "****** 6.";
        cout << " Medium - 300 nodes                                                             ";
        cout << "******\n";

        cout << "****** 7.";
        cout << " Medium - 400 nodes                                                             ";
        cout << "******\n";

        cout << "****** 8.";
        cout << " Medium - 500 nodes                                                             ";
        cout << "******\n";

        cout << "****** 9.";
        cout << " Medium - 600 nodes                                                             ";
        cout << "******\n";

        cout << "****** 10.";
        cout << " Medium - 700 nodes                                                            ";
        cout << "******\n";

        cout << "****** 11.";
        cout << " Medium - 800 nodes                                                            ";
        cout << "******\n";

        cout << "****** 12.";
        cout << " Medium - 900 nodes                                                            ";
        cout << "******\n";

        cout << "******";
        cout << " 13. Back                                                                          ";
        cout << "******\n";

        cout << "******";
        cout << " 14. Exit                                                                          ";
        cout << "******\n";

        cout << "***********************************************************************************************\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        if (choice == 14) { break; }
        handleMediumGraphs(choice);
        break;
    }
}

void Menu::handleMediumGraphs(int choice) {
    vector<string> edgeFiles = {
            "edges_25", "edges_50", "edges_75", "edges_100",
            "edges_200", "edges_300", "edges_400", "edges_500",
            "edges_600", "edges_700", "edges_800", "edges_900"
    };

    while (true) {
        if (choice >= 1 && choice <= 12) {
            cout << "Loading the selected Medium Graph..." << endl;
            TSPAlgorithms tspAlgorithm(edgeFiles[choice - 1]);
            auto start = chrono::high_resolution_clock::now();
            tspAlgorithm.loadGraph();
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> duration = end - start;
            cout << "Loading time: " << duration.count() << " seconds" << endl;
            algorithmMenu(tspAlgorithm);
            break;
        } else if (choice == 13) {
            graphMenu();
            break;
        } else if (choice == 14) {
            cout << "Exiting..." << endl;
            break;
        } else {
            cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }
}

void Menu::realWorldGraphs() {
    int choice = 0;
    while (true) {
        cout << "\n******************************  Travelling Salesperson Problem  *******************************\n";

        cout << "****** 1.";
        cout << " Real 1                                                                         ";
        cout << "******\n";

        cout << "****** 2.";
        cout << " Real 2                                                                         ";
        cout << "******\n";

        cout << "****** 3.";
        cout << " Real 3                                                                         ";
        cout << "******\n";

        cout << "******";
        cout << " 4. Back                                                                           ";
        cout << "******\n";

        cout << "******";
        cout << " 5. Exit                                                                           ";
        cout << "******\n";

        cout << "***********************************************************************************************\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        if (choice == 5) { break; }
        handleRealWorldGraphs(choice);
        break;
    }
}

void Menu::handleRealWorldGraphs(int choice) {
    while (true) {
        switch (choice) {
            case 1:
            {
                cout << "Loading Real World Graph 1..." << endl;
                string GraphName1 = "Graph1";
                TSPAlgorithms tspAlgorithm1(GraphName1);
                auto start = chrono::high_resolution_clock::now();
                tspAlgorithm1.loadGraph();
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> duration = end - start;
                cout << "Loading time: " << duration.count() << " seconds" << endl;
                algorithmMenu(tspAlgorithm1);
            }
                break;
            case 2:
            {
                cout << "Loading Real World Graph 2..." << endl;
                string GraphName2 = "Graph2";
                TSPAlgorithms tspAlgorithm2(GraphName2);
                auto start = chrono::high_resolution_clock::now();
                tspAlgorithm2.loadGraph();
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> duration = end - start;
                cout << "Loading time: " << duration.count() << " seconds" << endl;
                algorithmMenu(tspAlgorithm2);
            }
                break;
            case 3:
            {
                cout << "Loading Real World Graph 3..." << endl;
                string GraphName3 = "Graph3";
                TSPAlgorithms tspAlgorithm3(GraphName3);
                auto start = chrono::high_resolution_clock::now();
                tspAlgorithm3.loadGraph();
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> duration = end - start;
                cout << "Loading time: " << duration.count() << " seconds" << endl;
                algorithmMenu(tspAlgorithm3);
            }
                break;
            case 4:
                graphMenu();
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
        break;
    }
}

void Menu::algorithmMenu(TSPAlgorithms tspAlgorithm) {
    int choice = 0;
    while (true) {
        cout << "\n**********************  Travelling Salesperson Problem  **********************\n";

        cout << "****** 1.";
        cout << " Solve TSP with Backtracking                                   ";
        cout << "******\n";

        cout << "****** 2.";
        cout << " Solve TSP with Triangular Inequality                          ";
        cout << "******\n";

        cout << "****** 3.";
        cout << " Solve TSP with Christofides Algorithm                         ";
        cout << "******\n";

        cout << "******";
        cout << " 4. Back                                                          ";
        cout << "******\n";

        cout << "******";
        cout << " 5. Exit                                                          ";
        cout << "******\n";

        cout << "******************************************************************************\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        if (choice == 5) { break; }
        handleAlgorithmMenu(choice, tspAlgorithm);
        break;
    }
}

void Menu::handleAlgorithmMenu(int choice, TSPAlgorithms tspAlgorithm) {
    while (true) {
        switch (choice) {
            case 1: {
                stack<Node> minPath;
                auto start = chrono::high_resolution_clock::now();
                double minPathDistance = tspAlgorithm.getMinDistWithBackTracking(minPath);
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> duration = end - start;
                cout << "Minimum Path Distance: " << minPathDistance << endl;
                while (!minPath.empty()) {
                    cout << minPath.top().getID() << " -> ";
                    minPath.pop();
                }
                cout << "END" << endl;
                std::cout << "Backtracking execution time: " << duration.count() << " seconds" << std::endl;
            }
                break;
            case 2: {
                vector<Node> minPath;
                auto start = chrono::high_resolution_clock::now();
                double minPathDistance = tspAlgorithm.getMinDistWithTriangularInequality(minPath);
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> duration = end - start;
                cout << "Minimum Path Distance: " << minPathDistance << endl;
                for(Node node : minPath){
                    cout << node.getID() << " -> ";
                }
                cout << "END" << endl;
                cout << "Triangular inequality execution time: " << duration.count() << " seconds" << endl;
            }
                break;
            case 3: {
                vector<Node> minPath;
                auto start = chrono::high_resolution_clock::now();
                double minPathDistance = tspAlgorithm.getMinDistWithChristofidesAlgorithm(minPath);
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> duration = end - start;
                cout << "Minimum Path Distance: " << minPathDistance << endl;
                for(Node node : minPath){
                    cout << node.getID() << " -> ";
                }
                cout << "END" << endl;
                cout << "Christofides execution time: " << duration.count() << " seconds" << endl;
            }
                break;
            case 4:
                cout << "Going back to Graph Selection..." << endl;
                graphMenu();
            case 5:
                cout << "Exiting..." << endl;
                exit(0);  // Exit the program
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
        algorithmMenu(tspAlgorithm);
    }
}
