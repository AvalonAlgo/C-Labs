#include <functional>

#include "parser.hpp"

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

  if (!(readNumber(number, in) && readName(name, in)))
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

  if (!(readMarkName(markName, in) && readMarkName(newMarkName, in)))
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
  std::string pos, markName, number, name;
  in >> pos;

  bool isMarkName = readMarkName(markName, in);
  bool isNumber = readNumber(number, in);
  bool isName = readName(name, in);

  if (!(isNumber && isName && isMarkName) || (pos.empty()) || ((pos != "before") && (pos != "after")))
  {
    return printInvalidCommand;
  }
  else if (pos == "before")
  {
    return std::bind(&PhonebookUI::insert, std::placeholders::_2, markName, PhonebookUI::BEFORE,
      Phonebook::contact_t{name, number}, std::placeholders::_1);
  }
  else
  {
    return std::bind(&PhonebookUI::insert, std::placeholders::_2, markName, PhonebookUI::AFTER,
      Phonebook::contact_t{name, number}, std::placeholders::_1);
  }
}

Command parseDelete(std::istringstream& in)
{
  std::string markName;

  if (!readMarkName(markName, in))
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

  if (!readMarkName(markName, in))
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

  bool isMarkName = readMarkName(markName, in);
  bool isStep = readStep(steps, in);

  bool stepIsNumeric;
  for (auto it = steps.begin(); it != steps.end(); it++)
  {
    if ((*it == '+') || (*it == '-'))
    {
      continue;
    }
    else if (!std::isdigit(*it))
    {
      stepIsNumeric = false;
    }
    else
    {
      stepIsNumeric = true;
    }
  }

  if (!isMarkName)
  {
    return printInvalidCommand;
  }
  else if (!isStep)
  {
    return printInvalidStep;
  }

  if (isMarkName && (isStep))
  {
    if (stepIsNumeric)
    {
      return std::bind(&PhonebookUI::moveBySteps, std::placeholders::_2, markName, std::stoi(steps), std::placeholders::_1);
    }
    else
    {
      return std::bind(&PhonebookUI::moveByPlace, std::placeholders::_2, markName, steps, std::placeholders::_1);
    }
  }

  return printInvalidCommand;
}

bool readMarkName(std::string &markName, std::istringstream& in)
{
  char c = ' ';
  in >> std::ws >> c;
  if ((c == ' ') || !((c == '-') || std::isalpha(c) || std::isdigit(c)))
  {
    return false;
  }
  markName.push_back(c);
  while (in.get(c))
  {
    if (c == ' ')
    {
      break;
    }
    else if (!((c == '-') || std::isalpha(c) || std::isdigit(c)))
    {
      return false;
    }

    markName.push_back(c);
  }

  return true;
}

bool readStep(std::string &step, std::istringstream& in)
{
  char c = ' ';
  in >> std::ws >> c;
  if ((c == '-') || (c == '+') || std::isdigit(c))
  {
    step.push_back(c);
    while (in.get(c))
    {
      if (c == ' ')
      {
        break;
      }
      else if (!(std::isdigit(c)))
      {
        return false;
      }

      step.push_back(c);
    }

    return true;
  }
  step.push_back(c);
  while (in.get(c))
  {
    if (c == ' ')
    {
      break;
    }

    step.push_back(c);
  }

  if ((step == "first") || (step == "last"))
  {
    return true;
  }

  return false;
}

bool readNumber(std::string &number, std::istringstream& in)
{
  char c = ' ';
  in >> std::ws >> c;
  if ((c == '-') || (c == '+'))
  {
    number.push_back(c);
  }
  else if (!(std::isdigit(c)))
  {
    return false;
  }
  number.push_back(c);
  while (in.get(c))
  {
    if (c == ' ')
    {
      break;
    }
    else if (!(std::isdigit(c)))
    {
      return false;
    }

    number.push_back(c);
  }

  return true;
}

bool readName(std::string &name, std::istringstream& in)
{
  char c = ' ';
  in >> std::ws >> c;
  if (c != '"')
  {
    return false;
  }
  while (in.get(c))
  {
    if ((c == '"') || (c == '\'') || (c == '\\'))
    {
      if ((!name.empty() && (name.back() == '\\')))
      {
        name.pop_back();
      }
      else if (c == '"')
      {
        return true;
      }
    }
    name.push_back(c);
  }

  return false;
}
