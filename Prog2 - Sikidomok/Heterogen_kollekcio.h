#include <iostream>
#include <fstream>
#include <vector>
#include "pont.h"
#include "Shape.h"

#ifndef SHAPE_COLLECTION_H
#define SHAPE_COLLECTION_H

class ShapeCollection{
private:
    std::vector<Shape*> shapes;

public:
    //Adding a new shape
    void addShape(Shape* shape) {
        shapes.push_back(shape);
    }

    std::vector<Shape*> getShapes() const {
        return shapes;
    }

    //Print shape that contains the given point (by the user)
    Shape* getShapeContainingPoint(Pont p) {
        for (const auto& shape : shapes) {
            if (shape->containsPoint(p)) {
                return shape;
            }
        }
        return nullptr;
    }

    //Print shape that is contained within the circle centered at the origin (adott sugarú, origó középpontú kör)
    std::vector<Shape*> getShapesContainingCircle(double radius) {
        std::vector<Shape*> result;
        for (const auto& shape : shapes) {
            if (shape->containsCircle(radius)) {
                result.push_back(shape);
            }
        }
        return result;
    }

    int getNumberOfShapes() const {
        return shapes.size();
    }

    void clean() {
        for (auto& shape : shapes) {
            delete shape;
        }
        shapes.clear();
    }

    ~ShapeCollection() {
        clean();
    }
};

#endif