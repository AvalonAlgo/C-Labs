#ifndef FACTORIAL_CONTAINER_HPP
#define FACTORIAL_CONTAINER_HPP

#include <iterator>

class FactorialContainer
{
public:
    FactorialContainer(size_t n);
    class Iterator;
    Iterator begin();
    Iterator end();
private:
    size_t max_;
};

class FactorialContainer::Iterator : public std::iterator<std::bidirectional_iterator_tag, size_t>
{
public:
    Iterator(size_t index);

    const size_t &operator*() const noexcept;
    const size_t *operator->() const noexcept;

    Iterator &operator++() noexcept;
    const Iterator operator++(int) noexcept;
    Iterator &operator--() noexcept;
    const Iterator operator--(int) noexcept;

    bool operator==(const Iterator &rhs) const noexcept;
    bool operator!=(const Iterator &rhs) const noexcept;

private:
    size_t index_;
    size_t value_;
    size_t factorial(size_t n);
};

#endif
