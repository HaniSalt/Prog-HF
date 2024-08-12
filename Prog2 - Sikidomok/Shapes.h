#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
#include <string>
#include "pont.h"
#include "Shape.h"
#ifndef SHAPES_H
#define SHAPES_H

using std::endl;
using std::cout;

class Triangle : public Shape {
private:
    Pont v2;  //Second vertex
    Pont v3;  //Third vertex

public:
    Triangle(Pont c, Pont v)
        : Shape(c, v) {
        double x1 = v.getX();
        double y1 = v.getY();
        double xc = c.getX();
        double yc = c.getY();

        double sideLength = std::sqrt((x1 - xc) * (x1 - xc) + (y1 - yc) * (y1 - yc));

        double angle = std::atan2(y1 - yc, x1 - xc);
        double angle120 = angle + (2.0 * 3.14 / 3.0);
        double angle240 = angle + (4.0 * 3.14 / 3.0);

        double x2 = xc + sideLength * std::cos(angle120);
        double y2 = yc + sideLength * std::sin(angle120);

        double x3 = xc + sideLength * std::cos(angle240);
        double y3 = yc + sideLength * std::sin(angle240);

        v2 = Pont(x2, y2);
        v3 = Pont(x3, y3);   
    }

    double calculateArea() override {
        //Calculate the area of the triangle using the vertices
        double x1 = v.getX();
        double y1 = v.getY();
        double x2 = v2.getX();
        double y2 = v2.getY();
        double x3 = v3.getX();
        double y3 = v3.getY();

        return std::abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
    }

    bool containsPoint(Pont p) override {
        //Check if the given point is inside the triangle using barycentric coordinates
        double x1 = v.getX();
        double y1 = v.getY();
        double x2 = v2.getX();
        double y2 = v2.getY();
        double x3 = v3.getX();
        double y3 = v3.getY();
        double x = p.getX();
        double y = p.getY();

        double denominator = ((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));
        double lambda1 = ((y2 - y3) * (x - x3) + (x3 - x2) * (y - y3)) / denominator;
        double lambda2 = ((y3 - y1) * (x - x3) + (x1 - x3) * (y - y3)) / denominator;
        double lambda3 = 1 - lambda1 - lambda2;

        return lambda1 >= 0 && lambda1 <= 1 && lambda2 >= 0 && lambda2 <= 1 && lambda3 >= 0 && lambda3 <= 1;
    }

    bool containsCircle(double radius) override {
        //Check if the circle with the given radius is completely contained within the triangle
        //We can check if the distance from the center of the circle to each side of the triangle is less than or equal to the radius

        double x1 = v.getX();
        double y1 = v.getY();
        double x2 = v2.getX();
        double y2 = v2.getY();
        double x3 = v3.getX();
        double y3 = v3.getY();

        double centerX = (x1 + x2 + x3) / 3.0; //Calculate the centroid of the triangle
        double centerY = (y1 + y2 + y3) / 3.0;

        double dist1 = abs((x2 - x1) * (centerY - y1) - (centerX - x1) * (y2 - y1)) / sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
        double dist2 = abs((x3 - x2) * (centerY - y2) - (centerX - x2) * (y3 - y2)) / sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
        double dist3 = abs((x1 - x3) * (centerY - y3) - (centerX - x3) * (y1 - y3)) / sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));

        return dist1 <= radius && dist2 <= radius && dist3 <= radius;
    }

    string getName() override {
        return "Triangle";
    }

    void printData() {
        cout << "Triangle" << std::endl;
        cout << "Center: (" << c.getX() << ", " << c.getY() << ")" << endl;
        cout << "Vertex: (" << v.getX() << ", " << v.getY() << ")" << endl;
    }
};


class Rectangle : public Shape {
public:
    Rectangle(Pont C, Pont V) :  Shape(C, V) {}

    double calculateArea() override {
        double width = std::abs(v.x - c.x);
        double height = std::abs(v.y - c.y);
        return width * height;
    }

    bool containsPoint(Pont p) override {
        //Check if the point is inside the rectangle
        double minX = std::min(c.x, v.x);
        double maxX = std::max(c.x, v.x);
        double minY = std::min(c.y, v.y);
        double maxY = std::max(c.y, v.y);

        return p.x >= minX && p.x <= maxX && p.y >= minY && p.y <= maxY;
    }

    bool containsCircle(double radius) override {
        //Check if the rectangle contains a circle with the given radius centered at the origin
        //Check if all four corners of the rectangle are within the circle
        
        //Calculate the positions of the rectangle's corners
        double minX = std::min(c.x, v.x);
        double maxX = std::max(c.x, v.x);
        double minY = std::min(c.y, v.y);
        double maxY = std::max(c.y, v.y);

        //Check if all four corners of the rectangle are within or on the boundary of the circle
        return (minX * minX + minY * minY <= radius * radius) &&
            (minX * minX + maxY * maxY <= radius * radius) &&
            (maxX * maxX + minY * minY <= radius * radius) &&
            (maxX * maxX + maxY * maxY <= radius * radius);
    }

    std::string getName() override {
        return "Rectangle";
    }

    void printData() {
        std::cout << "Rectangle" << std::endl;
        std::cout << "Center: (" << c.x << ", " << c.y << ")" << std::endl;
        std::cout << "Vertex: (" << v.x << ", " << v.y << ")" << std::endl;
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(Pont C, Pont P) : Shape(C, P), radius(0) {
        double dx = P.x - C.x;
        double dy = P.y - C.y;
        radius = std::sqrt(dx * dx + dy * dy);
    }

    double calculateArea() override {
        double area = 3.14 * radius * radius;
        return area;
    }

    bool containsPoint(Pont p) override {
        return p.x * p.x + p.y * p.y <= radius * radius;
    }

    bool containsCircle(double otherRadius) override {
        //Check if the circle contains another circle with the given radius

        //Calculate the distance between the centers of the circles
        double dx = v.x - c.x;
        double dy = v.y - c.y;
        double distance = std::sqrt(dx * dx + dy * dy);

        //Calculate the minimum distance required for the other circle to be completely contained
        double minDistance = radius - otherRadius;

        //Check if the minimum distance is greater than or equal to the distance between the centers
        return minDistance >= distance;
    }

    std::string getName() override {
        return "Circle";
    }
    void printData() {
        std::cout << "Circle" << std::endl;
        std::cout << "Center: (" << c.x << ", " << c.y << ")" << std::endl;
        std::cout << "Vertex: (" << v.x << ", " << v.y << ")" << std::endl;
    }

};

#endif //SHAPES_H