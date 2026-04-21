#include "myString.h"

String::String() : data_(std::make_unique<char[]>(1)), size_(0), capacity_(0) {
    data_[0] = '\0';
}

String::String(sizeType size) : data_(std::make_unique<char[]>(size + 1)), size_(size), capacity_(size) {
    memorySet(data_.get(), '\0', size + 1);
}

String::String(const String& other) : data_(std::make_unique<char[]>(other.capacity_ + 1)), size_(other.size_), capacity_(other.capacity_) {
    stringCopy(data_.get(), other.data_.get());
}

String::String(String&& other) noexcept : data_(std::move(other.data_)), size_(other.size_), capacity_(other.capacity_) {
    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = std::make_unique<char[]>(1);
    other.data_[0] = '\0';
}

String::String(std::initializer_list<char> list) : data_(std::make_unique<char[]>(list.size() + 1)), size_(list.size()), capacity_(list.size()) {
    sizeType i = 0;
    for (char ch : list) {
        data_[i++] = ch;
    }
    data_[size_] = '\0';
}

String::String(const char* cStr) {
    if (cStr) {
        size_ = stringLength(cStr);
        capacity_ = size_;
        data_ = std::make_unique<char[]>(capacity_ + 1);
        stringCopy(data_.get(), cStr);
    } else {
        size_ = 0;
        capacity_ = 0;
        data_ = std::make_unique<char[]>(1);
        data_[0] = '\0';
    }
}

String& String::operator=(const char* cStr) {
    sizeType len = cStr ? stringLength(cStr) : 0;
    if (len > capacity_) {
        reallocate(len);
    }
    size_ = len;
    if (cStr) {
        stringCopy(data_.get(), cStr);
    } else {
        data_[0] = '\0';
    }
    return *this;
}

String& String::operator=(const String& other) {
    if (this != &other) {
        if (other.size_ > capacity_) {
            reallocate(other.size_);
        }
        size_ = other.size_;
        stringCopy(data_.get(), other.data_.get());
    }
    return *this;
}

String& String::operator=(String&& other) noexcept {
    if (this != &other) {
        data_ = std::move(other.data_);
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.size_ = 0;
        other.capacity_ = 0;
        other.data_ = std::make_unique<char[]>(1);
        other.data_[0] = '\0';
    }
    return *this;
}

String String::operator+(const String& other) const {
    String result(size_ + other.size_);
    stringCopy(result.data_.get(), data_.get());
    stringConcat(result.data_.get(), other.data_.get());
    return result;
}

String& String::operator+=(const String& other) {
    if (size_ + other.size_ > capacity_) {
        reallocate(size_ + other.size_);
    }
    stringConcat(data_.get(), other.data_.get());
    size_ += other.size_;
    return *this;
}

String& String::operator+=(const char* cStr) {
    if (!cStr) return *this;
    sizeType len = stringLength(cStr);
    if (size_ + len > capacity_) {
        reallocate(size_ + len);
    }
    stringConcat(data_.get(), cStr);
    size_ += len;
    return *this;
}

String& String::operator+=(char ch) {
    pushBack(ch);
    return *this;
}

char& String::operator[](sizeType index) {
    return data_[index];
}

const char& String::operator[](sizeType index) const {
    return data_[index];
}

char& String::at(sizeType pos) {
    if (pos >= size_) throw std::out_of_range("Index out of range");
    return data_[pos];
}

const char& String::at(sizeType pos) const {
    if (pos >= size_) throw std::out_of_range("Index out of range");
    return data_[pos];
}

char& String::front() {
    return data_[0];
}

const char& String::front() const {
    return data_[0];
}

char& String::back() {
    return data_[size_ - 1];
}

const char& String::back() const {
    return data_[size_ - 1];
}

char* String::data() {
    return data_.get();
}

const char* String::data() const {
    return data_.get();
}

const char* String::cStr() const {
    return data_.get();
}

String::sizeType String::size() const {
    return size_;
}

String::sizeType String::length() const {
    return size_;
}

String::sizeType String::capacity() const {
    return capacity_;
}

bool String::empty() const {
    return size_ == 0;
}

void String::reserve(sizeType newCapacity) {
    if (newCapacity > capacity_) {
        reallocate(newCapacity);
    }
}

void String::shrinkToFit() {
    if (capacity_ > size_) {
        reallocate(size_);
    }
}

void String::clear() {
    size_ = 0;
    data_[0] = '\0';
}

void String::pushBack(char value) {
    if (size_ == capacity_) {
        reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_++] = value;
    data_[size_] = '\0';
}

void String::popBack() {
    if (size_ > 0) {
        data_[--size_] = '\0';
    }
}

void String::resize(sizeType newSize, char value) {
    if (newSize > capacity_) {
        reallocate(newSize);
    }
    if (newSize > size_) {
        memorySet(data_.get() + size_, value, newSize - size_);
    }
    size_ = newSize;
    data_[size_] = '\0';
}

void String::reallocate(sizeType newCapacity) {
    auto newData = std::make_unique<char[]>(newCapacity + 1);
    if (size_ > 0) {
        memoryCopy(newData.get(), data_.get(), size_ + 1);
    } else {
        newData[0] = '\0';
    }
    data_ = std::move(newData);
    capacity_ = newCapacity;
}

String::iterator String::begin() {
    return iterator(data_.get());
}

String::iterator String::end() {
    return iterator(data_.get() + size_);
}

String::reverseIterator String::rbegin() {
    return reverseIterator(data_.get() + size_ - 1);
}

String::reverseIterator String::rend() {
    return reverseIterator(data_.get() - 1);
}

void* String::memoryCopy(void* dest, const void* src, sizeType n) {
    char* d = static_cast<char*>(dest);
    const char* s = static_cast<const char*>(src);
    for (sizeType i = 0; i < n; ++i) {
        d[i] = s[i];
    }
    return dest;
}

void* String::memoryMove(void* dest, const void* src, sizeType n) {
    char* d = static_cast<char*>(dest);
    const char* s = static_cast<const char*>(src);
    if (d < s) {
        for (sizeType i = 0; i < n; ++i) {
            d[i] = s[i];
        }
    } else if (d > s) {
        for (sizeType i = n; i > 0; --i) {
            d[i - 1] = s[i - 1];
        }
    }
    return dest;
}

char* String::stringCopy(char* dest, const char* src) {
    char* originalDest = dest;
    while ((*dest++ = *src++) != '\0') {}
    return originalDest;
}

char* String::stringCopyN(char* dest, const char* src, sizeType n) {
    char* originalDest = dest;
    sizeType i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    for (; i < n; i++) {
        dest[i] = '\0';
    }
    return originalDest;
}

char* String::stringConcat(char* dest, const char* src) {
    char* originalDest = dest;
    while (*dest) {
        dest++;
    }
    while ((*dest++ = *src++) != '\0') {}
    return originalDest;
}

char* String::stringConcatN(char* dest, const char* src, sizeType n) {
    char* originalDest = dest;
    while (*dest) {
        dest++;
    }
    while (n-- && (*dest++ = *src++) != '\0') {}
    *dest = '\0';
    return originalDest;
}

int String::memoryCompare(const void* s1, const void* s2, sizeType n) {
    const unsigned char* p1 = static_cast<const unsigned char*>(s1);
    const unsigned char* p2 = static_cast<const unsigned char*>(s2);
    for (sizeType i = 0; i < n; ++i) {
        if (p1[i] != p2[i]) {
            return p1[i] < p2[i] ? -1 : 1;
        }
    }
    return 0;
}

int String::stringCompare(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

int String::stringCompareN(const char* s1, const char* s2, sizeType n) {
    if (n == 0) return 0;
    while (--n && *s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

int String::stringCollate(const char* s1, const char* s2) {
    return stringCompare(s1, s2);
}

String::sizeType String::transformString(char* dest, const char* src, sizeType n) {
    sizeType len = stringLength(src);
    if (n > 0) {
        stringCopyN(dest, src, n);
    }
    return len;
}

char* String::stringTokenize(char* str, const char* delimiters) {
    static char* nextToken = nullptr;
    if (str) nextToken = str;
    if (!nextToken) return nullptr;

    while (*nextToken) {
        bool isDelimiter = false;
        for (const char* d = delimiters; *d; ++d) {
            if (*nextToken == *d) {
                isDelimiter = true;
                break;
            }
        }
        if (!isDelimiter) break;
        nextToken++;
    }

    if (!*nextToken) return nullptr;

    char* tokenStart = nextToken;
    while (*nextToken) {
        bool isDelimiter = false;
        for (const char* d = delimiters; *d; ++d) {
            if (*nextToken == *d) {
                isDelimiter = true;
                break;
            }
        }
        if (isDelimiter) {
            *nextToken++ = '\0';
            break;
        }
        nextToken++;
    }
    return tokenStart;
}

void* String::memorySet(void* ptr, int value, sizeType n) {
    unsigned char* p = static_cast<unsigned char*>(ptr);
    for (sizeType i = 0; i < n; ++i) {
        p[i] = static_cast<unsigned char>(value);
    }
    return ptr;
}

const char* String::errorString(int errorNum) {
    switch (errorNum) {
        case 1: return "Operation not permitted";
        case 2: return "No such file or directory";
        case 3: return "No such process";
        default: return "Unknown error";
    }
}

String::sizeType String::stringLength(const char* s) {
    sizeType len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

char* String::stringTokenize_r(char* str, const char* delimiters, char** saveptr) {
    char* nextToken;
    
    if (str) {
        nextToken = str;
    } else {
        nextToken = *saveptr;
    }
    
    if (!nextToken) {
        *saveptr = nullptr;
        return nullptr;
    }

    // Пропускаем начальные разделители
    while (*nextToken) {
        bool isDelimiter = false;
        for (const char* d = delimiters; *d; ++d) {
            if (*nextToken == *d) {
                isDelimiter = true;
                break;
            }
        }
        if (!isDelimiter) break;
        nextToken++;
    }

    if (!*nextToken) {
        *saveptr = nullptr;
        return nullptr;
    }

    char* tokenStart = nextToken;
    while (*nextToken) {
        bool isDelimiter = false;
        for (const char* d = delimiters; *d; ++d) {
            if (*nextToken == *d) {
                isDelimiter = true;
                break;
            }
        }
        if (isDelimiter) {
            *nextToken++ = '\0';
            break;
        }
        nextToken++;
    }
    
    // Сохраняем позицию для следующего вызова
    if (*nextToken) {
        *saveptr = nextToken;
    } else {
        *saveptr = nullptr;
    }
    
    return tokenStart;
}