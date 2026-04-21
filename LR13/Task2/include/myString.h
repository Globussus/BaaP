#ifndef STRING_H
#define STRING_H

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <initializer_list>

#include "iterator.h"
#include "reverseIterator.h"

class String {
public:
    using iterator = Iterator;
    using constIterator = Iterator;
    using reverseIterator = ReverseIterator;
    using constReverseIterator = ReverseIterator;
    using sizeType = std::size_t;
    using charType = char;

    static constexpr sizeType npos = static_cast<sizeType>(-1);

    String();
    explicit String(sizeType size);
    String(const String& other);
    String(String&& other) noexcept;
    String(std::initializer_list<char> list);
    String(const char* cStr);
    ~String() = default;

    String& operator=(const char* cStr);
    String& operator=(const String& other);
    String& operator=(String&& other) noexcept;

    String operator+(const String& other) const;
    String& operator+=(const String& other);
    String& operator+=(const char* cStr);
    String& operator+=(char ch);

    char& operator[](sizeType index);
    const char& operator[](sizeType index) const;
    char& at(sizeType pos);
    const char& at(sizeType pos) const;
    char& front();
    const char& front() const;
    char& back();
    const char& back() const;
    
    char* data();
    const char* data() const;
    const char* cStr() const;

    sizeType size() const;
    sizeType length() const;
    sizeType capacity() const;
    bool empty() const;
    
    void reserve(sizeType newCapacity);
    void shrinkToFit();
    void clear();
    void pushBack(char value);
    void popBack();
    void resize(sizeType newSize, char value = '\0');

    iterator begin();
    iterator end();
    reverseIterator rbegin();
    reverseIterator rend();

    static void* memoryCopy(void* dest, const void* src, sizeType n);
    static void* memoryMove(void* dest, const void* src, sizeType n);
    static char* stringCopy(char* dest, const char* src);
    static char* stringCopyN(char* dest, const char* src, sizeType n);
    static char* stringConcat(char* dest, const char* src);
    static char* stringConcatN(char* dest, const char* src, sizeType n);
    static int memoryCompare(const void* s1, const void* s2, sizeType n);
    static int stringCompare(const char* s1, const char* s2);
    static int stringCompareN(const char* s1, const char* s2, sizeType n);
    static int stringCollate(const char* s1, const char* s2);
    static sizeType transformString(char* dest, const char* src, sizeType n);
    static char* stringTokenize(char* str, const char* delimiters);
    static void* memorySet(void* ptr, int value, sizeType n);
    static const char* errorString(int errorNum);
    static sizeType stringLength(const char* s);

    static char* stringTokenize_r(char* str, const char* delimiters, char** saveptr);

private:
    std::unique_ptr<char[]> data_;
    sizeType size_;
    sizeType capacity_;

    void reallocate(sizeType newCapacity);
};

#endif 