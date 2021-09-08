#include <iostream>
#include <string>
#include <stdexcept>

#include <boost/test/unit_test.hpp>

#include "tasks.hpp"

BOOST_AUTO_TEST_SUITE(taskThree)

    struct fixture
    {
        const std::string input_one = "4 -2 6 7 -9 1 0\n";
        const std::string expected_output_one = "7 -9 1 \n";

        const std::string input_two = "4 -2 6 7 -9 2 0\n";
        const std::string expected_output_two = "4 -2 6 1 1 1 7 -9 1 1 1 2 \n";

        const std::string invalid_input_char = "4 -2 6 T -9 2 0\n";
        const std::string invalid_input_double = "4 -2 6 7.4 -9 2 0\n";

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

    BOOST_FIXTURE_TEST_CASE(correct_work_when_last_array_element_is_one, fixture)
    {
      inStream.str(input_one);

      task3();

      const std::string output = outStream.str();

      BOOST_CHECK_EQUAL(output, expected_output_one);
    }

    BOOST_FIXTURE_TEST_CASE(correct_work_when_last_array_element_is_two, fixture)
    {
      inStream.str(input_two);

      task3();

      const std::string output = outStream.str();

      BOOST_CHECK_EQUAL(output, expected_output_two);
    }

    BOOST_FIXTURE_TEST_CASE(incorrect_input_into_array_double, fixture)
    {
      inStream.str(invalid_input_double);

      BOOST_CHECK_THROW(task3(), std::runtime_error);
    }

    BOOST_FIXTURE_TEST_CASE(incorrect_input_into_array_char, fixture)
    {
      inStream.str(invalid_input_char);

      BOOST_CHECK_THROW(task3(), std::runtime_error);
    }

BOOST_AUTO_TEST_SUITE_END()
