#include <iostream>

void task1();
void task2();

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
        task1();
        break;
      case 2:
        task2();
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
