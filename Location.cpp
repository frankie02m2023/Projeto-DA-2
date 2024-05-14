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

double Location::getXInRadians() const {
    return (x * M_PI) / 180;
}

double Location::getYInRadians() const {
    return (y * M_PI) / 180;
}

double Location::getHaversineDistance(const Location &location) {
    double xRad, yRad, x1Rad, y1Rad;
    xRad = getXInRadians();
    yRad = getYInRadians();
    x1Rad = location.getXInRadians();
    y1Rad = location.getYInRadians();

    double deltaX = x1Rad - xRad;
    double deltaY = y1Rad - yRad;

    double a = pow(sin(deltaX / 2),2) + cos(xRad) * cos(x1Rad) * pow(sin(deltaY / 2), 2);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));

    return c * 6371000;
}

void Location::operator=(const Location &location) {
    x = location.x;
    y = location.y;
}
