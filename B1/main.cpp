#include <iostream>
#include <stdexcept>
#include <sstream>

#include "tasks.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if ((argc < 2) || (argc > 4))
    {
      throw std::runtime_error("Invalid amount of arguments - expected 2, 3, or 4 arguments\n");
    }

    int task;
    std::istringstream in(argv[1]);
    in >> task;

    if (!in.eof())
    {
      throw std::runtime_error("Invalid input as task number\n");
    }

    switch(task)
    {
      case 1 :
        if (argc != 3)
        {
          std::cerr << "Invalid amount of arguments for task 1\n";
          return 1;
        }

        task1(argv[2]);
        break;

      case 2 :
        if (argc != 3)
        {
          std::cerr << "Invalid amount of arguments for task 2\n";
          return 1;
        }

        task2(argv[2]);
        break;

      case 3 :
        if (argc != 2)
        {
          std::cerr << "Invalid amount of arguments for task 3\n";
          return 1;
        }

        task3();
        break;

      case 4 :
      {
        if (argc != 4)
        {
          std::cerr << "Invalid amount of arguments for task 4\n";
          return 1;
        }

        int size;
        std::istringstream inSize(argv[3]);
        inSize >> size;

        if (!inSize.eof())
        {
          std::cerr << "Invalid vector size\n";
          return 1;
        }

        task4(size, argv[2]);
        break;
      }

      default :
        throw std::invalid_argument("Invalid task number - expected 1, 2, 3, or 4\n");
        break;
    }
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
  catch (const std::runtime_error& error)
  {
    std::cerr << error.what() << '\n';
    return 2;
  }

  return 0;
}
