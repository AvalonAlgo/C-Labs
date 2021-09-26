#include <iostream>

#include "factorial-container.hpp"

FactorialContainer::FactorialContainer(size_t n) :
  max_(n),
  maxFactorial_(1)
{
  for (size_t i = 1; i <= n; i++)
  {
    if (maxFactorial_ > SIZE_MAX / i)
    {
      throw std::overflow_error("Current value exceeds size_t limit");
    }

    maxFactorial_ *= i;
  }
}

FactorialContainer::const_iterator FactorialContainer::begin()
{
  return const_iterator(1);
}

FactorialContainer::const_iterator FactorialContainer::end()
{
  return const_iterator(max_ + 1);
}

FactorialContainer::const_iterator::const_iterator(size_t index) :
  index_(index),
  value_(factorial(index))
{
}

size_t FactorialContainer::const_iterator::operator*() const noexcept
{
  return value_;
}

const size_t *FactorialContainer::const_iterator::operator->() noexcept
{
  return &value_;
}

FactorialContainer::const_iterator &FactorialContainer::const_iterator::operator++() noexcept
{
  ++index_;
  value_ *= index_;
  return *this;
}

const FactorialContainer::const_iterator FactorialContainer::const_iterator::operator++(int) noexcept
{
  FactorialContainer::const_iterator oldIter = *this;
  ++(*this);
  return oldIter;
}

FactorialContainer::const_iterator &FactorialContainer::const_iterator::operator--() noexcept
{
  value_ /= index_;
  --index_;
  return *this;
}

const FactorialContainer::const_iterator FactorialContainer::const_iterator::operator--(int) noexcept
{
  FactorialContainer::const_iterator oldIter = *this;
  --(*this);
  return oldIter;
}

bool FactorialContainer::const_iterator::operator==(const const_iterator &rhs) const noexcept
{
  return (value_ == rhs.value_) && (index_ == rhs.index_);
}

bool FactorialContainer::const_iterator::operator!=(const const_iterator &rhs) const noexcept
{
  return !(*this == rhs);
}

size_t FactorialContainer::const_iterator::factorial(size_t n)
{
  if (n == 0)
  {
    return 1;
  }
  size_t result = 1;
  for (size_t i = 2; i != n + 1; ++i)
  {
    result *= i;
  }
  return result;
}
