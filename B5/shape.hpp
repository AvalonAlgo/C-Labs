#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <vector>
#include <iostream>

struct Point
{
  int x, y;

  friend bool operator==(const Point &lhs, const Point &rhs);
  friend std::istream& operator>>(std::istream&, Point&);
  friend std::ostream& operator<<(std::ostream&, const Point&);
};

using Shape = std::vector<Point>;
std::istream& operator>>(std::istream&, Shape&);
std::ostream& operator<<(std::ostream&, const Shape&);

struct CompareShapes
{
  bool operator ()(const Shape&, const Shape&) const;
};

bool isTriangle(const Shape&);
bool isSquare(const Shape&);
bool isRectangle(const Shape&);
bool isPentagon(const Shape&);

double getSquaredDistanceBetweenPoints(const Point& pointOne, const Point& pointTwo);

#endif
