#ifndef ACCESS_POLICIES_HPP
#define ACCESS_POLICIES_HPP

#include <cstddef>

template <typename T>
struct OperatorAccess
{
    using value_type = typename T::reference;
    using iterator_t = std::size_t;

    static iterator_t getBegin(const T&)
    {
      return 0;
    }

    static iterator_t getEnd(const T& container)
    {
      return container.size();
    }

    value_type operator()(T& container, const iterator_t index)
    {
      return container[index];
    }
};

template <typename T>
struct AtAccess
{
    using value_type = typename T::reference;
    using iterator_t = std::size_t;

    static iterator_t getBegin(const T&)
    {
      return 0;
    }

    static iterator_t getEnd(const T& container)
    {
      return container.size();
    }

    value_type operator()(T& container, const iterator_t index)
    {
      return container.at(index);
    }
};

template <typename T>
struct IteratorAccess
{
    using value_type = typename T::reference;
    using iterator_t = typename T::iterator;

    iterator_t getBegin(T& container)
    {
      return container.begin();
    }

    iterator_t getEnd(T& container)
    {
      return container.end();
    }

    value_type operator()(T&, iterator_t it)
    {
      return *it;
    }
};

#endif
