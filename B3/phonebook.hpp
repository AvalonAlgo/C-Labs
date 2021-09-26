#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <iostream>
#include <string>
#include <list>

class Phonebook
{
public:
    using contact_t = std::pair<std::string, std::string>;
    using iterator = std::list<contact_t>::iterator;
    using const_iterator = std::list<contact_t>::const_iterator;

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;

    void insertBefore(iterator iter, const contact_t& contact);
    void insertAfter(iterator iter, const contact_t& contact);
    iterator erase(iterator iter);
    void push(const contact_t& contact);
    bool isEmpty() const;

private:
    std::list<contact_t> contacts_;
};

#endif
