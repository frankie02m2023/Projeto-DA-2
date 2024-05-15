//
// Created by Beatriz Pereira on 15/05/2024.
//

#include <iostream>
#include "Menu.h"

using namespace std;

#include <iostream>
#include "Menu.h"

using namespace std;

Menu::Menu() {}

void Menu::graphMenu() {
    int choice = 0;
    while (true) {
        cout << "\n******************************  Travelling Salesperson Problem  *******************************\n";

        cout << "*** Select the number of the option that corresponds to the type of graph you wish to load: ***"<< '\n';

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
                return;
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
                    tspAlgorithm1.loadGraph();
                }
                break;
            case 2:
                cout << "Loading Stadiums Toy Graph..." << endl;
                {
                    string GraphName2 = "stadiums";
                    TSPAlgorithms tspAlgorithm2(GraphName2);
                    tspAlgorithm2.loadGraph();
                }
                break;
            case 3:
                cout << "Loading Tourism Toy Graph..." << endl;
                {
                    string GraphName3 = "tourism";
                    TSPAlgorithms tspAlgorithm3(GraphName3);
                    tspAlgorithm3.loadGraph();
                }
                break;
            case 4:
                graphMenu();
                break;
            case 5:
                cout << "Exiting..." << endl;
                return;
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
    while (true) {
        switch (choice) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 10:
                break;
            case 11:
                break;
            case 12:
                break;
            case 13:
                graphMenu();
                break;
            case 14:
                cout << "Exiting..." << endl;
                return;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
        break;
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
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                graphMenu();
                break;
            case 5:
                cout << "Exiting..." << endl;
                return;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
        break;
    }
}

void Menu::algorithmMenu() {
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
        cout << " Our own algorithm                                             ";
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
        handleAlgorithmMenu(choice);
        break;
    }
}
void Menu::handleAlgorithmMenu(int choice) {
    while (true) {
        graphMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Solving TSP with Backtracking..." << endl;
                break;
            case 2:
                cout << "Solving TSP with Triangular Inequality..." << endl;
                break;
            case 3:
                cout << "Solving TSP with our Algorithm..." << endl;
                break;
            case 4:
                cout << "Going back to Graph Selection..." << endl;
                graphMenu();
                return;
            case 5:
                cout << "Exiting..." << endl;
                return;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }
}