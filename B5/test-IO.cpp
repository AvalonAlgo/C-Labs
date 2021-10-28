#include <stdexcept>
#include <boost/test/unit_test.hpp>

#include "Shape.hpp"

BOOST_AUTO_TEST_SUITE(IOTest)

struct Fixture
{
  std::string expectedOutput;
  std::stringstream input;
  std::ostringstream output;
  Shape shape;
  Point point;
};

BOOST_FIXTURE_TEST_CASE(empty_point_input, Fixture)
{
  input.str("");
  input >> point;

  BOOST_CHECK(input.fail());
}

BOOST_FIXTURE_TEST_CASE(correct_point_input, Fixture)
{
  expectedOutput = "1 (1;2) ";
  input.str("1 (1;2)");
  input >> shape;
  output << shape;

  BOOST_CHECK_EQUAL(expectedOutput, output.str());
}

BOOST_FIXTURE_TEST_CASE(correct_points_input, Fixture)
{
  expectedOutput = "2 (1;2) (4;7) ";
  input.str("2 (1;2) (4;7)");
  input >> shape;
  output << shape;

  BOOST_CHECK_EQUAL(expectedOutput, output.str());
}

BOOST_FIXTURE_TEST_CASE(invalid_first_coordinate, Fixture)
{
  input.str("(INVALID;2)");
  input >> point;

  BOOST_CHECK(input.fail());
}

BOOST_FIXTURE_TEST_CASE(invalid_second_coordinate, Fixture)
{
  input.str("(2;INVALID)");
  input >> point;

  BOOST_CHECK(input.fail());
}

BOOST_FIXTURE_TEST_CASE(invalid_both_coordinates, Fixture)
{
  input.str("(INVALID;INVALID)");
  input >> point;

  BOOST_CHECK(input.fail());
}

BOOST_FIXTURE_TEST_CASE(no_opening_bracket, Fixture)
{
  input.str("1;2)");
  input >> point;

  BOOST_CHECK(input.fail());
}

BOOST_FIXTURE_TEST_CASE(no_closing_bracket, Fixture)
{
  input.str("(1;2");
  input >> point;

  BOOST_CHECK(input.fail());
}

BOOST_FIXTURE_TEST_CASE(no_delimeter, Fixture)
{
  input.str("(12)");
  input >> point;

  BOOST_CHECK(input.fail());
}

BOOST_FIXTURE_TEST_CASE(invalid_delimeter, Fixture)
{
  input.str("(1,2)");
  input >> point;

  BOOST_CHECK(input.fail());
}

BOOST_FIXTURE_TEST_CASE(point_output, Fixture)
{
  expectedOutput = "1 (1;2) ";
  input.str("1 (1;2)");
  input >> shape;
  output << shape;

  BOOST_CHECK_EQUAL(expectedOutput, output.str());
}

BOOST_AUTO_TEST_SUITE_END()
