#include <iostream>

#include "Shape.hpp"

bool operator==(const Point &lhs, const Point &rhs) //
{
  if ((lhs.x == rhs.x) && (lhs.y == rhs.y))
  {
    return true;
  }

  return false;
}

void readShape(Shape &shape, std::stringstream &input)  //
{
  size_t count_points;
  Point tempPoint{0, 0};
  char tempCharacter;

  if (!(input >> std::ws >> count_points))
  {
    throw std::invalid_argument("Point count not specified");
  }
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

void printShape(const Shape &shape, std::ostream& out)  //
{
  out << shape.size() << " ";
  for (auto point : shape)
  {
    out << "(" << point.x << ";" << point.y << ")" << " ";
  }
  out << "\n";
}

bool compareShape(const Shape &lhs, const Shape &rhs)
{
  if (lhs.size() < rhs.size())
  {
    return true;
  }

  if ((lhs.size() == 4) && (rhs.size() == 4))
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

bool isTriangle(const Shape& shape) //
{
  if ((shape.size() != 3) ||
      (shape[0] == shape[1]) || (shape[0] == shape[2]) || (shape[1] == shape[2]))
  {
    return false;
  }

  return true;
}

bool isRectangle(const Shape& shape)  //
{
  if ((shape.size() != 4) ||
      (shape[0] == shape[1]) || (shape[0] == shape[2]) || (shape[0] == shape[3]) ||
      (shape[1] == shape[2]) || (shape[1] == shape[3]) ||
      (shape[2] == shape[3]))
  {
    return false;
  }

  const double sideAB =  getSquaredDistanceBetweenPoints(shape[0], shape[1]);
  const double sideBC =  getSquaredDistanceBetweenPoints(shape[1], shape[2]);
  const double sideCD =  getSquaredDistanceBetweenPoints(shape[2], shape[3]);
  const double sideDA =  getSquaredDistanceBetweenPoints(shape[3], shape[0]);

  return ((sideAB == sideCD) && (sideBC == sideDA));
}

bool isSquare(const Shape& shape) //
{
  if ((shape.size() != 4) ||
      (shape[0] == shape[1]) || (shape[0] == shape[2]) || (shape[0] == shape[3]) ||
      (shape[1] == shape[2]) || (shape[1] == shape[3]) ||
      (shape[2] == shape[3]))
  {
    return false;
  }

  const double sideAB =  getSquaredDistanceBetweenPoints(shape[0], shape[1]);
  const double sideBC =  getSquaredDistanceBetweenPoints(shape[1], shape[2]);
  const double sideCD =  getSquaredDistanceBetweenPoints(shape[2], shape[3]);
  const double sideDA =  getSquaredDistanceBetweenPoints(shape[3], shape[0]);


  return ((sideAB == sideBC) && (sideCD == sideDA));
}

bool isPentagon(const Shape& shape) //
{
  if ((shape.size() != 5) ||
      (shape[0] == shape[1]) || (shape[0] == shape[2]) || (shape[0] == shape[3]) || (shape[0] == shape[4]) ||
      (shape[1] == shape[2]) || (shape[1] == shape[3]) || (shape[1] == shape[4]) ||
      (shape[2] == shape[3]) || (shape[2] == shape[4]) ||
      (shape[3] == shape[4]))
  {
    return false;
  }

  return true;
}

double getSquaredDistanceBetweenPoints(const Point& pointOne, const Point& pointTwo)  //
{
  const double horizontalDist =  pointOne.x - pointTwo.x;
  const double verticalDist =  pointOne.y - pointTwo.y;

  return ((horizontalDist * horizontalDist) + (verticalDist * verticalDist));
}
