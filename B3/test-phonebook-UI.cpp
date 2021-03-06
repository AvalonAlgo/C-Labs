#include <sstream>

#include <boost/test/unit_test.hpp>

#include "phonebook-interface.hpp"

BOOST_AUTO_TEST_SUITE(phonebook_user_interface)

struct Fixture
{
  PhonebookUI UI;

  std::ostringstream output;
  std::ostringstream expectedOutput;
};

BOOST_FIXTURE_TEST_CASE(correct_add_interface, Fixture)
{
  expectedOutput << "5426507574 deniz\n";

  UI.add({"deniz", "5426507574"}, output);
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(correct_store_interface, Fixture)
{
  expectedOutput << "5426507574 deniz\n";

  UI.add({"onur", "947682513"}, output);
  UI.add({"deniz", "5426507574"}, output);
  UI.moveBySteps("current", 1, output);
  UI.store("current", "test", output);
  UI.show("test", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(store_invalid_mark, Fixture)
{
  expectedOutput << "<INVALID BOOKMARK>\n";

  UI.add({"onur", "947682513"}, output);
  UI.store("INVALID", "AAAAAAAA", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(store_empty_book, Fixture)
{
  expectedOutput << "<EMPTY>\n";

  UI.store("current", "AAAAAAAA", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(insert_invalid_mark, Fixture)
{
  expectedOutput << "<INVALID BOOKMARK>\n";

  UI.add({"onur", "947682513"}, output);
  UI.insert("INVALID", PhonebookUI::BEFORE, {"deniz", "5426507574"}, output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(correct_insert_before_interface, Fixture)
{
  expectedOutput << "5426507574 deniz\n";

  UI.add({"onur", "947682513"}, output);
  UI.insert("current", PhonebookUI::BEFORE, {"deniz", "5426507574"}, output);
  UI.moveBySteps("current", -1, output);
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(correct_insert_after_interface, Fixture)
{
  expectedOutput << "5426507574 deniz\n";

  UI.add({"onur", "947682513"}, output);
  UI.insert("current", PhonebookUI::AFTER, {"deniz", "5426507574"}, output);
  UI.moveBySteps("current", 1, output);
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(delete_invalid_mark, Fixture)
{
  expectedOutput << "<INVALID BOOKMARK>\n";

  UI.add({"onur", "947682513"}, output);
  UI.deleteContact("INVALID", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(delete_empty_book, Fixture)
{
  expectedOutput << "<EMPTY>\n";

  UI.deleteContact("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(correct_delete_contact_interface, Fixture)
{
  expectedOutput << "5426507574 deniz\n";

  UI.add({"onur", "947682513"}, output);
  UI.add({"deniz", "5426507574"}, output);
  UI.deleteContact("current", output);
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(correct_show_interface_interface, Fixture)
{
  expectedOutput << "5426507574 deniz\n";

  UI.add({"deniz", "5426507574"}, output);
  UI.add({"onur", "947682513"}, output);
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(show_bookmark_error_interface, Fixture)
{
  expectedOutput << "<INVALID BOOKMARK>\n";

  UI.add({"deniz", "5426507574"}, output);
  UI.show("test", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(show_empty_error_interface, Fixture)
{
  expectedOutput << "<EMPTY>\n";

  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(correct_move_positive_step_interface, Fixture)
{
  expectedOutput << "947682513 onur\n";

  UI.add({"deniz", "5426507574"}, output);
  UI.add({"onur", "947682513"}, output);
  UI.moveBySteps("current", 1, output);
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(correct_move_negative_step_interface, Fixture)
{
  expectedOutput << "5426507574 deniz\n";

  UI.add({"deniz", "5426507574"}, output);
  UI.add({"onur", "947682513"}, output);
  UI.moveBySteps("current", 1, output);
  UI.moveBySteps("current", -1, output);
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(move_step_empty_error_interface, Fixture)
{
  expectedOutput << "<EMPTY>\n";

  UI.moveBySteps("current", 1, output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(move_step_bookmark_error_interface, Fixture)
{
  expectedOutput << "<INVALID BOOKMARK>\n";

  UI.add({"deniz", "5426507574"}, output);
  UI.moveBySteps("test", 0, output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(correct_move_position_last_interface, Fixture)
{
  expectedOutput << "9618318645 gandalf\n";

  UI.add({"deniz", "5426507574"}, output);
  UI.add({"onur", "947682513"}, output);
  UI.add({"olorin", "2316183517"}, output);
  UI.add({"mithrandir", "1368186877"}, output);
  UI.add({"gandalf", "9618318645"}, output);
  UI.moveByPlace("current", "last", output);
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(correct_move_position_first_interface, Fixture)
{
  expectedOutput << "5426507574 deniz\n";

  UI.add({"deniz", "5426507574"} ,output);
  UI.add({"onur", "947682513"} ,output);
  UI.add({"olorin", "2316183517"} ,output);
  UI.add({"mithrandir", "1368186877"} ,output);
  UI.add({"gandalf", "9618318645"} ,output);
  UI.moveBySteps("current", 4, output);
  UI.moveByPlace("current", "first", output);
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_AUTO_TEST_SUITE_END()
