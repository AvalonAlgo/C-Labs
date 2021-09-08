#include <boost/test/unit_test.hpp>

#include <stdexcept>
#include <vector>

#include "task.hpp"

BOOST_AUTO_TEST_SUITE(test_data_struct)

struct fixture
{
  DataStruct d1{4, -3, "foo"};
  DataStruct d2{1, 3, "bar"};
  std::vector<DataStruct> arr{d1, d2};

  DataStruct d3 = {3, 4, "silver"};
  DataStruct d4 = {4, 4, "silver"};

  DataStruct d5 = {-3, -3, "fist"};
  DataStruct d6 = {-3, -3, "silver"};

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

BOOST_AUTO_TEST_CASE(invalid_key_parse)
{
  BOOST_CHECK_THROW(parseKey(""), std::invalid_argument);
  BOOST_CHECK_THROW(parseKey("135245"), std::out_of_range);
  BOOST_CHECK_THROW(parseKey("-99079872"), std::out_of_range);
}

BOOST_FIXTURE_TEST_CASE(correct_data_struct_vector_print, fixture)
{
  print(arr, outStream);

  const std::string output = outStream.str();

  BOOST_CHECK_EQUAL(output, "4,-3,foo\n1,3,bar\n");
}

/*BOOST_FIXTURE_TEST_CASE(correct_data_struct_compare, fixture)
{
  BOOST_CHECK(dataStructCompare(d1, d2));
  BOOST_CHECK(dataStructCompare(d3, d4));
  BOOST_CHECK(dataStructCompare(d5, d6));
}*/

BOOST_FIXTURE_TEST_CASE(correct_task_work, fixture)
{
  inStream.str("-3,-3,silver\n-3,-3,fist\n");

  task(inStream, outStream);

  const std::string output = outStream.str();

  BOOST_CHECK_EQUAL(output, "-3,-3,fist\n-3,-3,silver\n");
}

BOOST_AUTO_TEST_SUITE_END()
