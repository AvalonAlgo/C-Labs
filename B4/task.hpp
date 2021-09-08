#ifndef TASK_HPP
#define TASK_HPP

#include <iostream>
#include <string>

#include "DataStruct.hpp"

int parseKey(const std::string& str);
void print(const std::vector<DataStruct>& array, std::ostream& out);
bool dataStructCompare(const DataStruct &lhs, const DataStruct &rhs);
void task(std::istream& in, std::ostream& out);

#endif
