#include <iostream>
#include <cassert>
#include <cmath>
#include "Shapes.h"
#include "Heterogen_kollekcio.h"
#include "Shape.h"

void testRectangleArea() {
    Rectangle rectangle(Pont(0, 0), Pont(4, 3));
    double actualArea = rectangle.calculateArea();
    double expectedArea = 12;
    if (actualArea == expectedArea) {
        std::cout << "Rectangle Area Test: PASSED\n" << std::endl;
    }
    else {
        std::cout << "Rectangle Area Test: FAILED" << std::endl;
        std::cout << "Expected Area: " << expectedArea << std::endl;
        std::cout << "Actual Area: " << actualArea << std::endl << std::endl;
    }
}

void testRectangleContainsPoint() {
    Rectangle rectangle(Pont(0, 0), Pont(4, 3));
    Pont point(2, 2);
    bool containsPoint = rectangle.containsPoint(point);
    if (containsPoint) {
        std::cout << "Rectangle Contains Point Test: PASSED\n" << std::endl;
    }
    else {
        std::cout << "Rectangle Contains Point Test: FAILED\n" << std::endl;
    }
}

void testRectangleContainsCircle() {
    Rectangle rectangle(Pont(0, 0), Pont(2, 2));
    double radius = 10;
    bool containsCircle = rectangle.containsCircle(radius);
    if (containsCircle) {
        std::cout << "Rectangle Contains Circle Test: PASSED\n" << std::endl;
    }
    else {
        std::cout << "Rectangle Contains Circle Test: FAILED" << std::endl;
        std::cout << "Rectangle is not completely inside the circle\n" << std::endl;
    }
}

void testTriangleArea() {
    Triangle triangle(Pont(0, 0), Pont(1, 4));
    
    double actualArea = triangle.calculateArea();
    double expectedArea = 22;
    if (round(actualArea) == expectedArea) {
        std::cout << "Triangle Area Test: PASSED\n" << std::endl;
    }
    else {
        std::cout << "Triangle Area Test: FAILED" << std::endl;
        std::cout << "Expected Area: " << expectedArea << std::endl;
        std::cout << "Actual Area: " << actualArea << std::endl << "\n";
    }
}

void testTriangleContainsPoint() {
    Triangle triangle(Pont(0, 0), Pont(0, 4));
    Pont point(-1, 1);
    bool containsPoint = triangle.containsPoint(point);
    if (containsPoint) {
        std::cout << "Triangle Contains Point Test: PASSED\n" << std::endl;
    }
    else {
        std::cout << "Triangle Contains Point Test: FAILED\n" << std::endl;
    }
}

void testTriangleContainsCircle() {
    Triangle triangle(Pont(0, 0), Pont(0, 4));
    double radius = 20.0;
    bool containsCircle = triangle.containsCircle(radius);
    if (containsCircle) {
        std::cout << "Triangle Contains Circle Test: PASSED\n" << std::endl;
    }
    else {
        std::cout << "Triangle Contains Circle Test: FAILED" << std::endl;
        std::cout << "Triangle is not completely inside the circle\n" << std::endl;
    }
}

void testCircleArea() {
    Circle circle(Pont(0, 0), Pont(0, 5));
    double actualArea = circle.calculateArea();
    double expectedArea = 78.5;
    if (actualArea == expectedArea) {
        std::cout << "Circle Area Test: PASSED\n" << std::endl;
    }
    else {
        std::cout << "Circle Area Test: FAILED" << std::endl;
        std::cout << "Expected Area: " << expectedArea << std::endl;
        std::cout << "Actual Area: " << actualArea << std::endl << "\n";
    }
}

void testCircleContainsPoint() {
    Circle circle(Pont(0, 0), Pont(3, 3));
    Pont point(2, 2);
    bool containsPoint = circle.containsPoint(point);
    if (containsPoint) {
        std::cout << "Circle Contains Point Test: PASSED\n" << std::endl;
    }
    else {
        std::cout << "Circle Contains Point Test: FAILED\n" << std::endl;
    }
}

void testAddShape() {
    ShapeCollection collection;

    Rectangle* rectangle = new Rectangle(Pont(0, 0), Pont(4, 3));
    Triangle* triangle = new Triangle(Pont(0, 0), Pont(3, 0));
    Circle* circle = new Circle(Pont(0, 0), 5);

    collection.addShape(rectangle);
    collection.addShape(triangle);
    collection.addShape(circle);

    int numberOfShapes = collection.getNumberOfShapes();
    if (numberOfShapes == 3) {
        std::cout << "Add Shape Test: PASSED\n" << std::endl;
    }
    else {
        std::cout << "Add Shape Test: FAILED" << std::endl;
        std::cout << "Expected Number of Shapes: 3" << std::endl;
        std::cout << "Actual Number of Shapes: " << numberOfShapes << std::endl << "\n";
    }

    collection.clean();
}

void testGetShapeContainingPoint() {
    ShapeCollection collection;

    Rectangle* rectangle = new Rectangle(Pont(0, 0), Pont(4, 3));
    Triangle* triangle = new Triangle(Pont(0, 0), Pont(3, 0));
    Circle* circle = new Circle(Pont(0, 0), 5);

    collection.addShape(rectangle);
    collection.addShape(triangle);
    collection.addShape(circle);
    Pont point(2, 3);

    Shape* containingShape = collection.getShapeContainingPoint(point);

    if (containingShape == rectangle) {
        std::cout << "Get Shape Containing Point Test: PASSED\n" << std::endl;
    }
    else {
        std::cout << "Get Shape Containing Point Test: FAILED\n" << std::endl;
    }

    collection.clean();
}

std::istream& operator>>(std::istream& input, Pont& point) {
    char delimiter;
    input >> delimiter >> point.x >> delimiter >> point.y >> delimiter;
    return input;
}

std::istream& operator>>(std::istream& input, Shape*& shape) {
    std::string shapeType;
    Pont center, vertex;

    if (input >> shapeType >> center >> vertex) {
        if (shapeType == "Triangle") {
            shape = new Triangle(center, vertex);
        }
        else if (shapeType == "Rectangle") {
            shape = new Rectangle(center, vertex);
        }
        else if (shapeType == "Circle") {
            shape = new Circle(center, vertex);
        }
        else {
            shape = nullptr;
        }
    }

    return input;
}

void testShapes(std::string filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Failed to open the file." << std::endl;
        return;
    }

    ShapeCollection collection;
    Shape* shape = nullptr;
    while (file >> shape) {
        if (shape != nullptr) {
            collection.addShape(shape);
        }
        else {
            std::cout << "Invalid shape format encountered." << std::endl;
        }
    }

    std::cout << "Size of the collection: " << collection.getNumberOfShapes() << std::endl;

    for (const auto& shape : collection.getShapes()) {
        shape->printData();
        cout << std::endl;
    }

    collection.clean();
}

int main() {
    //Testing functions of shapes.h
    testRectangleArea();
    testRectangleContainsPoint();
    testRectangleContainsCircle();
    testTriangleArea();
    testTriangleContainsPoint();
    testTriangleContainsCircle();
    testCircleArea();
    testCircleContainsPoint();

    //Heterogen kollekcio tests:
    testAddShape();
    testGetShapeContainingPoint();

    //Working with files:
    std::string filename = "shapes.txt";
    testShapes(filename);
    return 0;
}

