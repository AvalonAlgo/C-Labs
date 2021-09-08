#include <iostream>
#include <sstream>
#include <algorithm>
#include <list>
#include "string"

#include "shape.hpp"

const int typesOfShapes = 3;

void readShape(std::stringstream &input, Shape &shape)
{
  size_t count_points;
  Point tempPoint;
  char tempCharacter;

  input >> std::ws >> count_points;
  while ((input >> std::ws >> tempCharacter))
  {
    if (tempCharacter != '(')
    {
      throw std::invalid_argument("Invalid input (expected \"(\" )");
    }

    input >> std::ws >> tempPoint.x;
    input >> std::ws >> tempCharacter;
    if (tempCharacter != ';')
    {
      throw std::invalid_argument("Invalid input (expected \";\" )");
    }

    input >> std::ws >> tempPoint.y;
    input >> std::ws >> tempCharacter;
    if (tempCharacter != ')')
    {
      throw std::invalid_argument("Invalid input (expected \")\" )");
    }

    shape.push_back({tempPoint.x, tempPoint.y});
  }

  if (count_points != shape.size())
  {
    throw std::invalid_argument("Invalid number of points provided");
  }
}

bool isSquare(const Shape &shape)
{
  if (shape.size() != 4)
  {
    return false;
  }

  if (shape[1].x != shape[0].x)
  {
    if (std::abs(shape[1].x - shape[0].x) != std::abs(shape[2].y - shape[1].y))
    {
      return false;
    }
  }
  else
  {
    if (std::abs(shape[2].x - shape[1].x) != std::abs(shape[1].y - shape[0].y))
    {
      return false;
    }
  }

  return true;
}

bool compareShape(const Shape &lhs, const Shape &rhs)
{
  if (lhs.size() < rhs.size())
  {
    return true;
  }

  if (lhs.size() == 4 && rhs.size() == 4)
  {
    if (isSquare(lhs))
    {
      if (isSquare(rhs))
      {
        return false;
      }
      else
      {
        return true;
      }
    }
  }

  return false;
}

void printShape(const Shape &shape)
{
  std::cout << shape.size() << " - ";
  for (auto point : shape)
  {
    std::cout << "(" << point.x << ";" << point.y << ")" << " ";
  }
  std::cout << std::endl;
}

void task2()
{
  std::list<Shape> shapes;
  size_t verticesCounters[typesOfShapes]{0, 0, 0};

  // 1
  Shape temp;
  std::string input;
  while (std::getline(std::cin >> std::ws, input))
  {
    std::stringstream inputStream(input);
    readShape(inputStream, temp);
    if (!temp.empty())
    {
      shapes.push_back(temp);
    }
    temp.clear();
  }

  // 2
  size_t vertices = 0;
  for (Shape shape : shapes)
  {
    vertices += shape.size();
  }

  // 3
  for (Shape shape : shapes)
  {
    if (shape.size() == 3)
    {
      ++verticesCounters[0];
    }
    else if (shape.size() == 4)
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
    if (shape->size() == 5)
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
  std::cout << "Vertices: " << vertices << std::endl
            << "Triangles: " << verticesCounters[0] << std::endl
            << "Squares: " << verticesCounters[1] << std::endl
            << "Rectangles: " << verticesCounters[2] << std::endl;

  std::cout << "Points: ";
  for (Point point : points)
  {
    std::cout << "(" << point.x << ";" << point.y << ")" << " ";
  }
  std::cout << std::endl;

  std::cout << "Shapes:" << std::endl;
  for (Shape shape : shapes)
  {
    printShape(shape);
  }
}
