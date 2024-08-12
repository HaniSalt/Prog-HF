#include <iostream>
#include <fstream>
#include "pont.h"
using std::string;

#ifndef SHAPE_H
#define SHAPE_H

class Shape {
protected:
    Pont v;  //Vertex
    Pont c;  //Center point
public:
    Shape(Pont C, Pont V) : v(V), c(C) {}
    virtual double calculateArea() = 0;
    virtual bool containsPoint(Pont p) = 0;
    virtual bool containsCircle(double radius) = 0;
    virtual string getName() = 0;
    virtual void printData()=0;
    virtual ~Shape(){}
};

std::istream& operator>>(std::istream& input, Pont& point);

std::istream& operator>>(std::istream& input, Shape** shape);
/*bool operator>>(std::istream& input, Pont& point);
bool operator>>(std::istream& input, Shape*& shape);*/

#endif