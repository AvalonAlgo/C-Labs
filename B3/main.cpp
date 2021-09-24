#include <iostream>
#include <sstream>

#include "tasks.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Invalid amount of arguments";
    return 1;
  }
  try
  {
    std::istringstream taskNumber(argv[1]);
    int task;
    taskNumber >> task;
    if (!taskNumber.eof())
    {
      throw  std::runtime_error("Invalid task number");
    }
    switch (task)
    {
      case 1:
        doTaskOne(std::cin, std::cout);
        break;

      case 2:
        doTaskTwo(std::cout);
        break;

      default:
        throw  std::invalid_argument("Invalid task number");
    }
  }
  catch (const std::invalid_argument &err)
  {
    std::cerr << err.what() << '\n';
    return 1;
  }
  catch (const std::exception& error)
  {
    std::cerr << error.what();
    return 2;
  }

  return 0;
}
