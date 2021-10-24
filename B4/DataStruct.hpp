#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>
#include <vector>

struct DataStruct
{
    int key1;
    int key2;
    std::string str;
};

void task(std::istream& in, std::ostream& out);
int getKey(const std::string& str);
void print(const std::vector<DataStruct>& array, std::ostream& out);
bool dataStructCompare(const DataStruct &lhs, const DataStruct &rhs);

#endif
