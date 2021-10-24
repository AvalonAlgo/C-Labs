#include <iostream>
#include <stdexcept>

#include "DataStruct.hpp"

int main()
{
  try
  {
    task(std::cin, std::cout);
  }
  catch (const std::out_of_range &err)
  {
    std::cerr << err.what() << '\n';
    return 1;
  }
  catch (const std::exception &err)
  {
    std::cerr << err.what() << '\n';
    return 2;
  }

  return 0;
}
