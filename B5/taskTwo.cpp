#include <iostream>
#include <sstream>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <vector>
#include <list>

#include "Shape.hpp"

void taskTwo(std::istream& in, std::ostream& out)
{
  std::list<Shape> shapes((std::istream_iterator<Shape>(in)), std::istream_iterator<Shape>());
  if (!in.eof())
  {
    throw std::runtime_error("Error in shape input");
  }

  size_t vertices = 0;
  std::for_each(shapes.begin(), shapes.end(),
                [&vertices](const Shape& shape)
                {
                    vertices += shape.size();
                });

  const size_t triangles = std::count_if(shapes.begin(), shapes.end(), &isTriangle);
  const size_t squares = std::count_if(shapes.begin(), shapes.end(), &isSquare);
  const size_t rectangles = std::count_if(shapes.begin(), shapes.end(), &isRectangle);
  shapes.erase(std::remove_if(shapes.begin(), shapes.end(), isPentagon), shapes.end());

  std::vector<Point> points;
  points.reserve(shapes.size());
  std::for_each(shapes.begin(), shapes.end(),
                [&points](const Shape& shape)
                {
                    points.push_back(shape[0]);
                });
  shapes.sort(CompareShapes());

  out << "Vertices: " << vertices
      << "\nTriangles: " << triangles
      << "\nSquares: " << squares
      << "\nRectangles: " << rectangles
      << "\nPoints: ";
  std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(out, " "));

  out << "\nShapes:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape>(out, "\n"));
}
