#include "bitset.h"
#include <memory>

// ==================== BitReference ====================

BitSet::BitReference::BitReference(unsigned short& block, sizeType bitMask)
    : block_(&block), bitMask_(static_cast<unsigned short>(bitMask)) {}

BitSet::BitReference& BitSet::BitReference::operator=(bool value) {
    if (value) {
        *block_ |= bitMask_;
    } else {
        *block_ &= ~bitMask_;
    }
    return *this;
}

BitSet::BitReference& BitSet::BitReference::operator=(const BitReference& other) {
    return *this = static_cast<bool>(other);
}

BitSet::BitReference::operator bool() const {
    return (*block_ & bitMask_) != 0;
}

bool BitSet::BitReference::operator~() const {
    return !static_cast<bool>(*this);
}

BitSet::BitReference& BitSet::BitReference::flip() {
    *block_ ^= bitMask_;
    return *this;
}

// ==================== BitSet ====================

BitSet::BitSet(sizeType size) 
    : size_(size), 
      numBlocks_((size + BITS_PER_BLOCK - 1) / BITS_PER_BLOCK) {
    if (size_ == 0) {
        numBlocks_ = 0;
    }
    data_ = std::make_unique<unsigned short[]>(numBlocks_ + 1);
    reset();
}

BitSet::BitSet(const BitSet& other)
    : size_(other.size_), 
      numBlocks_(other.numBlocks_) {
    data_ = std::make_unique<unsigned short[]>(numBlocks_ + 1);
    for (sizeType i = 0; i < numBlocks_; ++i) {
        data_[i] = other.data_[i];
    }
}

BitSet::BitSet(BitSet&& other) noexcept
    : data_(std::move(other.data_)), 
      size_(other.size_), 
      numBlocks_(other.numBlocks_) {
    other.size_ = 0;
    other.numBlocks_ = 0;
}

BitSet& BitSet::operator=(const BitSet& other) {
    if (this != &other) {
        if (numBlocks_ != other.numBlocks_) {
            numBlocks_ = other.numBlocks_;
            data_ = std::make_unique<unsigned short[]>(numBlocks_ + 1);
        }
        size_ = other.size_;
        for (sizeType i = 0; i < numBlocks_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    return *this;
}

BitSet& BitSet::operator=(BitSet&& other) noexcept {
    if (this != &other) {
        data_ = std::move(other.data_);
        size_ = other.size_;
        numBlocks_ = other.numBlocks_;
        other.size_ = 0;
        other.numBlocks_ = 0;
    }
    return *this;
}

BitSet::sizeType BitSet::blockIndex(sizeType pos) const {
    return pos / BITS_PER_BLOCK;
}

BitSet::sizeType BitSet::bitIndex(sizeType pos) const {
    return pos & BLOCK_MASK;
}

unsigned short BitSet::bitMask(sizeType pos) const {
    return static_cast<unsigned short>(1u << bitIndex(pos));
}

// ==================== Доступ к элементам (O(1)) ====================

bool BitSet::operator[](sizeType pos) const {
    return test(pos);
}

BitSet::BitReference BitSet::operator[](sizeType pos) {
    return BitReference(data_[blockIndex(pos)], bitMask(pos));
}

bool BitSet::test(sizeType pos) const {
    return (data_[blockIndex(pos)] & bitMask(pos)) != 0;
}

// ==================== Модификация отдельного бита (O(1)) ====================

void BitSet::set(sizeType pos) {
    data_[blockIndex(pos)] |= bitMask(pos);
}

void BitSet::reset(sizeType pos) {
    data_[blockIndex(pos)] &= ~bitMask(pos);
}

void BitSet::flip(sizeType pos) {
    data_[blockIndex(pos)] ^= bitMask(pos);
}

// ==================== Модификация всех битов (O(N/16)) ====================

void BitSet::set() {
    for (sizeType i = 0; i < numBlocks_; ++i) {
        data_[i] = ALL_ONES;
    }
    sizeType extraBits = size_ & BLOCK_MASK;
    if (extraBits != 0 && numBlocks_ > 0) {
        data_[numBlocks_ - 1] &= static_cast<unsigned short>((1u << extraBits) - 1);
    }
}

void BitSet::reset() {
    for (sizeType i = 0; i < numBlocks_; ++i) {
        data_[i] = 0;
    }
}

void BitSet::flip() {
    for (sizeType i = 0; i < numBlocks_; ++i) {
        data_[i] = ~data_[i];
    }
    sizeType extraBits = size_ & BLOCK_MASK;
    if (extraBits != 0 && numBlocks_ > 0) {
        data_[numBlocks_ - 1] &= static_cast<unsigned short>((1u << extraBits) - 1);
    }
}

// ==================== Проверки (O(N/16)) ====================

bool BitSet::all() const {
    if (size_ == 0) return true;
    
    sizeType fullBlocks = size_ / BITS_PER_BLOCK;
    
    for (sizeType i = 0; i < fullBlocks; ++i) {
        if (data_[i] != ALL_ONES) {
            return false;
        }
    }
    
    sizeType extraBits = size_ & BLOCK_MASK;
    if (extraBits != 0) {
        unsigned short mask = static_cast<unsigned short>((1u << extraBits) - 1);
        if ((data_[fullBlocks] & mask) != mask) {
            return false;
        }
    }
    
    return true;
}

bool BitSet::any() const {
    for (sizeType i = 0; i < numBlocks_; ++i) {
        if (data_[i] != 0) {
            return true;
        }
    }
    return false;
}

bool BitSet::none() const {
    return !any();
}

// ==================== Информация ====================

BitSet::sizeType BitSet::size() const {
    return size_;
}

BitSet::sizeType BitSet::count() const {
    sizeType result = 0;
    for (sizeType i = 0; i < numBlocks_; ++i) {
        unsigned short value = data_[i];
        while (value) {
            result += (value & 1u);
            value >>= 1;
        }
    }
    return result;
}

// ==================== Преобразования ====================

String BitSet::toString() const {
    String result;
    for (int i = static_cast<int>(size_) - 1; i >= 0; --i) {
        result.pushBack(test(static_cast<sizeType>(i)) ? '1' : '0');
    }
    return result;
}

unsigned long BitSet::toULong() const {
    if (size_ > sizeof(unsigned long) * 8) {
        return 0;
    }
    unsigned long result = 0;
    for (sizeType i = 0; i < size_; ++i) {
        if (test(i)) {
            result |= (1ul << i);
        }
    }
    return result;
}

unsigned long long BitSet::toULongLong() const {
    if (size_ > sizeof(unsigned long long) * 8) {
        return 0;
    }
    unsigned long long result = 0;
    for (sizeType i = 0; i < size_; ++i) {
        if (test(i)) {
            result |= (1ull << i);
        }
    }
    return result;
}

// ==================== Логические операции (O(N/16)) ====================

BitSet BitSet::operator~() const {
    BitSet result(*this);
    result.flip();
    return result;
}

BitSet BitSet::operator&(const BitSet& other) const {
    BitSet result(*this);
    result &= other;
    return result;
}

BitSet BitSet::operator|(const BitSet& other) const {
    BitSet result(*this);
    result |= other;
    return result;
}

BitSet BitSet::operator^(const BitSet& other) const {
    BitSet result(*this);
    result ^= other;
    return result;
}

BitSet& BitSet::operator&=(const BitSet& other) {
    sizeType minBlocks = (numBlocks_ < other.numBlocks_) ? numBlocks_ : other.numBlocks_;
    for (sizeType i = 0; i < minBlocks; ++i) {
        data_[i] &= other.data_[i];
    }
    for (sizeType i = minBlocks; i < numBlocks_; ++i) {
        data_[i] = 0;
    }
    return *this;
}

BitSet& BitSet::operator|=(const BitSet& other) {
    sizeType minBlocks = (numBlocks_ < other.numBlocks_) ? numBlocks_ : other.numBlocks_;
    for (sizeType i = 0; i < minBlocks; ++i) {
        data_[i] |= other.data_[i];
    }
    return *this;
}

BitSet& BitSet::operator^=(const BitSet& other) {
    sizeType minBlocks = (numBlocks_ < other.numBlocks_) ? numBlocks_ : other.numBlocks_;
    for (sizeType i = 0; i < minBlocks; ++i) {
        data_[i] ^= other.data_[i];
    }
    return *this;
}

// ==================== Сравнение ====================

bool BitSet::operator==(const BitSet& other) const {
    if (size_ != other.size_) return false;
    for (sizeType i = 0; i < numBlocks_; ++i) {
        if (data_[i] != other.data_[i]) return false;
    }
    return true;
}

bool BitSet::operator!=(const BitSet& other) const {
    return !(*this == other);
}

// ==================== Сдвиги (O(N/16)) ====================

BitSet BitSet::operator<<(sizeType pos) const {
    BitSet result(*this);
    result <<= pos;
    return result;
}

BitSet BitSet::operator>>(sizeType pos) const {
    BitSet result(*this);
    result >>= pos;
    return result;
}

BitSet& BitSet::operator<<=(sizeType pos) {
    if (pos >= size_) {
        reset();
        return *this;
    }
    
    sizeType blockShift = pos / BITS_PER_BLOCK;
    sizeType bitShift = pos & BLOCK_MASK;
    
    for (int i = static_cast<int>(numBlocks_) - 1; i >= 0; --i) {
        sizeType srcIdx = static_cast<sizeType>(i) - blockShift;
        unsigned short newValue = 0;
        
        if (srcIdx < numBlocks_) {
            newValue = data_[srcIdx] << bitShift;
            if (bitShift != 0 && srcIdx > 0) {
                newValue |= data_[srcIdx - 1] >> (BITS_PER_BLOCK - bitShift);
            }
        }
        
        data_[static_cast<sizeType>(i)] = newValue;
    }
    
    for (sizeType i = 0; i < blockShift && i < numBlocks_; ++i) {
        data_[i] = 0;
    }
    
    sizeType extraBits = size_ & BLOCK_MASK;
    if (extraBits != 0 && numBlocks_ > 0) {
        data_[numBlocks_ - 1] &= static_cast<unsigned short>((1u << extraBits) - 1);
    }
    
    return *this;
}

BitSet& BitSet::operator>>=(sizeType pos) {
    if (pos >= size_) {
        reset();
        return *this;
    }
    
    sizeType blockShift = pos / BITS_PER_BLOCK;
    sizeType bitShift = pos & BLOCK_MASK;
    
    for (sizeType i = 0; i < numBlocks_; ++i) {
        sizeType srcIdx = i + blockShift;
        unsigned short newValue = 0;
        
        if (srcIdx < numBlocks_) {
            newValue = data_[srcIdx] >> bitShift;
            if (bitShift != 0 && srcIdx + 1 < numBlocks_) {
                newValue |= data_[srcIdx + 1] << (BITS_PER_BLOCK - bitShift);
            }
        }
        
        data_[i] = newValue;
    }
    
    for (sizeType i = numBlocks_ - blockShift; i < numBlocks_; ++i) {
        data_[i] = 0;
    }
    
    return *this;
}