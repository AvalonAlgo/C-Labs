#include <iostream>
#include <vector>
#include <forward_list>
#include <stdexcept>
#include <functional>
#include <fstream>
#include <memory>
#include <random>
#include <cstring>
#include <ctime>

#include "tasks.hpp"
#include "sort.hpp"
#include "access-policies.hpp"
#include "utilities.hpp"

void getComparator(const char *order);

void task1(const char* order)
{
  std::function<bool(int&, int&)> comparison = getComparator<int>(order);

  std::vector<int> forOperatorSort;
  int input = 0;

  while (std::cin >> input)
  {
    forOperatorSort.push_back(input);
  }

  if (!std::cin.eof())
  {
    throw std::runtime_error("Invalid type in input - expected int type\n");
  }
  if (forOperatorSort.empty())
  {
    return;
  }

  std::vector<int> forAtSort(forOperatorSort);
  std::forward_list<int> forIteratorSort(forOperatorSort.begin(), forOperatorSort.end());

  sort(forOperatorSort, OperatorAccess<std::vector<int>>(), comparison);
  print(std::cout, forOperatorSort, " ");
  std::cout << "\n";

  sort(forAtSort, AtAccess<std::vector<int>>(), comparison);
  print(std::cout, forAtSort, " ");
  std::cout << "\n";

  sort(forIteratorSort, IteratorAccess<std::forward_list<int>>(), comparison);
  print(std::cout, forIteratorSort, " ");
  std::cout << "\n";
}

void task2(const char* fileName)
{
  if (fileName == nullptr)
  {
    throw std::invalid_argument("File name cannot be empty");
  }

  std::ifstream fileInput(fileName);

  if (!fileInput.is_open())
  {
    throw std::runtime_error("Cannot access the file\n");
  }

  size_t fileSize = 0;
  size_t allocatedSize = 16;
  std::unique_ptr<char[]> source = std::make_unique<char[]>(allocatedSize);

  while (!fileInput.eof())
  {
    fileInput.read(&source[fileSize], allocatedSize - fileSize);
    fileSize += fileInput.gcount();

    if (fileSize == allocatedSize)
    {
      const double GOLDEN_RATIO = 1.618;
      allocatedSize *= GOLDEN_RATIO;
      std::unique_ptr<char[]> newArray = std::make_unique<char[]>(allocatedSize);

      std::memcpy(newArray.get(), source.get(), fileSize);

      source = std::move(newArray);
    }
  }

  std::vector<char> dest(source.get(), source.get() + fileSize);
  print(std::cout, dest, "");
}

void task3()
{
  std::vector<int> forTask3;
  int input = 0;

  while (std::cin >> input)
  {
    if (input == 0)
    {
      break;
    }

    forTask3.push_back(input);
  }
  if (input != 0)
  {
    throw std::runtime_error("Invalid last number - expected zero\n");
  }

  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Invalid type in input - expected int type\n");
  }
  if (forTask3.empty())
  {
    return;
  }

  if (forTask3.back() == 1)
  {
    for (auto it = forTask3.begin(); it != forTask3.end();)
    {
      if (*it % 2 == 0)
      {
        it = forTask3.erase(it);
      }
      else
      {
        it++;
      }
    }
  }
  else if (forTask3.back() == 2)
  {
    for (auto it = forTask3.begin(); it != forTask3.end();)
    {
      if (*it % 3 == 0)
      {
        it = forTask3.insert(it + 1, 3, 1) + 3;
      }
      else
      {
        it++;
      }
    }
  }

  print(std::cout, forTask3, " ");
  std::cout << "\n";
}

void task4(int size, const char* order)
{
  if (size <= 0)
  {
    throw std::invalid_argument("Array size cannot be equal to or less than zero\n");
  }

  std::vector<double> forTask4(size);

  fillRandom(forTask4.data(), size);

  print(std::cout, forTask4, " ");
  std::cout << "\n";

  std::function<bool(double&, double&)> comparison = getComparator<double>(order);
  sort(forTask4, OperatorAccess<std::vector<double>>(), comparison);

  print(std::cout, forTask4, " ");
  std::cout << "\n";
}

void fillRandom(double* array, int size)
{
  std::default_random_engine rng;
  std::uniform_real_distribution<double> distribution(-1.0, 1.0);

  for (int i = 0; i < size; i++)
  {
    array[i] = distribution(rng);
  }
}
