//
// Created by Beatriz Pereira on 15/05/2024.
//

#ifndef PROJETO_DA_2_MENU_H
#define PROJETO_DA_2_MENU_H

#include "TSPAlgorithms.h"

class Menu {
    public:
        Menu();
        void graphMenu();
        void algorithmMenu();
        void handleGraphMenu(int choice);
        void handleAlgorithmMenu(int choice);
        void toyGraphs();
        void realWorldGraphs();
        void mediumGraphs();
        void handleToyGraphs(int choice);
        void handleMediumGraphs(int choice);
        void handleRealWorldGraphs(int choice);
};

#endif //PROJETO_DA_2_MENU_H
