#include <boost/test/unit_test.hpp>

#include "parser.hpp"

BOOST_AUTO_TEST_SUITE(parser)

struct Parser
{
    PhonebookUI UI;
    Command instruction;
    std::istringstream input;
    std::ostringstream output;
    std::ostringstream expectedOutput;
};

BOOST_FIXTURE_TEST_CASE (invalid_command, Parser)
{
  expectedOutput << "<INVALID COMMAND>\n";
  instruction = parse("I am an invalid command", UI);
  instruction(output, UI);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(add_with_missing_number, Parser)
{
  expectedOutput << "<INVALID COMMAND>\n";
  instruction = parse("add \"Mithrandir\"", UI);
  instruction(output, UI);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(add_with_missing_name, Parser)
{
  expectedOutput << "<INVALID COMMAND>\n";
  instruction = parse("add 54298456413", UI);
  instruction(output, UI);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(add_with_invalid_number, Parser)
{
  expectedOutput << "<INVALID COMMAND>\n";
  instruction = parse("add 54298INVALID \"Mithrandir\"", UI);
  instruction(output, UI);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(add_with_invalid_name, Parser)
{
  expectedOutput << "<INVALID COMMAND>\n";
  instruction = parse("add 54298456413 Mithrandir", UI);
  instruction(output, UI);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(add_correct_work, Parser)
{
  expectedOutput << "54298456413 Mithrandir\n";
  instruction = parse("add 54298456413 \"Mithrandir\"", UI);
  instruction(output, UI);
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(store_with_missing_mark_name, Parser)
{
  expectedOutput << "<INVALID COMMAND>\n";
  UI.add({"Mithrandir", "123"}, output);
  instruction = parse("store TheGrayWizard", UI);
  instruction(output, UI);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(store_with_missing_new_mark_name, Parser)
{
  expectedOutput << "<INVALID COMMAND>\n";
  UI.add({"Mithrandir", "123"}, output);
  instruction = parse("store current", UI);
  instruction(output, UI);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(store_with_invalid_mark_name, Parser)
{
  expectedOutput << "<INVALID COMMAND>\n";
  UI.add({"Mithrandir", "123"}, output);
  instruction = parse("store cur!rent TheGrayWizard", UI);
  instruction(output, UI);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(store_with_invalid_new_mark_name, Parser)
{
  expectedOutput << "<INVALID COMMAND>\n";
  UI.add({"Mithrandir", "123"}, output);
  instruction = parse("store current TheGray!Wizard", UI);
  instruction(output, UI);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(store_correct_work, Parser)
{
  expectedOutput << "123 Mithrandir\n";
  UI.add({"Mithrandir", "123"}, output);
  instruction = parse("store current TheGrayWizard", UI);
  instruction(output, UI);
  UI.show("TheGrayWizard", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(insert_with_missing_position, Parser)
{
  expectedOutput << "<INVALID COMMAND>\n";
  UI.add({"Mithrandir", "123"}, output);
  instruction = parse("insert current 321 \"Olorin\"", UI);
  instruction(output, UI);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(insert_with_missing_mark_name, Parser)
{
  expectedOutput << "<INVALID COMMAND>\n";
  UI.add({"Mithrandir", "123"}, output);
  instruction = parse("insert after 321 \"Olorin\"", UI);
  instruction(output, UI);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(insert_with_missing_number, Parser)
{
  expectedOutput << "<INVALID COMMAND>\n";
  UI.add({"Mithrandir", "123"}, output);
  instruction = parse("insert after current \"Olorin\"", UI);
  instruction(output, UI);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(insert_with_missing_name, Parser)
{
  expectedOutput << "<INVALID COMMAND>\n";
  UI.add({"Mithrandir", "123"}, output);
  instruction = parse("insert after current 321", UI);
  instruction(output, UI);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(insert_with_invalid_position, Parser)
{
  expectedOutput << "<INVALID COMMAND>\n";
  UI.add({"Mithrandir", "123"}, output);
  instruction = parse("insert SDFRGWSR current 321 \"Olorin\"", UI);
  instruction(output, UI);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(insert_with_invalid_mark_name, Parser)
{
  expectedOutput << "<INVALID COMMAND>\n";
  UI.add({"Mithrandir", "123"}, output);
  instruction = parse("insert after cur!rent 321 \"Olorin\"", UI);
  instruction(output, UI);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(insert_with_invalid_number, Parser)
{
  expectedOutput << "<INVALID COMMAND>\n";
  UI.add({"Mithrandir", "123"}, output);
  instruction = parse("insert after current 321INVALID \"Olorin\"", UI);
  instruction(output, UI);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(insert_with_invalid_name, Parser)
{
  expectedOutput << "<INVALID COMMAND>\n";
  UI.add({"Mithrandir", "123"}, output);
  instruction = parse("insert after current 321 Olorin", UI);
  instruction(output, UI);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(insert_correct_work, Parser)
{
  expectedOutput << "321 Olorin\n";
  UI.add({"Mithrandir", "123"}, output);
  instruction = parse("insert after current 321 \"Olorin\"", UI);
  instruction(output, UI);\
  UI.moveBySteps("current", 1, output);
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(delete_with_missing_mark_name, Parser)
{
  expectedOutput << "<INVALID COMMAND>\n";
  UI.add({"Mithrandir", "123"}, output);
  instruction = parse("delete", UI);
  instruction(output, UI);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(delete_with_invalid_mark_name, Parser)
{
  expectedOutput << "<INVALID BOOKMARK>\n";
  UI.add({"Mithrandir", "123"}, output);
  instruction = parse("delete InvalidMark", UI);
  instruction(output, UI);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(delete_empty_phone_book, Parser)
{
  expectedOutput << "<EMPTY>\n";
  instruction = parse("delete current", UI);
  instruction(output, UI);
  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(delete_correct_work, Parser)
{
  expectedOutput << "321 Olorin\n";
  UI.add({"Mithrandir", "123"}, output);
  UI.add({"Olorin", "321"}, output);
  instruction = parse("delete current", UI);
  instruction(output, UI);
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(show_missing_mark_name, Parser)
{
  expectedOutput << "<INVALID COMMAND>\n";
  instruction = parse("show", UI);
  instruction(output, UI);
  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(show_invalid_mark_name, Parser)
{
  expectedOutput << "<INVALID COMMAND>\n";
  instruction = parse("show cur!rent", UI);
  instruction(output, UI);
  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(show_empty_phone_book, Parser)
{
  expectedOutput << "<EMPTY>\n";
  instruction = parse("show current", UI);
  instruction(output, UI);
  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(show_correct_work, Parser)
{
  expectedOutput << "123 Mithrandir\n";
  UI.add({"Mithrandir", "123"}, output);
  instruction = parse("show current", UI);
  instruction(output, UI);
  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(move_with_invalid_mark_name, Parser)//////////
{
  expectedOutput << "<INVALID COMMAND>\n";
  UI.add({"Mithrandir", "123"}, output);
  UI.add({"Olorin", "321"}, output);
  UI.add({"Gandalf", "213"}, output);
  instruction = parse("move cur!rent 1", UI);
  instruction(output, UI);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(move_with_invalid_steps, Parser)
{
  expectedOutput << "<INVALID STEP>\n";
  UI.add({"Mithrandir", "123"}, output);
  UI.add({"Olorin", "321"}, output);
  UI.add({"Gandalf", "213"}, output);
  instruction = parse("move current 1INVALID", UI);
  instruction(output, UI);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(move_more_than_contacts_number_steps, Parser)
{
  expectedOutput << "213 Gandalf\n";
  UI.add({"Mithrandir", "123"}, output);
  UI.add({"Olorin", "321"}, output);
  UI.add({"Gandalf", "213"}, output);
  instruction = parse("move current 7969667", UI);
  instruction(output, UI);
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(move_more_than_contacts_number_steps_negative, Parser)
{
  expectedOutput << "123 Mithrandir\n";
  UI.add({"Mithrandir", "123"}, output);
  UI.add({"Olorin", "321"}, output);
  UI.add({"Gandalf", "213"}, output);
  UI.moveByPlace("current", "last", output);
  instruction = parse("move current -7969667", UI);
  instruction(output, UI);
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(move_correct_work_number_steps, Parser)
{
  expectedOutput << "321 Olorin\n";
  UI.add({"Mithrandir", "123"}, output);
  UI.add({"Olorin", "321"}, output);
  UI.add({"Gandalf", "213"}, output);
  instruction = parse("move current 1", UI);
  instruction(output, UI);
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(move_correct_work_place_steps_first, Parser)
{
  expectedOutput << "123 Mithrandir\n";
  UI.add({"Mithrandir", "123"}, output);
  UI.add({"Olorin", "321"}, output);
  UI.add({"Gandalf", "213"}, output);
  UI.moveByPlace("current", "last", output);
  instruction = parse("move current first", UI);
  instruction(output, UI);
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(move_correct_work_place_steps_last, Parser)
{
  expectedOutput << "213 Gandalf\n";
  UI.add({"Mithrandir", "123"}, output);
  UI.add({"Olorin", "321"}, output);
  UI.add({"Gandalf", "213"}, output);
  instruction = parse("move current last", UI);
  instruction(output, UI);
  UI.show("current", output);

  BOOST_CHECK_EQUAL(expectedOutput.str(), output.str());
}

BOOST_FIXTURE_TEST_CASE(parse_name_empty_name, Parser)
{
  std::string name;
  std::string test = "";
  input.str(test);
  bool isNameValid = readName(name, input);

  BOOST_CHECK_EQUAL(isNameValid, false);
}

BOOST_FIXTURE_TEST_CASE(parse_name_valid_name, Parser)
{
  std::string name;
  std::string test = "\"Mithrandir\"";
  input.str(test);
  bool isNameValid = readName(name, input);

  BOOST_CHECK_EQUAL(isNameValid, true);
}

BOOST_FIXTURE_TEST_CASE(check_mark_name_empty_mark_name, Parser)
{
  std::string markName;
  std::string test = "";
  input.str(test);
  bool isMarkNameValid = readMarkName(markName, input);

  BOOST_CHECK_EQUAL(isMarkNameValid, false);
}

BOOST_FIXTURE_TEST_CASE(check_mark_name_invalid_mark_name_plus, Parser)
{
  std::string markName;
  std::string test = "Mark+Name";
  input.str(test);
  bool isMarkNameValid = readMarkName(markName, input);

  BOOST_CHECK_EQUAL(isMarkNameValid, false);
}

BOOST_FIXTURE_TEST_CASE(check_mark_name_invalid_mark_name_illegal_symbol, Parser)
{
  std::string markName;
  std::string test = "Mark!Name";
  input.str(test);
  bool isMarkNameValid = readMarkName(markName, input);

  BOOST_CHECK_EQUAL(isMarkNameValid, false);
}

BOOST_FIXTURE_TEST_CASE(check_mark_name_valid_mark_name_minus, Parser)
{
  std::string markName;
  std::string test = "Mark-Name";
  input.str(test);
  bool isMarkNameValid = readMarkName(markName, input);

  BOOST_CHECK_EQUAL(isMarkNameValid, true);
}

BOOST_FIXTURE_TEST_CASE(check_mark_name_valid_mark_name_all_alpha, Parser)
{
  std::string markName;
  std::string test = "MarkName";
  input.str(test);
  bool isMarkNameValid = readMarkName(markName, input);

  BOOST_CHECK_EQUAL(isMarkNameValid, true);
}

BOOST_FIXTURE_TEST_CASE(check_mark_name_valid_mark_name_with_num, Parser)
{
  std::string markName;
  std::string test = "Mark87Name";
  input.str(test);
  bool isMarkNameValid = readMarkName(markName, input);

  BOOST_CHECK_EQUAL(isMarkNameValid, true);
}

BOOST_FIXTURE_TEST_CASE(check_number_empty_number, Parser)
{
  std::string number;
  std::string test = "";
  input.str(test);
  bool isNumberValid = readNumber(number, input);

  BOOST_CHECK_EQUAL(isNumberValid, false);
}

BOOST_FIXTURE_TEST_CASE(check_number_invalid_number, Parser)
{
  std::string number;
  std::string test = "T5T6";
  input.str(test);
  bool isNumberValid = readNumber(number, input);

  BOOST_CHECK_EQUAL(isNumberValid, false);
}

BOOST_FIXTURE_TEST_CASE(check_number_number_with_plus, Parser)
{
  std::string number;
  std::string test = "+5";
  input.str(test);
  bool isNumberValid = readNumber(number, input);

  BOOST_CHECK_EQUAL(isNumberValid, true);
}

BOOST_FIXTURE_TEST_CASE(check_number_number_with_minus, Parser)
{
  std::string number;
  std::string test = "-5";
  input.str(test);
  bool isNumberValid = readNumber(number, input);

  BOOST_CHECK_EQUAL(isNumberValid, true);
}

BOOST_AUTO_TEST_SUITE_END()
