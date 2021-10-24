#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <vector>
#include <sstream>

struct Point
{
    int x, y;

    friend bool operator== (const Point &lhs, const Point &rhs);
};

using Shape = std::vector<Point>;

void readShape(Shape &shape, std::stringstream &input);
void printShape(const Shape &shape, std::ostream& out);

bool compareShape(const Shape &lhs, const Shape &rhs);
bool isTriangle(const Shape& shape);
bool isRectangle(const Shape& shape);
bool isSquare(const Shape& shape);
bool isPentagon(const Shape& shape);

double getSquaredDistanceBetweenPoints(const Point& pointOne, const Point& pointTwo);

#endif
