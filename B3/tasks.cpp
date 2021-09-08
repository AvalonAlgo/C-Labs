#include "tasks.hpp"
#include "phonebook-interface.hpp"
#include "factorial-container.hpp"

#include <string>
#include <sstream>
#include <algorithm>
#include <cstring>

std::string parseName(std::string &name)
{
  if (*name.begin() == '\"' && *std::prev(name.end()) == '\"')
  {
    name.erase(name.begin());
    name.erase(std::prev(name.end()));

    for (auto i = name.begin(); i != name.end(); ++i)
    {
      if (*i == '\\')
      {
        if (*std::next(i) == '\"')
        {
          name.erase(i);
        }
        else
        {
          throw std::invalid_argument("Invalid name in parser");
        }
      }
    }

    return name;
  }
  else
  {
    return name;
  }
}

bool checkNumber(std::string &number)
{
  auto it = number.begin();
  if (*it == '-')
  {
    ++it;
  }
  while (it != number.end())
  {
    if (!std::isdigit(*it))
    {
      return false;
    }
    ++it;
  }

  return true;
}

void doTaskOne(std::istream& in, std::ostream& out)
{
  PhonebookUI UI;
  std::string input;
  std::string command;

  while (std::getline(std::cin >> std::ws, input))
  {
    std::stringstream inputStream(input);
    inputStream >> command;

    if (command == "add")
    {
      std::string name;
      std::string number;

      inputStream >> number;
      inputStream >> std::ws;
      std::getline(inputStream, name);

      if (name.empty() || number.empty())
      {
        throw std::invalid_argument("Empty add contact parameters");
      }
      else if (checkNumber(number))
      {
        name = parseName(name);
        UI.add({name, number});
      }
      else
      {
        throw std::invalid_argument("Invalid add contact number");
      }
    }
    else if (command == "store")
    {
      std::string markName;
      std::string newMarkName;

      inputStream >> markName;
      inputStream >> newMarkName;

      if (markName.empty() || newMarkName.empty())
      {
        throw std::invalid_argument("Empty store parameters");
      }
      else
      {
        UI.store(markName, newMarkName, out);
      }
    }
    else if (command == "insert")
    {
      std::string order;
      std::string markName;
      std::string number;
      std::string name;

      inputStream >> order >> markName >> number;
      std::getline(inputStream >> std::ws, name);

      if (order.empty() || markName.empty() || number.empty() || name.empty())
      {
        throw std::invalid_argument("Empty insert parameters");
      }
      else if (order != "before" && order != "after")
      {
        throw std::invalid_argument("Invalid step order parameter");
      }
      else
      {
        name = parseName(name);
        UI.insert(markName, order, {name, number}, out);
      }
    }
    else if (command == "delete")
    {
      std::string markName;
      inputStream >> markName;

      if (markName.empty())
      {
        throw std::invalid_argument("Empty delete parameters");
      }
      else
      {
        UI.deleteContact(markName, out);
      }
    }
    else if (command == "show")
    {
      std::string markName;
      inputStream >> markName;

      if (markName.empty())
      {
        throw std::invalid_argument("Empty show parameters");
      }
      else
      {
        UI.show(markName, out);
      }
    }
    else if (command == "move")
    {
      std::string markName;
      std::string steps;

      inputStream >> markName;
      inputStream >> std::ws;
      inputStream >> steps;

      if (checkNumber(steps))
      {
        UI.move(markName, std::stoi(steps), out);
      }
      else if (steps == "first" || steps == "last")
      {
        UI.move(markName, steps, out);
      }
      else
      {
        throw std::invalid_argument("Invalid step move parameter");
      }
    }
    else
    {
      out << "<INVALID COMMAND>\n";
    }
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
