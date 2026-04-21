#ifndef BITSET_H
#define BITSET_H

#include "./../../Task2/include/myString.h"

class BitSet {
public:
    using sizeType = std::size_t;
    
    // Прокси-класс для operator[]
    class BitReference {
    public:
        BitReference(unsigned short& block, sizeType bitMask);
        
        BitReference& operator=(bool value);
        BitReference& operator=(const BitReference& other);
        
        operator bool() const;
        bool operator~() const;
        
        BitReference& flip();
        
    private:
        unsigned short* block_;
        sizeType bitMask_;
    };
    
    // Конструкторы
    explicit BitSet(sizeType size);
    BitSet(const BitSet& other);
    BitSet(BitSet&& other) noexcept;
    ~BitSet() = default;
    
    BitSet& operator=(const BitSet& other);
    BitSet& operator=(BitSet&& other) noexcept;
    
    // Доступ к элементам
    bool operator[](sizeType pos) const;
    BitReference operator[](sizeType pos);
    
    // Модификация отдельного бита — O(1)
    void set(sizeType pos);
    void reset(sizeType pos);
    void flip(sizeType pos);
    bool test(sizeType pos) const;
    
    // Модификация всех битов — O(N/16)
    void set();
    void reset();
    void flip();
    
    // Проверки — O(N/16)
    bool all() const;
    bool any() const;
    bool none() const;
    
    // Информация — O(1)
    sizeType count() const;
    sizeType size() const;
    
    // Преобразования
    String toString() const;
    unsigned long toULong() const;
    unsigned long long toULongLong() const;
    
    // Логические операции — O(N/16)
    BitSet operator~() const;
    BitSet operator&(const BitSet& other) const;
    BitSet operator|(const BitSet& other) const;
    BitSet operator^(const BitSet& other) const;
    
    BitSet& operator&=(const BitSet& other);
    BitSet& operator|=(const BitSet& other);
    BitSet& operator^=(const BitSet& other);
    
    // Сравнение
    bool operator==(const BitSet& other) const;
    bool operator!=(const BitSet& other) const;
    
    // Сдвиги — O(N/16)
    BitSet operator<<(sizeType pos) const;
    BitSet operator>>(sizeType pos) const;
    BitSet& operator<<=(sizeType pos);
    BitSet& operator>>=(sizeType pos);

private:
    static constexpr sizeType BITS_PER_BLOCK = 16;
    static constexpr sizeType BLOCK_MASK = BITS_PER_BLOCK - 1;
    static constexpr unsigned short ALL_ONES = static_cast<unsigned short>(-1);
    
    std::unique_ptr<unsigned short[]> data_;
    sizeType size_;
    sizeType numBlocks_;
    
    sizeType blockIndex(sizeType pos) const;
    sizeType bitIndex(sizeType pos) const;
    unsigned short bitMask(sizeType pos) const;
};

#endif 