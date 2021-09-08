#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

#include <boost/test/unit_test.hpp>

#include "tasks.hpp"

BOOST_AUTO_TEST_SUITE(taskFour)

    BOOST_AUTO_TEST_CASE(correct_ascending_sort)
    {
      std::ostringstream outStream;
      std::stringstream ss;
      std::string temp;
      int arraySize = 10;

      task4(arraySize, "ascending");

      ss << outStream.str();

      double found;
      std::vector<double> forSortCheck;

      while (std::getline(ss, temp, ' '))
      {
        if (std::stringstream(temp) >> found)
        {
          forSortCheck.push_back(found);
        }
      }

      BOOST_CHECK(std::is_sorted(forSortCheck.begin(), forSortCheck.end(), std::greater<>()));
    }

    BOOST_AUTO_TEST_CASE(correct_descending_sort)
    {
      std::ostringstream outStream;
      std::stringstream ss;
      std::string temp;
      int arraySize = 10;

      task4(arraySize, "descending");

      ss << outStream.str();

      double found;
      std::vector<double> forSortCheck;

      while (std::getline(ss, temp, ' '))
      {
        if (std::stringstream(temp) >> found)
        {
          forSortCheck.push_back(found);
        }
      }

      BOOST_CHECK(std::is_sorted(forSortCheck.begin(), forSortCheck.end(), std::greater<>()));
    }

    BOOST_AUTO_TEST_CASE(correct_range_of_randomly_generated_numbers)
    {
      int size = 10;

      std::vector<double> vector(size);
      fillRandom(vector.data(), size);

      for (int i = 0; i < size; i++)
      {
        BOOST_CHECK(vector[i] > -1 && vector[i] < 1);
      }
    }

    BOOST_AUTO_TEST_CASE(incorrect_sort_order)
    {
      BOOST_CHECK_THROW(task4(10, "I am a string"), std::invalid_argument);
      BOOST_CHECK_THROW(task4(10, nullptr), std::invalid_argument);
    }

    BOOST_AUTO_TEST_CASE(incorrect_array_size)
    {
      BOOST_CHECK_THROW(task4(0, "ascending"), std::invalid_argument);
      BOOST_CHECK_THROW(task4(0, "descending"), std::invalid_argument);

      BOOST_CHECK_THROW(task4(-10, "ascending"), std::invalid_argument);
      BOOST_CHECK_THROW(task4(-10, "descending"), std::invalid_argument);
    }

BOOST_AUTO_TEST_SUITE_END()
