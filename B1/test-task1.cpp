#include <iostream>
#include <string>
#include <stdexcept>

#include <boost/test/unit_test.hpp>

#include "tasks.hpp"

BOOST_AUTO_TEST_SUITE(taskOne)

    struct fixture
    {
        const std::string input = "4 -2 6 7 -9 1\n";

        const std::string expected_output_ascending = "-9 -2 1 4 6 7 \n-9 -2 1 4 6 7 \n-9 -2 1 4 6 7 \n";
        const std::string expected_output_descending = "7 6 4 1 -2 -9 \n7 6 4 1 -2 -9 \n7 6 4 1 -2 -9 \n";

        const std::string invalid_input_char = "4 -2 6 T -9 2\n";
        const std::string invalid_input_double = "4 -2 6 7.4 -9 2\n";

        std::streambuf* backupCin;
        std::streambuf* backupCout;
        std::istringstream inStream;
        std::ostringstream outStream;

        fixture() :
                backupCin(std::cin.rdbuf(inStream.rdbuf())),
                backupCout(std::cout.rdbuf(outStream.rdbuf()))
        {}

        ~fixture()
        {
          std::cin.rdbuf(backupCin);
          std::cout.rdbuf(backupCout);
        }
    };

    BOOST_FIXTURE_TEST_CASE(incorrect_sort_order, fixture)
    {
      BOOST_CHECK_THROW(task1("I am a string"), std::invalid_argument);
      BOOST_CHECK_THROW(task1(nullptr), std::invalid_argument);
    }

    BOOST_FIXTURE_TEST_CASE(correct_ascending_sort, fixture)
    {
      inStream.str(input);

      task1("ascending");

      const std::string output = outStream.str();

      BOOST_CHECK_EQUAL(output, expected_output_ascending);
    }

    BOOST_FIXTURE_TEST_CASE(correct_descending_sort, fixture)
    {
      inStream.str(input);

      task1("descending");

      const std::string output = outStream.str();

      BOOST_CHECK_EQUAL(output, expected_output_descending);
    }

    BOOST_FIXTURE_TEST_CASE(incorrect_input_into_array_double, fixture)
    {
      inStream.str(invalid_input_double);

      BOOST_CHECK_THROW(task1("ascending"), std::runtime_error);
      BOOST_CHECK_THROW(task1("descending"), std::runtime_error);
    }

    BOOST_FIXTURE_TEST_CASE(incorrect_input_into_array_char, fixture)
    {
      inStream.str(invalid_input_char);

      BOOST_CHECK_THROW(task1("ascending"), std::runtime_error);
      BOOST_CHECK_THROW(task1("descending"), std::runtime_error);
    }

BOOST_AUTO_TEST_SUITE_END()
