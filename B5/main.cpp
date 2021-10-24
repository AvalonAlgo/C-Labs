#include <iostream>

void taskOne(std::istream& in, std::ostream& out);
void taskTwo(std::istream& in, std::ostream& out);

int main(int argc, char *argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Invalid number of input parameters");
    }

    const int taskNumber = std::atoi(argv[1]);
    switch (taskNumber)
    {
    case 1:
      taskOne(std::cin, std::cout);
      break;
    case 2:
      taskTwo(std::cin, std::cout);
      break;
    default:
      throw std::invalid_argument("Invalid task number");
    }

    return 0;
  }
  catch (const std::invalid_argument &err)
  {
    std::cerr << err.what() << '\n';
    return 1;
  }
  catch (const std::exception &err)
  {
    std::cerr << err.what() << '\n';
    return 2;
  }
}
