#include <boost/test/unit_test.hpp>
#include <sstream>

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

  UI.add({"deniz", "5426507574"});
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(correct_store_interface, Fixture)
{
  expectedOutput << "5426507574 deniz\n";

  UI.add({"onur", "947682513"});
  UI.add({"deniz", "5426507574"});
  UI.move("current", 1, output);
  UI.store("current", "test", output);
  UI.show("test", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(correct_insert_before_interface, Fixture)
{
  expectedOutput << "5426507574 deniz\n";

  UI.add({"onur", "947682513"});
  UI.insert("current", "before", {"deniz", "5426507574"}, output);
  UI.move("current", -1, output);
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(correct_insert_after_interface, Fixture)
{
  expectedOutput << "5426507574 deniz\n";

  UI.add({"onur", "947682513"});
  UI.insert("current", "after", {"deniz", "5426507574"}, output);
  UI.move("current", 1, output);
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(correct_delete_contact_interface, Fixture)
{
  expectedOutput << "5426507574 deniz\n";

  UI.add({"onur", "947682513"});
  UI.add({"deniz", "5426507574"});
  UI.deleteContact("current", output);
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(correct_show_interface_interface, Fixture)
{
  expectedOutput << "5426507574 deniz\n";

  UI.add({"deniz", "5426507574"});
  UI.add({"onur", "947682513"});
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(show_bookmark_error_interface, Fixture)
{
  expectedOutput << "<INVALID BOOKMARK>\n";

  UI.add({"deniz", "5426507574"});
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

  UI.add({"deniz", "5426507574"});
  UI.add({"onur", "947682513"});
  UI.move("current", 1, output);
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(correct_move_negative_step_interface, Fixture)
{
  expectedOutput << "5426507574 deniz\n";

  UI.add({"deniz", "5426507574"});
  UI.add({"onur", "947682513"});
  UI.move("current", 1, output);
  UI.move("current", -1, output);
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(move_step_empty_error_interface, Fixture)
{
  expectedOutput << "<EMPTY>\n";

  UI.move("current", 1, output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(move_step_bookmark_error_interface, Fixture)
{
  expectedOutput << "<INVALID BOOKMARK>\n";

  UI.add({"deniz", "5426507574"});
  UI.move("test", 0, output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(correct_move_position_last_interface, Fixture)
{
  expectedOutput << "9618318645 gandalf\n";

  UI.add({"deniz", "5426507574"});
  UI.add({"onur", "947682513"});
  UI.add({"olorin", "2316183517"});
  UI.add({"mithrandir", "1368186877"});
  UI.add({"gandalf", "9618318645"});
  UI.move("current", "last", output);
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(correct_move_position_first_interface, Fixture)
{
  expectedOutput << "5426507574 deniz\n";

  UI.add({"deniz", "5426507574"});
  UI.add({"onur", "947682513"});
  UI.add({"olorin", "2316183517"});
  UI.add({"mithrandir", "1368186877"});
  UI.add({"gandalf", "9618318645"});
  UI.move("current", 4, output);
  UI.move("current", "first", output);
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_AUTO_TEST_SUITE_END()
