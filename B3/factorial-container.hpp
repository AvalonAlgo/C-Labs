#ifndef FACTORIAL_CONTAINER_HPP
#define FACTORIAL_CONTAINER_HPP

#include <iterator>

class FactorialContainer
{
public:
    FactorialContainer(size_t n);
    class const_iterator;
    const_iterator begin();
    const_iterator end();
private:
    size_t max_;
    size_t maxFactorial_;
};

class FactorialContainer::const_iterator : public std::iterator<std::bidirectional_iterator_tag, size_t>
{
public:
    const_iterator(size_t index);

    size_t operator*() const noexcept;
    const size_t *operator->() noexcept;

    const_iterator &operator++() noexcept;
    const const_iterator operator++(int) noexcept;
    const_iterator &operator--() noexcept;
    const const_iterator operator--(int) noexcept;

    bool operator==(const const_iterator &rhs) const noexcept;
    bool operator!=(const const_iterator &rhs) const noexcept;

private:
    size_t index_;
    size_t value_;
    size_t factorial(size_t n);
};

#endif
