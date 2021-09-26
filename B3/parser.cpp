#include "parser.hpp"

#include <functional>

void printInvalidCommand(std::ostream &out, const PhonebookUI&)
{
  out << "<INVALID COMMAND>\n";
}

void printInvalidStep(std::ostream &out, const PhonebookUI&)
{
  out << "<INVALID STEP>\n";
}

Command getCommand(const std::string& command_type, std::istringstream& stringToParse, PhonebookUI&)
{
  const std::unordered_map<std::string, std::function<Command(std::istringstream&)>> Commands =
          {
                  {"add", parseAdd},
                  {"store", parseStore},
                  {"insert", parseInsert},
                  {"delete", parseDelete},
                  {"show", parseShow},
                  {"move", parseMove}
          };

  auto it = Commands.find(command_type);
  if (it == Commands.end())
  {
    return printInvalidCommand;
  }
  return it->second(stringToParse);
}

Command parse(const std::string &stringToParse, PhonebookUI& phonebook)
{
  std::istringstream stream(stringToParse);
  std::string command_name;
  stream >> command_name;

  return getCommand(command_name, stream, phonebook);
}

Command parseAdd(std::istringstream &in)
{
  std::string number, name;
  in >> number;
  in >> std::ws;
  std::getline(in, name);

  if (!(checkNumber(number) && checkName(name)))
  {
    return printInvalidCommand;
  }
  else
  {
    return std::bind(&PhonebookUI::add, std::placeholders::_2, Phonebook::contact_t{name, number}, std::placeholders::_1);
  }
}

Command parseStore(std::istringstream& in)
{
  std::string markName, newMarkName;
  in >> markName >> newMarkName;

  if (markName.empty() || newMarkName.empty())
  {
    return printInvalidCommand;
  }
  else
  {
    return std::bind(&PhonebookUI::store, std::placeholders::_2, markName, newMarkName, std::placeholders::_1);
  }
}

Command parseInsert(std::istringstream& in)
{
  std::string order, markName, number, name;
  in >> order >> markName >> number;
  in >> std::ws;
  std::getline(in, name);

  if (!(checkNumber(number) && checkName(name))
    || order.empty()
    || markName.empty()
    || ((order != "before" && order != "after")))
  {
    return printInvalidCommand;
  }
  else
  {
    return std::bind(&PhonebookUI::insert, std::placeholders::_2, markName, order,
                     Phonebook::contact_t{name, number}, std::placeholders::_1);
  }
}

Command parseDelete(std::istringstream& in)
{
  std::string markName;
  in >> markName;

  if (markName.empty())
  {
    return printInvalidCommand;
  }
  else
  {
    return std::bind(&PhonebookUI::deleteContact, std::placeholders::_2, markName, std::placeholders::_1);
  }
}

Command parseShow(std::istringstream& in)
{
  std::string markName;
  in >> markName;

  if (markName.empty())
  {
    return printInvalidCommand;
  }
  else
  {
    return std::bind(&PhonebookUI::show, std::placeholders::_2, markName, std::placeholders::_1);
  }
}

Command parseMove(std::istringstream& in)
{
  std::string markName, steps;
  in >> markName >> steps;

  if (checkNumber(steps))
  {
    return std::bind(&PhonebookUI::moveBySteps, std::placeholders::_2, markName, std::stoi(steps), std::placeholders::_1);
  }
  else if ((steps == "first") || (steps == "last"))
  {
    return std::bind(&PhonebookUI::moveByPlace, std::placeholders::_2, markName, steps, std::placeholders::_1);
  }
  else
  {
    return printInvalidStep;
  }
}

bool checkName(std::string &name)
{
  if (name.empty())
  {
    return false;
  }

  if ((*name.begin() == '\"') && (*std::prev(name.end()) == '\"'))
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
          return false;
        }
      }
    }

    return true;
  }

  return false;
}

bool checkNumber(std::string& number)
{
  if (number.empty())
  {
    return false;
  }

  auto it = number.begin();
  if ((*it != '+') && (*it != '-') && !(std::isdigit(*it)))
  {
    return false;
  }
  it++;

  while (it != number.end())
  {
    if (!std::isdigit(*it))
    {
      return false;
    }
    it++;
  }

  return true;
}
