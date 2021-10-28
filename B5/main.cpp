#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

void taskOne(std::istream& in, std::ostream& out);
void taskTwo(std::istream& in, std::ostream& out);

int main(int argc, char* args[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Invalid amount of arguments");
    }

    std::istringstream argStream(args[1]);
    int taskNumber;
    argStream >> taskNumber;
    if (!argStream.eof() || (taskNumber > 2) || (taskNumber < 1))
    {
      throw std::runtime_error("Error in task parameter");
    }

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
  }
  catch (const std::runtime_error& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
  catch (const std::bad_alloc& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }

  return 0;
}
