#include "phonebook.hpp"

Phonebook::contactIter Phonebook::begin()
{
  return contacts_.begin();
}

Phonebook::contactIter Phonebook::end()
{
  return contacts_.end();
}

Phonebook::constContactIter Phonebook::cbegin() const
{
  return contacts_.cbegin();
}

Phonebook::constContactIter Phonebook::cend() const
{
  return contacts_.cend();
}

void Phonebook::insertBefore(contactIter iter, const contact_t& contact)
{
  if (contacts_.empty())
  {
    contacts_.push_back(contact);
  }
  contacts_.insert(iter, contact);
}

void Phonebook::insertAfter(contactIter iter, const contact_t& contact)
{
  if (contacts_.empty())
  {
    contacts_.push_back(contact);
  }
  contacts_.insert(std::next(iter), contact);
}

void Phonebook::add(const contact_t& contact)
{
  contacts_.push_back(contact);
}

Phonebook::contactIter Phonebook::erase(contactIter iter)
{
  return contacts_.erase(iter);
}

bool Phonebook::isEmpty() const
{
  return contacts_.empty();
}
