#ifndef VECTOR_H
#define VECTOR_H

#include <cstdint>
#include <cstdio>
#include <stdexcept>
#include <new>
#include "iterator.h"
#include "reverse_iterator.h"

template <typename T>
class Vector {
private:
    T* array = nullptr;
    size_t _size = 0;
    size_t _capacity = 0;

public:
    using iterator = Iterator<T>;
    using reverseIterator = ReverseIterator<T>;
    using constIterator = Iterator<const T>;

    Vector() : array(nullptr), _size(0), _capacity(0) {}

    Vector(size_t n) : array(nullptr), _size(0), _capacity(0) {
        resize(n);
    }

    Vector(const Vector<T>& vector) : _size(vector._size), _capacity(vector._size) {
        if (_capacity > 0) {
            array = reinterpret_cast<T*>(new char[_capacity * sizeof(T)]);
            for (size_t i = 0; i < _size; i++) {
                new (array + i) T(vector.array[i]);
            }
        } else {
            array = nullptr;
        }
    }

    ~Vector() {
        clear();
        delete[] reinterpret_cast<char*>(array);
    }

    void assign(size_t number, T value) {
        clear();
        resize(number, value);
    }

    void assign(iterator begin, iterator end) {
        clear();
        size_t n = 0;
        for (iterator it = begin; it != end; ++it) n++;
        reserve(n);
        for (iterator it = begin; it != end; ++it) {
            push_back(*it);
        }
    }

    const T& at(size_t i) const {
        if (i >= _size)
            throw std::out_of_range("Index out of range");
        return array[i];
    }

    T& back() { return array[_size - 1]; }
    iterator begin() { return iterator(array); }
    size_t capacity() const { return _capacity; }
    constIterator cbegin() const { return constIterator(array); }
    
    void clear() {
        for (size_t i = 0; i < _size; i++) {
            (array + i)->~T();
        }
        _size = 0;
    }

    T* data() {
        return array;
    }

    template<typename... Args>
    iterator emplace(iterator it, Args&&... args) {
        if (_size == 0) {
            if (_capacity == 0) reserve(1);
            new (array) T(std::forward<Args>(args)...);
            _size++;
            return iterator(array + 1);
        }
        size_t index = it.distance(begin());
        if (_size >= _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }
        _size++;
        for (size_t i = _size - 1; i > index; i--) {
            new (array + i) T(array[i - 1]);
            (array + i - 1)->~T();
        }
        new (array + index) T(std::forward<Args>(args)...);
        return iterator(array + index + 1);
    }

    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (_size >= _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }
        new (array + _size) T(std::forward<Args>(args)...);
        _size++;
    }

    bool empty() const { return _size == 0; }
    iterator end() { return iterator(array + _size); }

    iterator erase(iterator it) {
        size_t index = it.distance(begin());
        for (size_t i = index; i < _size - 1; i++) {
            array[i] = array[i + 1];
        }
        pop_back();
        return iterator(array + index);
    }

    iterator erase(iterator start, iterator end) {
        size_t index = start.distance(begin());
        size_t count = end.distance(start);
        for (size_t i = index; i < _size - count; i++) {
            array[i] = array[i + count];
        }
        for (size_t i = 0; i < count; i++) {
            pop_back();
        }
        return iterator(array + index);
    }

    T& front() { return array[0]; }

    iterator insert(iterator it, const T& value) {
        if (_size == 0) {
            push_back(value);
            return iterator(array + 1);
        }
        size_t index = it.distance(begin());
        if (_size >= _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }
        _size++;
        for (size_t i = _size - 1; i > index; i--) {
            new (array + i) T(array[i - 1]);
            (array + i - 1)->~T();
        }
        new (array + index) T(value);
        return iterator(array + index + 1);
    }

    long long max_size() const { return INT64_MAX / sizeof(T); }

    void pop_back() {
        if (_size > 0) {
            _size--;
            (array + _size)->~T();
        }
    }

    void push_back(T value) {
        if (_size >= _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }
        new (array + _size) T(value);
        _size++;
    }

    reverseIterator rbegin() { return reverseIterator(array + _size - 1); }
    reverseIterator rend() { return reverseIterator(array - 1); }

    void reserve(size_t n) {
        if (n <= _capacity) return;
        T* temp = reinterpret_cast<T*>(new char[n * sizeof(T)]);
        for (size_t i = 0; i < _size; i++) {
            new (temp + i) T(array[i]);
            (array + i)->~T();
        }
        delete[] reinterpret_cast<char*>(array);
        array = temp;
        _capacity = n;
    }

    void resize(size_t n, const T& value = T()) {
        if (n < _size) {
            while (_size > n) pop_back();
        } else {
            if (n > _capacity) reserve(n);
            for (size_t i = _size; i < n; i++) {
                new (array + i) T(value);
            }
            _size = n;
        }
    }

    size_t size() const { return _size; }

    void swap(Vector<T>& other) {
        T* temp_arr = array;
        size_t temp_sz = _size;
        size_t temp_cp = _capacity;

        array = other.array;
        _size = other._size;
        _capacity = other._capacity;

        other.array = temp_arr;
        other._size = temp_sz;
        other._capacity = temp_cp;
    }

    T& operator[](size_t i) { return array[i]; }
    const T& operator[](size_t i) const { return array[i]; }
};

#endif