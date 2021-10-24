#include <sstream>

#include <boost/test/unit_test.hpp>

#include "phonebook.hpp"

BOOST_AUTO_TEST_SUITE(phonebook)

struct Fixture
{
  Phonebook book;

  std::ostringstream output;
  std::ostringstream expectedOutput;
};

BOOST_FIXTURE_TEST_CASE(correct_insert_before, Fixture)
{
  expectedOutput << "456789797 Gandalf\n";
  book.push({"Mithrandir", "994865415348"});
  book.push({"Gandalf", "456789797"});
  book.insertBefore(book.end(), {"Olorin", "74512317"});
  book.showContact(std::next(book.begin()), output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(correct_insert_after, Fixture)
{
  expectedOutput << "74512317 Olorin\n";
  book.push({"Mithrandir", "994865415348"});
  book.push({"Gandalf", "456789797"});
  book.insertAfter(book.begin(), {"Olorin", "74512317"});
  book.showContact(std::next(book.begin()), output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(correct_work_erase, Fixture)
{
  expectedOutput << "994865415348 Mithrandir\n";
  book.push({"Mithrandir", "994865415348"});
  book.erase(book.begin());

  BOOST_CHECK_EQUAL(book.isEmpty(), true);
}

BOOST_FIXTURE_TEST_CASE(correct_work_push, Fixture)
{
  expectedOutput << "5426507574 deniz\n";
  book.push({"deniz", "5426507574"});
  book.showContact(book.begin(), output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(correct_work_is_empty, Fixture)
{
  BOOST_CHECK_EQUAL(book.isEmpty(), true);
}

BOOST_FIXTURE_TEST_CASE(correct_work_show_contact, Fixture)
{
  expectedOutput << "5426507574 deniz\n";
  book.push({"deniz", "5426507574"});
  book.showContact(book.begin(), output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_AUTO_TEST_SUITE_END()
