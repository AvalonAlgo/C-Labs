#include "factorial-container.hpp"

#include <stdexcept>

FactorialContainer::FactorialContainer(size_t n) :
  max_(n),
  maxFactorial_(1)
{
  for (size_t i = 1; i <= n; i++)
  {
    if (maxFactorial_ > (SIZE_MAX / i))
    {
      throw std::overflow_error("Current value exceeds size_t limit");
    }

    maxFactorial_ *= i;
  }
}

FactorialContainer::const_iterator FactorialContainer::begin() const
{
  return const_iterator(1, 1);
}

FactorialContainer::const_iterator FactorialContainer::end() const
{
  return const_iterator(max_ + 1, maxFactorial_ * (max_ + 1));
}

FactorialContainer::const_reverse_iterator FactorialContainer::rbegin() const
{
  return std::make_reverse_iterator(end());
}

FactorialContainer::const_reverse_iterator FactorialContainer::rend() const
{
  return std::make_reverse_iterator(begin());
}

FactorialContainer::const_iterator::const_iterator(size_t index, size_t value) :
  index_(index),
  value_(value)
{
}

size_t FactorialContainer::const_iterator::operator*() const noexcept
{
  return value_;
}

size_t FactorialContainer::const_iterator::operator->() noexcept
{
  return value_;
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
