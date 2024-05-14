//
// Created by franc on 07/05/2024.
//

#ifndef DA2324_P03_STUDENT_NODE_H
#define DA2324_P03_STUDENT_NODE_H

#include <string>
#include "Location.h"
using namespace std;


class Node{
private:
    int id;
    string name;
    Location location;
public:
    Node(int id);
    Node(int id, string name);
    Node(int id, Location location);
    Node(int id, string name, Location location);
    int getID() const;
    string getName() const;
    Location getLocation() const;
    void setName(string name);
    void operator=(const Node& node);
    bool operator()(const Node& node) const;
    bool operator==(const Node& node) const;
    bool operator<(const Node& node) const;
    bool operator<=(const Node& node) const;
    bool operator>(const Node& node) const;
    bool operator>=(const Node& node) const;
    bool operator!=(const Node& node) const;
};

#endif //DA2324_P03_STUDENT_NODE_H