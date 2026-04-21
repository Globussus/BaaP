#ifndef ITERATOR_H
#define ITERATOR_H

#include <cstddef>

class Iterator {
public:
    using valueType = char;
    using pointer = char*;
    using reference = char&;
    using differenceType = std::ptrdiff_t;

    Iterator();
    explicit Iterator(pointer ptr);

    reference operator*() const;
    pointer operator->();

    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);

    Iterator operator+(differenceType n) const;
    Iterator operator-(differenceType n) const;
    differenceType operator-(const Iterator& other) const;

    Iterator& operator+=(differenceType n);
    Iterator& operator-=(differenceType n);

    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;
    bool operator<(const Iterator& other) const;
    bool operator<=(const Iterator& other) const;
    bool operator>(const Iterator& other) const;
    bool operator>=(const Iterator& other) const;

private:
    pointer ptr_;
};

#endif