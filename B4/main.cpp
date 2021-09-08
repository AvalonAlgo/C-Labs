#include <iostream>

void task(std::istream& in, std::ostream& out);

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
