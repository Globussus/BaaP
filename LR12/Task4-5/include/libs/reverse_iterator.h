#ifndef REVERSEEITERATOR_H
#define REVERSEEITERATOR_H

template <typename T>
class ReverseIterator {
private:
    T* it;
public:
    ReverseIterator(T* first) : it(first) {}
    T& operator+(int n) { return *(it - n); }
    T& operator-(int n) { return *(it + n); }
    T& operator++() { return *it--; }
    T& operator--() { return *it++; }
    T& operator*() { return *it; }
    int distance(ReverseIterator<T>& other) { return it - other.it; }
};

#endif 