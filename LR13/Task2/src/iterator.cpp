#include "iterator.h"

Iterator::Iterator() : ptr_(nullptr) {}

Iterator::Iterator(pointer ptr) : ptr_(ptr) {}

Iterator::reference Iterator::operator*() const {
    return *ptr_;
}

Iterator::pointer Iterator::operator->() {
    return ptr_;
}

Iterator& Iterator::operator++() {
    ++ptr_;
    return *this;
}

Iterator Iterator::operator++(int) {
    Iterator temp = *this;
    ++ptr_;
    return temp;
}

Iterator& Iterator::operator--() {
    --ptr_;
    return *this;
}

Iterator Iterator::operator--(int) {
    Iterator temp = *this;
    --ptr_;
    return temp;
}

Iterator Iterator::operator+(differenceType n) const {
    return Iterator(ptr_ + n);
}

Iterator Iterator::operator-(differenceType n) const {
    return Iterator(ptr_ - n);
}

Iterator::differenceType Iterator::operator-(const Iterator& other) const {
    return ptr_ - other.ptr_;
}

Iterator& Iterator::operator+=(differenceType n) {
    ptr_ += n;
    return *this;
}

Iterator& Iterator::operator-=(differenceType n) {
    ptr_ -= n;
    return *this;
}

bool Iterator::operator==(const Iterator& other) const {
    return ptr_ == other.ptr_;
}

bool Iterator::operator!=(const Iterator& other) const {
    return ptr_ != other.ptr_;
}

bool Iterator::operator<(const Iterator& other) const {
    return ptr_ < other.ptr_;
}

bool Iterator::operator<=(const Iterator& other) const {
    return ptr_ <= other.ptr_;
}

bool Iterator::operator>(const Iterator& other) const {
    return ptr_ > other.ptr_;
}

bool Iterator::operator>=(const Iterator& other) const {
    return ptr_ >= other.ptr_;
}