#include <iostream>

#include "factorial-container.hpp"

FactorialContainer::FactorialContainer(size_t n) :
  max_(n)
{
}

FactorialContainer::iterator_t FactorialContainer::begin()
{
  return iterator_t(1);
}

FactorialContainer::iterator_t FactorialContainer::end()
{
  return iterator_t(max_ + 1);
}

FactorialContainer::iterator_t::iterator_t(size_t index) :
  index_(index),
  value_(factorial(index))
{
}

const size_t &FactorialContainer::iterator_t::operator*() const noexcept
{
  return value_;
}

const size_t *FactorialContainer::iterator_t::operator->() const noexcept
{
  return &value_;
}

FactorialContainer::iterator_t &FactorialContainer::iterator_t::operator++() noexcept
{
  ++index_;
  value_ *= index_;
  return *this;
}

const FactorialContainer::iterator_t FactorialContainer::iterator_t::operator++(int) noexcept
{
  FactorialContainer::iterator_t oldIter = *this;
  ++(*this);
  return oldIter;
}

FactorialContainer::iterator_t &FactorialContainer::iterator_t::operator--() noexcept
{
  value_ /= index_;
  --index_;
  return *this;
}

const FactorialContainer::iterator_t FactorialContainer::iterator_t::operator--(int) noexcept
{
  FactorialContainer::iterator_t oldIter = *this;
  --(*this);
  return oldIter;
}

bool FactorialContainer::iterator_t::operator==(const iterator_t &rhs) const noexcept
{
  return (value_ == rhs.value_) && (index_ == rhs.index_);
}

bool FactorialContainer::iterator_t::operator!=(const iterator_t &rhs) const noexcept
{
  return !(*this == rhs);
}

size_t FactorialContainer::iterator_t::factorial(size_t n)
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
