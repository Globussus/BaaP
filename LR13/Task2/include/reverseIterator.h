#ifndef REVERSE_ITERATOR_H
#define REVERSE_ITERATOR_H

#include <cstddef>
#include "iterator.h"

class ReverseIterator {
public:
    using valueType = char;
    using pointer = char*;
    using reference = char&;
    using differenceType = std::ptrdiff_t;

    ReverseIterator();
    explicit ReverseIterator(pointer ptr);

    reference operator*() const;
    pointer operator->();

    ReverseIterator& operator++();
    ReverseIterator operator++(int);
    ReverseIterator& operator--();
    ReverseIterator operator--(int);

    ReverseIterator operator+(differenceType n) const;
    ReverseIterator operator-(differenceType n) const;
    differenceType operator-(const ReverseIterator& other) const;

    ReverseIterator& operator+=(differenceType n);
    ReverseIterator& operator-=(differenceType n);

    bool operator==(const ReverseIterator& other) const;
    bool operator!=(const ReverseIterator& other) const;

private:
    pointer ptr_;
};

#endif