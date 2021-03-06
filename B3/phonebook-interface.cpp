#include <algorithm>
#include <iterator>

#include "phonebook-interface.hpp"

PhonebookUI::PhonebookUI() :
  marks_({{"current", book_.end()}})
{}

void printInvalidBookmark(std::ostream &out)
{
  out << "<INVALID BOOKMARK>\n";
}

void printEmpty(std::ostream &out)
{
  out << "<EMPTY>\n";
}

void PhonebookUI::add(const Phonebook::contact_t& contact, std::ostream&)
{
  if (book_.isEmpty())
  {
    book_.push(contact);
    for (auto iterator = marks_.begin(); iterator != marks_.end(); ++iterator)
    {
      iterator->second = book_.begin();
    }
  }
  else
  {
    book_.push(contact);
  }
}

void PhonebookUI::store(const std::string& markName, const std::string& newMarkName, std::ostream& out)
{
  auto it = marks_.find(markName);
  if (it == marks_.end())
  {
    printInvalidBookmark(out);
    return;
  }
  if (book_.isEmpty())
  {
    printEmpty(out);
    return;
  }
  marks_[newMarkName] = it->second;
}

void PhonebookUI::insert(const std::string& markName, Position pos,
    const Phonebook::contact_t& contact, std::ostream& out)
{
  if (book_.isEmpty())
  {
    add(contact, out);
    return;
  }

  auto it = marks_.find(markName);
  if (it == marks_.end())
  {
    printInvalidBookmark(out);
    return;
  }

  if (pos == BEFORE)
  {
    book_.insertBefore(it->second, contact);
  }
  else if (pos == AFTER)
  {
    book_.insertAfter(it->second, contact);
  }
}

void PhonebookUI::deleteContact(const std::string& markName, std::ostream& out)
{
  auto iteratorOfCurrentMark = marks_.find(markName);
  if (iteratorOfCurrentMark == marks_.end())
  {
    printInvalidBookmark(out);
    return;
  }
  if (book_.isEmpty())
  {
    printEmpty(out);
    return;
  }
  auto deletedMark = iteratorOfCurrentMark->second;

  auto iteratorOfFirstBookmark = marks_.begin();
  auto iteratorOfLastContact = std::prev(book_.end());
  auto iteratorOfFirstContact = book_.begin();

  while (iteratorOfFirstBookmark != marks_.end())
  {
    if (iteratorOfFirstBookmark->second == deletedMark)
    {
      if ((deletedMark != iteratorOfFirstContact)
        && (iteratorOfFirstBookmark->second == iteratorOfLastContact))
      {
        iteratorOfFirstBookmark->second--;
      }
      else
      {
        iteratorOfFirstBookmark->second++;
      }
    }
    ++iteratorOfFirstBookmark;
  }
  book_.erase(deletedMark);
}

void PhonebookUI::show(const std::string& markName, std::ostream& out) const
{
  auto it = marks_.find(markName);
  if (it == marks_.end())
  {
    printInvalidBookmark(out);
    return;
  }
  if (book_.isEmpty())
  {
    printEmpty(out);
    return;
  }
  out << it->second->second << " " << it->second->first << "\n";
}

void PhonebookUI::moveBySteps(const std::string& markName, int steps, std::ostream& out)
{
  auto it = marks_.find(markName);
  if (it == marks_.end())
  {
    printInvalidBookmark(out);
    return;
  }
  else if (book_.isEmpty())
  {
    printEmpty(out);
    return;
  }

  if ((steps > 0) && (steps > std::distance(it->second, book_.end()) - 1))
  {
    it->second = std::prev(book_.end());
  }
  else if ((steps < 0) && ((-steps) > std::distance(book_.begin(), it->second)))
  {
    it->second = book_.begin();
  }
  else
  {
    std::advance(it->second, steps);
  }
}

void PhonebookUI::moveByPlace(const std::string &markName, const std::string &place, std::ostream &out)
{
  auto it = marks_.find(markName);
  if (it == marks_.end())
  {
    printInvalidBookmark(out);
  }
  else if (book_.isEmpty())
  {
    printEmpty(out);
  }

  if (place == "first")
  {
    it->second = book_.begin();
  }
  else if (place == "last")
  {
    it->second = std::prev(book_.end());
  }
}
