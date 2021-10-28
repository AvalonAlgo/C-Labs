#include <iostream>
#include <iterator>

#include "Shape.hpp"

bool operator==(const Point &lhs, const Point &rhs)
{
  if ((lhs.x == rhs.x) && (lhs.y == rhs.y))
  {
    return true;
  }

  return false;
}

std::istream& operator>>(std::istream& stream, Point& point)
{
  int x = 0, y = 0;
  std::istream::sentry sen(stream);
  if (!sen)
  {
    return stream;
  }
  stream >> std::ws;
  if (stream.get() != '(')
  {
    stream.setstate(std::ios_base::failbit);
    return stream;
  }
  if (!(stream >> std::ws >> x))
  {
    return stream;
  }
  if ((stream >> std::ws).get() != ';')
  {
    stream.setstate(std::ios_base::failbit);
    return stream;
  }
  if (!(stream >> std::ws >> y))
  {
    return stream;
  }
  if ((stream >> std::ws).get() != ')')
  {
    stream.setstate(std::ios_base::failbit);
    return stream;
  }
  point.x = x;
  point.y = y;

  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Point& point)
{
  std::ostream::sentry sen(stream);
  if (!sen)
  {
    return stream;
  }
  stream << '(' << point.x << ';' << point.y << ')';

  return stream;
}

std::istream& operator>>(std::istream& stream, Shape& shape)
{
  std::istream::sentry sen(stream);
  if (!sen)
  {
    return stream;
  }
  size_t vertices;
  stream >> std::noskipws >> std::ws >> vertices;
  if (!stream)
  {
    return stream;
  }
  Shape temp(vertices);
  for (size_t i = 0; i < vertices; ++i)
  {
    if (!(stream >> temp[i]))
    {
      return stream;
    }
  }
  shape = std::move(temp);
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Shape& shape)
{
  std::ostream::sentry sen(stream);
  if (!sen)
  {
    return stream;
  }
  stream << shape.size() << ' ';
  std::copy(shape.begin(), shape.end(), std::ostream_iterator<Point>(stream, " "));
  return stream;
}

bool isTriangle(const Shape& shape)
{
  if ((shape.size() != 3) ||
      (shape[0] == shape[1]) || (shape[0] == shape[2]) || (shape[1] == shape[2]))
  {
    return false;
  }

  return true;
}

bool isSquare(const Shape& shape)
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

bool isRectangle(const Shape& shape)
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

bool isPentagon(const Shape& shape)
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

bool CompareShapes::operator()(const Shape& first, const Shape& second) const
{
  if ((first.size() == 4) && (second.size() == 4))
  {
    return isSquare(first) && !isSquare(second);
  }
  return first.size() < second.size();
}

double getSquaredDistanceBetweenPoints(const Point& pointOne, const Point& pointTwo)
{
  const double horizontalDist =  pointOne.x - pointTwo.x;
  const double verticalDist =  pointOne.y - pointTwo.y;

  return ((horizontalDist * horizontalDist) + (verticalDist * verticalDist));
}
