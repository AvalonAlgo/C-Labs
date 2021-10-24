#include <iostream>
#include <sstream>
#include <algorithm>
#include <list>
#include "string"

#include "Shape.hpp"

const int typesOfShapes = 3;

void taskTwo(std::istream& in, std::ostream& out)
{
  std::list<Shape> shapes;
  size_t verticesCounters[typesOfShapes]{0, 0, 0};

  // 1
  Shape temp;
  std::string input;
  while (std::getline(in >> std::ws, input))
  {
    std::stringstream inputStream(input);
    readShape(temp, inputStream);
    if (!temp.empty())
    {
      shapes.push_back(temp);
    }
    temp.clear();
  }

  // 2
  size_t vertices = 0;
  for (const Shape& shape : shapes)
  {
    vertices += shape.size();
  }

  // 3
  for (const Shape& shape : shapes)
  {
    if (isTriangle(shape))
    {
      ++verticesCounters[0];
    }
    else if (isRectangle(shape))
    {
      if (isSquare(shape))
      {
        ++verticesCounters[1];
      }
      ++verticesCounters[2];
    }
  }

  // 4
  for (auto shape = shapes.begin(); shape != shapes.end();)
  {
    if (isPentagon(*shape))
    {
      shape = shapes.erase(shape);
    }
    else
    {
      ++shape;
    }
  }

  // 5
  std::vector<Point> points;
  for (auto shape : shapes)
  {
    points.push_back(shape[0]);
  }

  // 6
  shapes.sort(compareShape);

  // 7
  out << "Vertices: " << vertices << "\n"
      << "Triangles: " << verticesCounters[0] << "\n"
      << "Squares: " << verticesCounters[1] << "\n"
      << "Rectangles: " << verticesCounters[2] << "\n";

  out << "Points: ";
  for (Point point : points)
  {
    out << "(" << point.x << ";" << point.y << ")" << " ";
  }
  out << "\n";

  out << "Shapes:" << "\n";
  for (const Shape& shape : shapes)
  {
    printShape(shape, out);
  }
}
