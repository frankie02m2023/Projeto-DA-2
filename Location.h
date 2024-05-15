//
// Created by franc on 07/05/2024.
//
#include <cmath>

class Location{
private:
    double x;
    double y;
public:
    Location() {};
    Location(double x, double y);
    double getX() const;
    double getY() const;
    void setX(const double& x);
    void setY(const double& y);
    void operator=(const Location& location);
    double getXInRadians() const;
    double getYInRadians() const;
    double getHaversineDistance(const Location& location);
};
