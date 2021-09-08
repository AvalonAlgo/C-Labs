#include <iostream>

#include "factorial-container.hpp"

FactorialContainer::FactorialContainer(size_t n) :
  max_(n)
{
}

FactorialContainer::Iterator FactorialContainer::begin()
{
  return Iterator(1);
}

FactorialContainer::Iterator FactorialContainer::end()
{
  return Iterator(max_ + 1);
}

FactorialContainer::Iterator::Iterator(size_t index) :
        index_(index),
        value_(factorial(index))
{
}

const size_t &FactorialContainer::Iterator::operator*() const noexcept
{
  return value_;
}

const size_t *FactorialContainer::Iterator::operator->() const noexcept
{
  return &value_;
}

FactorialContainer::Iterator &FactorialContainer::Iterator::operator++() noexcept
{
  ++index_;
  value_ *= index_;
  return *this;
}

const FactorialContainer::Iterator FactorialContainer::Iterator::operator++(int) noexcept
{
  FactorialContainer::Iterator oldIter = *this;
  ++(*this);
  return oldIter;
}

FactorialContainer::Iterator &FactorialContainer::Iterator::operator--() noexcept
{
  value_ /= index_;
  --index_;
  return *this;
}

const FactorialContainer::Iterator FactorialContainer::Iterator::operator--(int) noexcept
{
  FactorialContainer::Iterator oldIter = *this;
  --(*this);
  return oldIter;
}

bool FactorialContainer::Iterator::operator==(const Iterator &rhs) const noexcept
{
  return (value_ == rhs.value_) && (index_ == rhs.index_);
}

bool FactorialContainer::Iterator::operator!=(const Iterator &rhs) const noexcept
{
  return !(*this == rhs);
}

size_t FactorialContainer::Iterator::factorial(size_t n)
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
