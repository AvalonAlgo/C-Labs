#ifndef FACTORIAL_CONTAINER_HPP
#define FACTORIAL_CONTAINER_HPP

#include <iterator>

class FactorialContainer
{
public:
    class const_iterator;
    using const_reverse_iterator = std::reverse_iterator<FactorialContainer::const_iterator>;

    FactorialContainer(size_t n);
    const_iterator begin() const;
    const_iterator end() const;
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;
private:
    size_t max_;
    size_t maxFactorial_;
};

class FactorialContainer::const_iterator : public std::iterator<std::bidirectional_iterator_tag, size_t,
    std::ptrdiff_t, size_t, size_t>
{
public:
    const_iterator(size_t index, size_t value);

    reference operator*() const noexcept;
    pointer operator->() noexcept;

    const_iterator &operator++() noexcept;
    const const_iterator operator++(int) noexcept;
    const_iterator &operator--() noexcept;
    const const_iterator operator--(int) noexcept;

    bool operator==(const const_iterator &rhs) const noexcept;
    bool operator!=(const const_iterator &rhs) const noexcept;

private:
    size_t index_;
    size_t value_;
};

#endif
