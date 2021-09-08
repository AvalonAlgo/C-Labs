#ifndef UTILITIES
#define UTILITIES

#include <ostream>

template <typename T>
void print(std::ostream& out, T& container, const char* delimeter)
{
  for (auto it = container.begin(); it != container.end(); it++)
  {
    out << *it;

    if (it != container.end())
    {
      out << delimeter;
    }
  }
}

#endif
