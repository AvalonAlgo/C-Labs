#include <ostream>
#include <vector>
#include <sstream>
#include <algorithm>

#include "DataStruct.hpp"

void task(std::istream& in, std::ostream& out)
{
  std::vector<DataStruct> array;

  std::string inputLine;
  while (std::getline(in, inputLine))
  {
    std::stringstream input(inputLine);
    std::string forKey1, forKey2, forStr;

    std::getline(input >> std::ws, forKey1, ',');
    int key1 = getKey(forKey1);

    std::getline(input >> std::ws, forKey2, ',');
    int key2 = getKey(forKey2);

    std::getline(input >> std::ws, forStr, '\n');
    if (forStr.empty())
    {
      throw std::invalid_argument("Invalid input, missing string\n");
    }

    array.push_back({key1, key2, forStr});
  }

  std::sort(array.begin(), array.end(), dataStructCompare);
  print(array, out);
}

int getKey(const std::string &str)
{
  if (str.empty())
  {
    throw std::invalid_argument("Invalid input, key missing\n");
  }

  std::istringstream in(str);
  int result;
  in >> result;

  if ((!in))
  {
    throw std::invalid_argument("Invalid input in key\n");
  }
  if ((result > 5) || (result < -5))
  {
    throw std::out_of_range("Input key out of range [-5, 5]\n");
  }

  return result;
}

void print(const std::vector<DataStruct> &array, std::ostream& out)
{
  for (auto it = array.begin(); it != array.end(); it++)
  {
    out << it->key1 << "," << it->key2 << "," << it->str << "\n";
  }
}

bool dataStructCompare(const DataStruct &lhs, const DataStruct &rhs)
{
  if (lhs.key1 != rhs.key1)
  {
    return (lhs.key1 < rhs.key1);
  }
  else if (lhs.key2 != rhs.key2)
  {
    return (lhs.key2 < rhs.key2);
  }
  else
  {
    return (lhs.str.size() < rhs.str.size());
  }
}
