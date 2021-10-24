#include <stdexcept>
#include <boost/test/unit_test.hpp>

#include "Shape.hpp"

BOOST_AUTO_TEST_SUITE(InputOutputTest)

struct Fixture
{
  std::string expectedOutput;
  std::stringstream input;
  std::ostringstream output;
  Shape shape;
};

BOOST_FIXTURE_TEST_CASE(empty_point_input, Fixture)
{
  input.str("");

  BOOST_CHECK_THROW(readShape(shape, input), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(correct_point_input, Fixture)
{
  expectedOutput = "1 (1;2) \n";
  input.str("1 (1;2)");
  readShape(shape, input);
  printShape(shape, output);

  BOOST_CHECK_EQUAL(expectedOutput, output.str());
}

BOOST_FIXTURE_TEST_CASE(correct_points_input, Fixture)
{
  expectedOutput = "2 (1;2) (4;7) \n";
  input.str("2 (1;2) (4;7)");
  readShape(shape, input);
  printShape(shape, output);

  BOOST_CHECK_EQUAL(expectedOutput, output.str());
}

BOOST_FIXTURE_TEST_CASE(invalid_first_coordinate, Fixture)
{
  input.str("(INVALID;2)");

  BOOST_CHECK_THROW(readShape(shape, input), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(invalid_second_coordinate, Fixture)
{
  input.str("(2;INVALID)");

  BOOST_CHECK_THROW(readShape(shape, input), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(invalid_both_coordinates, Fixture)
{
  input.str("(INVALID;INVALID)");

  BOOST_CHECK_THROW(readShape(shape, input), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(no_opening_bracket, Fixture)
{
  input.str("1;2)");

  BOOST_CHECK_THROW(readShape(shape, input), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(no_closing_bracket, Fixture)
{
  input.str("(1;2");

  BOOST_CHECK_THROW(readShape(shape, input), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(no_delimeter, Fixture)
{
  input.str("(12)");

  BOOST_CHECK_THROW(readShape(shape, input), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(invalid_delimeter, Fixture)
{
  input.str("(1,2)");

  BOOST_CHECK_THROW(readShape(shape, input), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(point_output, Fixture)
{
  expectedOutput = "1 (1;2) \n";
  input.str("1 (1;2)");
  readShape(shape, input);
  printShape(shape, output);

  BOOST_CHECK_EQUAL(expectedOutput, output.str());
}

BOOST_AUTO_TEST_SUITE_END()
