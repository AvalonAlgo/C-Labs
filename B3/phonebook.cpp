#include "phonebook.hpp"

Phonebook::iterator Phonebook::begin()
{
  return contacts_.begin();
}

Phonebook::iterator Phonebook::end()
{
  return contacts_.end();
}

Phonebook::const_iterator Phonebook::cbegin() const
{
  return contacts_.cbegin();
}

Phonebook::const_iterator Phonebook::cend() const
{
  return contacts_.cend();
}

void Phonebook::insertBefore(iterator iter, const contact_t& contact)
{
  if (contacts_.empty())
  {
    contacts_.push_back(contact);
  }
  contacts_.insert(iter, contact);
}

void Phonebook::insertAfter(iterator iter, const contact_t& contact)
{
  if (contacts_.empty())
  {
    contacts_.push_back(contact);
  }
  contacts_.insert(std::next(iter), contact);
}

void Phonebook::push(const contact_t& contact)
{
  contacts_.push_back(contact);
}

Phonebook::iterator Phonebook::erase(iterator iter)
{
  return contacts_.erase(iter);
}

bool Phonebook::isEmpty() const
{
  return contacts_.empty();
}
