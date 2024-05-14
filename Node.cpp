//
// Created by franc on 07/05/2024.
//

#include "Node.h"

Node::Node(int id){
    this->id = id;
    this->name = "";
    this->location = Location(-1,-1);
}

Node::Node(int id, string name) {
    this->id = id;
    this->name = name;
    this->location = Location(-1,-1);
}

Node::Node(int id, Location location) {
    this->id = id;
    this->name = "";
    this->location = location;
}

Node::Node(int id, string name, Location location) {
    this->id = id;
    this->name = name;
    this->location = location;
}

int Node::getID() const {
    return id;
}

string Node::getName() const {
    return name;
}

Location Node::getLocation() const {
    return location;
}

bool Node::operator==(const Node &node) const {
    return id == node.id;
}

void Node::setName(string name) {
    this->name = name;
}

bool Node::operator<(const Node &node) const {
    return id < node.id;
}

bool Node::operator>(const Node &node) const {
    return id > node.id;
}

bool Node::operator!=(const Node &node) const {
    return id != node.id;
}

void Node::operator=(const Node &node) {
    id = node.id;
    name = node.name;
    location = node.location;
}



