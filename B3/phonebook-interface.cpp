#include "phonebook-interface.hpp"

PhonebookUI::PhonebookUI() :
  marks_({{"current", book_.end()}})
{}

void PhonebookUI::add(const Phonebook::contact_t& contact)
{
  if (book_.isEmpty())
  {
    book_.add(contact);
    for (auto iterator = marks_.begin(); iterator != marks_.end(); ++iterator)
    {
      iterator->second = book_.begin();
    }
  }
  else
  {
    book_.add(contact);
  }
}

void PhonebookUI::store(const std::string& markName, const std::string& newMarkName, std::ostream& out)
{
  auto it = marks_.find(markName);
  if (it == marks_.end())
  {
    out << "<INVALID BOOKMARK>";
    return;
  }
  if (book_.isEmpty())
  {
    out << "<EMPTY>";
    return;
  }
  marks_[newMarkName] = it->second;
}

void PhonebookUI::insert(const std::string& markName, const std::string& order,
  const Phonebook::contact_t& contact, std::ostream& out)
{
  auto it = marks_.find(markName);
  if (it == marks_.end())
  {
    out << "<INVALID BOOKMARK>\n";
    return;
  }
  if (book_.isEmpty())
  {
    book_.add(contact);
    return;
  }

  if (order == "before")
  {
    book_.insertBefore(it->second, contact);
  }
  else if (order == "after")
  {
    book_.insertAfter(it->second, contact);
  }
}

void PhonebookUI::deleteContact(const std::string& markName, std::ostream& out)
{
  auto it = marks_.find(markName);
  if (it == marks_.end())
  {
    out << "<INVALID BOOKMARK>\n";
    return;
  }
  if (book_.isEmpty())
  {
    out << "<EMPTY>\n";
    return;
  }
  auto temp = marks_[markName];
  auto iter = marks_.begin();
  while (iter != marks_.end())
  {
    if (iter->second == temp)
    {
      if ((it->second != book_.begin()) && (iter->second == std::prev(book_.end())))
      {
        iter->second--;
      }
      else
      {
        iter->second++;
      }
    }
    ++iter;
  }
  book_.erase(temp);
}

void PhonebookUI::show(const std::string& markName, std::ostream& out) const
{
  auto it = marks_.find(markName);
  if (it == marks_.end())
  {
    out << "<INVALID BOOKMARK>\n";
    return;
  }
  if (book_.isEmpty())
  {
    out << "<EMPTY>\n";
    return;
  }
  out << it->second->second << " " << it->second->first << "\n";
}

void PhonebookUI::move(const std::string& markName, int steps, std::ostream& out)
{
  auto it = marks_.find(markName);
  if (it == marks_.end())
  {
    out << "<INVALID BOOKMARK>\n";
  }
  else if (book_.isEmpty())
  {
    out << "<EMPTY>\n";
  }

  if (steps > 0 && steps > std::distance(it->second, book_.end()) - 1)
  {
    it->second = std::prev(book_.end());
  }
  else if (steps < 0 && (-steps) > std::distance(book_.begin(), it->second))
  {
    it->second = book_.begin();
  }

  std::advance(it->second, steps);
}

void PhonebookUI::move(const std::string &markName, const std::string &place, std::ostream &out)
{
  auto it = marks_.find(markName);
  if (it == marks_.end())
  {
    out << "<INVALID BOOKMARK>\n";
  }
  else if (book_.isEmpty())
  {
    out << "<EMPTY>\n";
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
