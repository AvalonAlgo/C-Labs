#ifndef PHONEBOOK_INTERFACE_HPP
#define PHONEBOOK_INTERFACE_HPP

#include <unordered_map>
#include <string>

#include "phonebook.hpp"

class PhonebookUI
{
public:
    PhonebookUI();

    void add(const Phonebook::contact_t& contact);
    void store(const std::string& markName, const std::string& newMarkName, std::ostream& out);
    void insert(const std::string& markName, const std::string& order,const Phonebook::contact_t& contact, std::ostream& out);
    void deleteContact(const std::string& markName, std::ostream& out);
    void show(const std::string& markName, std::ostream& out) const;
    void move(const std::string& markName, int steps, std::ostream& out);
    void move(const std::string& markName, const std::string& place, std::ostream& out);

private:
    Phonebook book_;
    std::unordered_map<std::string, Phonebook::contactIter> marks_;
};

#endif
