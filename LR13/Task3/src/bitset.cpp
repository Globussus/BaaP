#include "bitset.h"

BitSet::BitReference::BitReference(unsigned short& block, SizeType bitMask)
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

BitSet::BitSet(SizeType size)
    : size_(size), numBlocks_((size + kBitsPerBlock - 1) / kBitsPerBlock) {
    if (size_ == 0) {
        numBlocks_ = 0;
    }
    data_ = std::make_unique<unsigned short[]>(numBlocks_ + 1);
    reset();
}

BitSet::BitSet(const BitSet& other)
    : size_(other.size_), numBlocks_(other.numBlocks_) {
    data_ = std::make_unique<unsigned short[]>(numBlocks_ + 1);
    for (SizeType i = 0; i < numBlocks_; ++i) {
        data_[i] = other.data_[i];
    }
}

BitSet::BitSet(BitSet&& other) noexcept
    : data_(std::move(other.data_)), size_(other.size_), numBlocks_(other.numBlocks_) {
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
        for (SizeType i = 0; i < numBlocks_; ++i) {
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

BitSet::SizeType BitSet::blockIndex(SizeType pos) const {
    return pos / kBitsPerBlock;
}

BitSet::SizeType BitSet::bitIndex(SizeType pos) const {
    return pos & kBlockMask;
}

unsigned short BitSet::bitMask(SizeType pos) const {
    return static_cast<unsigned short>(1u << bitIndex(pos));
}

bool BitSet::operator[](SizeType pos) const {
    return test(pos);
}

BitSet::BitReference BitSet::operator[](SizeType pos) {
    return BitReference(data_[blockIndex(pos)], bitMask(pos));
}

bool BitSet::test(SizeType pos) const {
    return (data_[blockIndex(pos)] & bitMask(pos)) != 0;
}

void BitSet::set(SizeType pos) {
    data_[blockIndex(pos)] |= bitMask(pos);
}

void BitSet::reset(SizeType pos) {
    data_[blockIndex(pos)] &= ~bitMask(pos);
}

void BitSet::flip(SizeType pos) {
    data_[blockIndex(pos)] ^= bitMask(pos);
}

void BitSet::set() {
    for (SizeType i = 0; i < numBlocks_; ++i) {
        data_[i] = kAllOnes;
    }
    SizeType extraBits = size_ & kBlockMask;
    if (extraBits != 0 && numBlocks_ > 0) {
        data_[numBlocks_ - 1] &= static_cast<unsigned short>((1u << extraBits) - 1);
    }
}

void BitSet::reset() {
    for (SizeType i = 0; i < numBlocks_; ++i) {
        data_[i] = 0;
    }
}

void BitSet::flip() {
    for (SizeType i = 0; i < numBlocks_; ++i) {
        data_[i] = ~data_[i];
    }
    SizeType extraBits = size_ & kBlockMask;
    if (extraBits != 0 && numBlocks_ > 0) {
        data_[numBlocks_ - 1] &= static_cast<unsigned short>((1u << extraBits) - 1);
    }
}

bool BitSet::all() const {
    if (size_ == 0) {
        return true;
    }

    SizeType fullBlocks = size_ / kBitsPerBlock;
    for (SizeType i = 0; i < fullBlocks; ++i) {
        if (data_[i] != kAllOnes) {
            return false;
        }
    }

    SizeType extraBits = size_ & kBlockMask;
    if (extraBits != 0) {
        unsigned short mask = static_cast<unsigned short>((1u << extraBits) - 1);
        if ((data_[fullBlocks] & mask) != mask) {
            return false;
        }
    }

    return true;
}

bool BitSet::any() const {
    for (SizeType i = 0; i < numBlocks_; ++i) {
        if (data_[i] != 0) {
            return true;
        }
    }
    return false;
}

bool BitSet::none() const {
    return !any();
}

BitSet::SizeType BitSet::size() const {
    return size_;
}

BitSet::SizeType BitSet::count() const {
    SizeType result = 0;
    for (SizeType i = 0; i < numBlocks_; ++i) {
        unsigned short value = data_[i];
        while (value) {
            result += (value & 1u);
            value >>= 1;
        }
    }
    return result;
}

String BitSet::toString() const {
    String result;
    for (int i = static_cast<int>(size_) - 1; i >= 0; --i) {
        result.pushBack(test(static_cast<SizeType>(i)) ? '1' : '0');
    }
    return result;
}

unsigned long BitSet::toULong() const {
    if (size_ > sizeof(unsigned long) * 8) {
        return 0;
    }
    unsigned long result = 0;
    for (SizeType i = 0; i < size_; ++i) {
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
    for (SizeType i = 0; i < size_; ++i) {
        if (test(i)) {
            result |= (1ull << i);
        }
    }
    return result;
}

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
    SizeType minBlocks = (numBlocks_ < other.numBlocks_) ? numBlocks_ : other.numBlocks_;
    for (SizeType i = 0; i < minBlocks; ++i) {
        data_[i] &= other.data_[i];
    }
    for (SizeType i = minBlocks; i < numBlocks_; ++i) {
        data_[i] = 0;
    }
    return *this;
}

BitSet& BitSet::operator|=(const BitSet& other) {
    SizeType minBlocks = (numBlocks_ < other.numBlocks_) ? numBlocks_ : other.numBlocks_;
    for (SizeType i = 0; i < minBlocks; ++i) {
        data_[i] |= other.data_[i];
    }
    return *this;
}

BitSet& BitSet::operator^=(const BitSet& other) {
    SizeType minBlocks = (numBlocks_ < other.numBlocks_) ? numBlocks_ : other.numBlocks_;
    for (SizeType i = 0; i < minBlocks; ++i) {
        data_[i] ^= other.data_[i];
    }
    return *this;
}

bool BitSet::operator==(const BitSet& other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (SizeType i = 0; i < numBlocks_; ++i) {
        if (data_[i] != other.data_[i]) {
            return false;
        }
    }
    return true;
}

bool BitSet::operator!=(const BitSet& other) const {
    return !(*this == other);
}

BitSet BitSet::operator<<(SizeType pos) const {
    BitSet result(*this);
    result <<= pos;
    return result;
}

BitSet BitSet::operator>>(SizeType pos) const {
    BitSet result(*this);
    result >>= pos;
    return result;
}

BitSet& BitSet::operator<<=(SizeType pos) {
    if (pos >= size_) {
        reset();
        return *this;
    }

    SizeType blockShift = pos / kBitsPerBlock;
    SizeType bitShift = pos & kBlockMask;

    for (int i = static_cast<int>(numBlocks_) - 1; i >= 0; --i) {
        SizeType srcIdx = static_cast<SizeType>(i) - blockShift;
        unsigned short newValue = 0;

        if (srcIdx < numBlocks_) {
            newValue = data_[srcIdx] << bitShift;
            if (bitShift != 0 && srcIdx > 0) {
                newValue |= data_[srcIdx - 1] >> (kBitsPerBlock - bitShift);
            }
        }

        data_[static_cast<SizeType>(i)] = newValue;
    }

    SizeType extraBits = size_ & kBlockMask;
    if (extraBits != 0 && numBlocks_ > 0) {
        data_[numBlocks_ - 1] &= static_cast<unsigned short>((1u << extraBits) - 1);
    }

    return *this;
}

BitSet& BitSet::operator>>=(SizeType pos) {
    if (pos >= size_) {
        reset();
        return *this;
    }

    SizeType blockShift = pos / kBitsPerBlock;
    SizeType bitShift = pos & kBlockMask;

    for (SizeType i = 0; i < numBlocks_; ++i) {
        SizeType srcIdx = i + blockShift;
        unsigned short newValue = 0;

        if (srcIdx < numBlocks_) {
            newValue = data_[srcIdx] >> bitShift;
            if (bitShift != 0 && srcIdx + 1 < numBlocks_) {
                newValue |= data_[srcIdx + 1] << (kBitsPerBlock - bitShift);
            }
        }

        data_[i] = newValue;
    }

    for (SizeType i = numBlocks_ - blockShift; i < numBlocks_; ++i) {
        data_[i] = 0;
    }

    SizeType extraBits = size_ & kBlockMask;
    if (extraBits != 0 && numBlocks_ > 0) {
        data_[numBlocks_ - 1] &= static_cast<unsigned short>((1u << extraBits) - 1);
    }

    return *this;
}