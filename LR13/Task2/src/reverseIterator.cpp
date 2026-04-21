#include "reverseIterator.h"

ReverseIterator::ReverseIterator() : ptr_(nullptr) {}

ReverseIterator::ReverseIterator(pointer ptr) : ptr_(ptr) {}

ReverseIterator::reference ReverseIterator::operator*() const {
    return *ptr_;
}

ReverseIterator::pointer ReverseIterator::operator->() {
    return ptr_;
}

ReverseIterator& ReverseIterator::operator++() {
    --ptr_;
    return *this;
}

ReverseIterator ReverseIterator::operator++(int) {
    ReverseIterator temp = *this;
    --ptr_;
    return temp;
}

ReverseIterator& ReverseIterator::operator--() {
    ++ptr_;
    return *this;
}

ReverseIterator ReverseIterator::operator--(int) {
    ReverseIterator temp = *this;
    ++ptr_;
    return temp;
}

ReverseIterator ReverseIterator::operator+(differenceType n) const {
    return ReverseIterator(ptr_ - n);
}

ReverseIterator ReverseIterator::operator-(differenceType n) const {
    return ReverseIterator(ptr_ + n);
}

ReverseIterator::differenceType ReverseIterator::operator-(const ReverseIterator& other) const {
    return other.ptr_ - ptr_;
}

ReverseIterator& ReverseIterator::operator+=(differenceType n) {
    ptr_ -= n;
    return *this;
}

ReverseIterator& ReverseIterator::operator-=(differenceType n) {
    ptr_ += n;
    return *this;
}

bool ReverseIterator::operator==(const ReverseIterator& other) const {
    return ptr_ == other.ptr_;
}

bool ReverseIterator::operator!=(const ReverseIterator& other) const {
    return ptr_ != other.ptr_;
}