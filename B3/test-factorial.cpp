#include <boost/test/unit_test.hpp>
#include <sstream>

#include "factorial-container.hpp"

BOOST_AUTO_TEST_SUITE(factorial_container)

BOOST_AUTO_TEST_CASE(empty_full_factorial_container)
{
  FactorialContainer forEmptyTest(0);
  BOOST_CHECK(forEmptyTest.begin() == forEmptyTest.end());

  FactorialContainer forEmptyTestTwo(10);
  BOOST_CHECK(forEmptyTestTwo.begin() != forEmptyTestTwo.end());
}

BOOST_AUTO_TEST_CASE(correct_straight_output)
{
  const std::string correctStraightOutput = "1 2 6 24 120 720 5040 40320 362880 3628800 ";
  std::ostringstream out;

  FactorialContainer forStraightOutputTest(10);

  std::copy(forStraightOutputTest.begin(), forStraightOutputTest.end(), std::ostream_iterator<size_t>(out, " "));
  BOOST_CHECK(correctStraightOutput == out.str());}

BOOST_AUTO_TEST_CASE(correct_reverse_output)
{
  const std::string correctReverseOutput = "3628800 362880 40320 5040 720 120 24 6 2 1 ";
  std::ostringstream out;

  FactorialContainer forReverseOutputTest(10);

  std::reverse_copy(forReverseOutputTest.begin(), forReverseOutputTest.end(), std::ostream_iterator<size_t>(out, " "));
  BOOST_CHECK(correctReverseOutput == out.str());
}

BOOST_AUTO_TEST_SUITE_END()
