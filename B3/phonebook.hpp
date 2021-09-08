#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <iostream>
#include <string>
#include <list>

class Phonebook
{
public:
    using contact_t = std::pair<std::string /*name*/, std::string /*number*/>;
    using contactIter = std::list<contact_t>::iterator;
    using constContactIter = std::list<contact_t>::const_iterator;

    contactIter begin();
    contactIter end();
    constContactIter cbegin() const;
    constContactIter cend() const;

    void insertBefore(contactIter iter, const contact_t& contact);
    void insertAfter(contactIter iter, const contact_t& contact);
    contactIter erase(contactIter iter);
    void add(const contact_t& contact);
    bool isEmpty() const;

private:
    std::list<contact_t> contacts_;
};

#endif
