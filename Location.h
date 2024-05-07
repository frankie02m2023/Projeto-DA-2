//
// Created by franc on 07/05/2024.
//
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
    double getHaversineDistance(const Location& location);
};
