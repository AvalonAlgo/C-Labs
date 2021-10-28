#include <stdexcept>
#include <boost/test/unit_test.hpp>

#include "Shape.hpp"

BOOST_AUTO_TEST_SUITE(ShapeTest)

const double EPSILON = 0.00001;

struct Fixture
{
  Shape falseTriangle{{1,1}, {1, 1}, {2, 3}};
  Shape trueTriangle{{1,1}, {1, 2}, { 2, 1}};

  Shape falseRectangle{{1,1}, {1, 1}, {1, 3}, {2, 3}};
  Shape trueRectangle{{1,1}, {2, 1}, {2, 3}, {1, 3}};

  Shape falseSquare{{1,1}, {1, 1}, {1, 2}, {2, 2}};
  Shape trueSquare{{1,1}, {2, 1}, {2, 2}, {1, 2}};

  Shape falsePentagon{{1,1}, {1, 1}, {1, 3}, {2, 3}, {3, 2}};
  Shape truePentagon{{1,1}, {2, 1}, {3, 2}, {2, 3}, {1, 3}};

  Point lhs{78978, 34253};
  Point rhs{78978, 34253};

  Point lhsf{78978, 0};
  Point rhsf{78978, 34253};
};

BOOST_FIXTURE_TEST_CASE(equality_sign_overload_test, Fixture)
{
  BOOST_CHECK_EQUAL((lhs == rhs), true);
  BOOST_CHECK_EQUAL((lhsf == rhsf), false);
}

BOOST_FIXTURE_TEST_CASE(is_triangle_test, Fixture)
{
  BOOST_CHECK_EQUAL(isTriangle(falseTriangle), false);
  BOOST_CHECK_EQUAL(isTriangle(trueTriangle), true);
}

BOOST_FIXTURE_TEST_CASE(is_rectangle_test, Fixture)
{
  BOOST_CHECK_EQUAL(isRectangle(falseRectangle), false);
  BOOST_CHECK_EQUAL(isRectangle(trueRectangle), true);

  BOOST_CHECK_EQUAL(isRectangle(falseSquare), false);
  BOOST_CHECK_EQUAL(isRectangle(trueSquare), true);
}

BOOST_FIXTURE_TEST_CASE(is_square_test, Fixture)
{
  BOOST_CHECK_EQUAL(isSquare(falseRectangle), false);
  BOOST_CHECK_EQUAL(isSquare(trueRectangle), false);

  BOOST_CHECK_EQUAL(isSquare(falseSquare), false);
  BOOST_CHECK_EQUAL(isSquare(trueSquare), true);
}

BOOST_FIXTURE_TEST_CASE(is_pentagon_test, Fixture)
{
  BOOST_CHECK_EQUAL(isPentagon(falsePentagon), false);
  BOOST_CHECK_EQUAL(isPentagon(truePentagon), true);
}

BOOST_FIXTURE_TEST_CASE(get_squared_distance_between_points_test, Fixture)
{
  double result = getSquaredDistanceBetweenPoints(lhsf, rhsf);

  const double horizontalDist =  lhsf.x - rhsf.x;
  const double verticalDist =  lhsf.y - rhsf.y;

  BOOST_CHECK_CLOSE(result, ((horizontalDist * horizontalDist) + (verticalDist * verticalDist)), EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()
