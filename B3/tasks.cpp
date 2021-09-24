#include "tasks.hpp"
#include "phonebook-interface.hpp"
#include "factorial-container.hpp"
#include "parser.hpp"

#include <string>
#include <sstream>
#include <algorithm>
#include <cstring>

void doTaskOne(std::istream& in, std::ostream& out)
{
  PhonebookUI UI;
  std::string command;
  while (std::getline(in, command))
  {
    Command instruction = parse(command, UI);
    instruction(out, UI);
  }
}

void doTaskTwo(std::ostream& out)
{
  FactorialContainer array(10);

  std::copy(array.begin(), array.end(), std::ostream_iterator<size_t>(out, " "));
  out << "\n";

  std::reverse_copy(array.begin(), array.end(), std::ostream_iterator<size_t>(out, " "));
  out << "\n";
}
