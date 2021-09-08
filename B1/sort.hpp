#ifndef SORT_HPP
#define SORT_HPP

#include <algorithm>
#include <functional>
#include <cstring>
#include <stdexcept>

template <typename T>
std::function<bool(const T&, const T&)> getComparator(const char* order)
{
  if (order == nullptr)
  {
    throw std::invalid_argument("Order cannot be empty\n");
  }

  if (std::strcmp(order, "ascending") == 0)
  {
    return std::greater<T>();
  }
  if (std::strcmp(order, "descending") == 0)
  {
    return std::less<T>();
  }

  throw std::invalid_argument("Invalid sort order declared\n");
}

template <typename Container, typename AccessPolicy, typename Comparator>
void sort(Container& container, AccessPolicy access, Comparator comparator)
{
  for (auto i = access.getBegin(container); i != access.getEnd(container); i++)
  {
    for (auto j = i; j != access.getEnd(container); j++)
    {
      if (comparator(access(container, i), access(container, j)))
      {
        std::swap(access(container, i), access(container, j));
      }
    }
  }
}

#endif
