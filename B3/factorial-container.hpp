#ifndef FACTORIAL_CONTAINER_HPP
#define FACTORIAL_CONTAINER_HPP

#include <iterator>

class FactorialContainer
{
public:
    FactorialContainer(size_t n);
    class iterator_t;
    iterator_t begin();
    iterator_t end();
private:
    size_t max_;
};

class FactorialContainer::iterator_t : public std::iterator<std::bidirectional_iterator_tag, size_t>
{
public:
    iterator_t(size_t index);

    const size_t &operator*() const noexcept;
    const size_t *operator->() const noexcept;

    iterator_t &operator++() noexcept;
    const iterator_t operator++(int) noexcept;
    iterator_t &operator--() noexcept;
    const iterator_t operator--(int) noexcept;

    bool operator==(const iterator_t &rhs) const noexcept;
    bool operator!=(const iterator_t &rhs) const noexcept;

private:
    size_t index_;
    size_t value_;
    size_t factorial(size_t n);
};

#endif
