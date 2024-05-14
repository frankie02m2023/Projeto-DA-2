//
// Created by franc on 07/05/2024.
//

#include "Location.h"

Location::Location(double x, double y){
    this->x = x;
    this->y = y;
}

double Location::getX() const {
    return x;
}

double Location::getY() const {
    return y;
}

void Location::setX(const double& x) {
    this->x = x;
}

void Location::setY(const double& y) {
    this->y = y;
}

double Location::getHaversineDistance(const Location &location) {
    //to be completed
    return 0;
}

void Location::operator=(const Location &location) {
    x = location.x;
    y = location.y;
}
