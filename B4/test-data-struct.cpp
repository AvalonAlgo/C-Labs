#include <stdexcept>
#include <sstream>
#include <vector>

#include <boost/test/unit_test.hpp>

#include "DataStruct.hpp"

BOOST_AUTO_TEST_SUITE(test_data_struct)

struct fixture
{
    DataStruct d1{1, -3, "Mirkwood"};
    DataStruct d2{4, 3, "Lothlorien"};
    std::vector<DataStruct> arr{d1, d2};

    std::istringstream inStream;
    std::ostringstream outStream;
    std::ostringstream expectedOutput;
};

BOOST_AUTO_TEST_CASE(invalid_get_key)
{
  BOOST_CHECK_THROW(getKey(""), std::invalid_argument);
  BOOST_CHECK_THROW(getKey("INVALID"), std::invalid_argument);
  BOOST_CHECK_THROW(getKey("!1"), std::invalid_argument);
  BOOST_CHECK_THROW(getKey("135245"), std::out_of_range);
  BOOST_CHECK_THROW(getKey("-135245"), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(valid_get_key)
{
  for (int i = -5; i <= 5; i++)
  {
    BOOST_CHECK_NO_THROW(getKey(std::to_string(i)));
  }
}

BOOST_FIXTURE_TEST_CASE(correct_data_struct_vector_print, fixture)
{
  expectedOutput << "1,-3,Mirkwood\n4,3,Lothlorien\n";
  print(arr, outStream);

  BOOST_CHECK_EQUAL(outStream.str(), expectedOutput.str());
}

BOOST_FIXTURE_TEST_CASE(correct_data_struct_compare, fixture)
{
  expectedOutput << "1,-3,Mirkwood\n4,3,Lothlorien\n";
  std::sort(arr.begin(), arr.end(), dataStructCompare);
  print(arr, outStream);

  BOOST_CHECK_EQUAL(outStream.str(), expectedOutput.str());
}

BOOST_FIXTURE_TEST_CASE(correct_task_work, fixture)
{
  expectedOutput << "-3,-3,Silver\n-3,-3,Fist\n";
  inStream.str("-3,-3,Fist\n-3,-3,Silver\n");
  task(inStream, outStream);

  BOOST_CHECK_EQUAL(outStream.str(), "-3,-3,Fist\n-3,-3,Silver\n");
}

BOOST_AUTO_TEST_SUITE_END()
