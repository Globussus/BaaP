#ifndef BITSET_H
#define BITSET_H

#include <cstddef>
#include <memory>
#include "./../../Task2/include/myString.h"

class BitSet {
public:
    using SizeType = std::size_t;

    class BitReference {
    public:
        BitReference(unsigned short& block, SizeType bitMask);
        BitReference& operator=(bool value);
        BitReference& operator=(const BitReference& other);
        operator bool() const;
        bool operator~() const;
        BitReference& flip();

    private:
        unsigned short* block_;
        unsigned short bitMask_;
    };

    explicit BitSet(SizeType size);
    BitSet(const BitSet& other);
    BitSet(BitSet&& other) noexcept;
    BitSet& operator=(const BitSet& other);
    BitSet& operator=(BitSet&& other) noexcept;
    ~BitSet() = default;

    bool operator[](SizeType pos) const;
    BitReference operator[](SizeType pos);

    bool test(SizeType pos) const;
    void set(SizeType pos);
    void reset(SizeType pos);
    void flip(SizeType pos);
    void set();
    void reset();
    void flip();

    bool all() const;
    bool any() const;
    bool none() const;
    SizeType size() const;
    SizeType count() const;
    String toString() const;
    unsigned long toULong() const;
    unsigned long long toULongLong() const;

    BitSet operator~() const;
    BitSet operator&(const BitSet& other) const;
    BitSet operator|(const BitSet& other) const;
    BitSet operator^(const BitSet& other) const;
    BitSet& operator&=(const BitSet& other);
    BitSet& operator|=(const BitSet& other);
    BitSet& operator^=(const BitSet& other);

    bool operator==(const BitSet& other) const;
    bool operator!=(const BitSet& other) const;

    BitSet operator<<(SizeType pos) const;
    BitSet operator>>(SizeType pos) const;
    BitSet& operator<<=(SizeType pos);
    BitSet& operator>>=(SizeType pos);

private:
    static constexpr int kBitsPerBlock = 16;
    static constexpr int kBlockMask = kBitsPerBlock - 1;
    static constexpr unsigned short kAllOnes = 0xFFFF;

    SizeType size_;
    SizeType numBlocks_;
    std::unique_ptr<unsigned short[]> data_;

    SizeType blockIndex(SizeType pos) const;
    SizeType bitIndex(SizeType pos) const;
    unsigned short bitMask(SizeType pos) const;
};

#endif 