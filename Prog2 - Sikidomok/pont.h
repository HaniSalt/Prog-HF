#ifndef PONT_H
#define PONT_H
#include <iostream>
struct Pont {
    double x; 
    double y;
    Pont(double x = 0, double y = 0) :x(x), y(y) {}

    double getX() const { return x; }
    double getY() const { return y; }
    void setX(double px) { x = px; }
    void setY(double py) { y = py; }

};
#endif // PONT_H