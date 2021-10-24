#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <functional>
#include <unordered_map>

#include "phonebook.hpp"
#include "phonebook-interface.hpp"

using Command = std::function<void(std::ostream &out, PhonebookUI& UI)>;

void printInvalidCommand(std::ostream &out, const PhonebookUI&);
void printInvalidStep(std::ostream &out, const PhonebookUI&);

Command parse(const std::string &stringToParse, PhonebookUI& UI);
Command parseAdd(std::istringstream& in);
Command parseStore(std::istringstream& in);
Command parseInsert(std::istringstream& in);
Command parseDelete(std::istringstream& in);
Command parseShow(std::istringstream& in);
Command parseMove(std::istringstream& in);

Phonebook::contact_t parseContact(std::istream& in);
std::istream& operator>>(std::istream& in, Phonebook::contact_t& contact);

bool readName(std::string &name, std::istringstream& in);
bool readMarkName(std::string &markName, std::istringstream& in);
bool readNumber(std::string &number, std::istringstream& in);
bool readStep(std::string &name, std::istringstream& in);

#endif
