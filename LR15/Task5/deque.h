#ifndef DEQUE_H
#define DEQUE_H

#include <cstddef>
#include <utility>
#include <stdexcept>

template <typename T>
class Deque {
    friend class InspectorGadget;

private:
    static const size_t INI_BLOCKS = 4;
    static const size_t BLOCK_SIZE = 4;

    struct Block {
        T els[BLOCK_SIZE];
    };

    // Вспомогательные методы для работы с блоками
    void incrementPointer(size_t& blockIdx, size_t& pos) const {
        pos++;
        if (pos == BLOCK_SIZE) {
            pos = 0;
            blockIdx = (blockIdx + 1) % blocks_count;
        }
    }

    void decrementPointer(size_t& blockIdx, size_t& pos) const {
        if (pos == 0) {
            blockIdx = (blockIdx == 0) ? blocks_count - 1 : blockIdx - 1;
            pos = BLOCK_SIZE - 1;
        } else {
            pos--;
        }
    }

    void init(size_t count) {
        blocks_count = count;
        blocks = new Block*[count];
        for (size_t i = 0; i < count; i++) {
            blocks[i] = (Block*)new unsigned char[sizeof(Block)];
        }

        beginBlock = 0;
        beginPos = 0;
        endBlock = 0;
        endPos = 0;
    }

public:
    Deque() { init(INI_BLOCKS); }

    ~Deque() {
        clear();
        for (size_t i = 0; i < blocks_count; i++) {
            delete[] (unsigned char*)blocks[i];
        }
        delete[] blocks;
    }

    Deque(const Deque& d) {
        init(d.blocks_count);
        for (size_t i = 0; i < d.size(); i++) {
            push_back(d[i]);
        }
    }

    Deque& operator=(const Deque& d) {
        if (this == &d) return *this;
        clear();
        for (size_t i = 0; i < d.size(); i++) {
            push_back(d[i]);
        }
        return *this;
    }

    Deque(Deque&& d) noexcept {
        blocks_count = d.blocks_count;
        blocks = d.blocks;
        beginBlock = d.beginBlock;
        beginPos = d.beginPos;
        endBlock = d.endBlock;
        endPos = d.endPos;

        d.blocks = nullptr;
        d.init(INI_BLOCKS);
    }

    Deque& operator=(Deque&& d) noexcept {
        if (this == &d) return *this;
        
        clear();
        for (size_t i = 0; i < blocks_count; i++) {
            delete[] (unsigned char*)blocks[i];
        }
        delete[] blocks;

        blocks_count = d.blocks_count;
        blocks = d.blocks;
        beginBlock = d.beginBlock;
        beginPos = d.beginPos;
        endBlock = d.endBlock;
        endPos = d.endPos;

        d.blocks = nullptr;
        d.init(INI_BLOCKS);

        return *this;
    }

    // Random access
    T& at(size_t i) {
        if (i >= size()) {
            throw std::out_of_range("Index out of range");
        }
        size_t totalPos = beginBlock * BLOCK_SIZE + beginPos + i;
        size_t blockIdx = (totalPos / BLOCK_SIZE) % blocks_count;
        size_t pos = totalPos % BLOCK_SIZE;
        return blocks[blockIdx]->els[pos];
    }

    const T& at(size_t i) const {
        if (i >= size()) {
            throw std::out_of_range("Index out of range");
        }
        size_t totalPos = beginBlock * BLOCK_SIZE + beginPos + i;
        size_t blockIdx = (totalPos / BLOCK_SIZE) % blocks_count;
        size_t pos = totalPos % BLOCK_SIZE;
        return blocks[blockIdx]->els[pos];
    }

    T& operator[](size_t i) { return at(i); }
    const T& operator[](size_t i) const { return at(i); }

    T& front() {
        if (empty()) throw std::underflow_error("Deque is empty!");
        return blocks[beginBlock]->els[beginPos];
    }

    const T& front() const {
        if (empty()) throw std::underflow_error("Deque is empty!");
        return blocks[beginBlock]->els[beginPos];
    }

    T& back() {
        if (empty()) throw std::underflow_error("Deque is empty!");
        size_t lastBlock = endBlock;
        size_t lastPos = endPos;
        decrementPointer(lastBlock, lastPos);
        return blocks[lastBlock]->els[lastPos];
    }

    const T& back() const {
        if (empty()) throw std::underflow_error("Deque is empty!");
        size_t lastBlock = endBlock;
        size_t lastPos = endPos;
        decrementPointer(lastBlock, lastPos);
        return blocks[lastBlock]->els[lastPos];
    }

    // Добавление элементов
    void push_back(T el) {
        size_t nextBlock = endBlock;
        size_t nextPos = endPos;
        incrementPointer(nextBlock, nextPos);
        
        if (nextBlock == beginBlock && size() > 0) {
            expand();
        }
        
        if (endBlock == beginBlock && endPos < beginPos && size() > 0) {
            expand();
        }

        new (&blocks[endBlock]->els[endPos]) T(std::move(el));
        incrementPointer(endBlock, endPos);
    }

    T pop_back() {
        if (empty()) {
            throw std::underflow_error("Deque is empty! Cannot pop_back().");
        }
        
        decrementPointer(endBlock, endPos);
        
        T res = std::move(blocks[endBlock]->els[endPos]);
        blocks[endBlock]->els[endPos].~T();

        return res;
    }

    void push_front(T el) {
        size_t prevBlock = beginBlock;
        size_t prevPos = beginPos;
        decrementPointer(prevBlock, prevPos);
        
        if (prevBlock == endBlock && size() > 0) {
            expand();
        }
        
        if (beginBlock == endBlock && endPos < beginPos && size() > 0) {
            expand();
        }

        decrementPointer(beginBlock, beginPos);
        new (&blocks[beginBlock]->els[beginPos]) T(std::move(el));
    }

    T pop_front() {
        if (empty()) {
            throw std::underflow_error("Deque is empty! Cannot pop_front().");
        }
        
        T res = std::move(blocks[beginBlock]->els[beginPos]);
        blocks[beginBlock]->els[beginPos].~T();

        incrementPointer(beginBlock, beginPos);
        return res;
    }

    // Служебные методы
    size_t size() const {
        if (empty()) return 0;
        
        if (endBlock > beginBlock || (endBlock == beginBlock && endPos > beginPos)) {
            return (endBlock - beginBlock) * BLOCK_SIZE + endPos - beginPos;
        } else if (endBlock < beginBlock || (endBlock == beginBlock && endPos < beginPos)) {
            return (blocks_count - beginBlock) * BLOCK_SIZE - beginPos 
                   + endBlock * BLOCK_SIZE + endPos;
        }
        return 0;
    }

    bool empty() const {
        return beginBlock == endBlock && beginPos == endPos;
    }

    void clear() {
        while (!empty()) {
            pop_back();
        }
    }

private:
    void expand() {
        size_t new_count = blocks_count * 2;
        Block** new_blocks = new Block*[new_count];

        size_t srcBlock = beginBlock;
        
        for (size_t i = 0; i < blocks_count; i++) {
            new_blocks[i] = blocks[srcBlock];
            
            if (srcBlock == endBlock) {
                endBlock = i;
            }
            
            srcBlock = (srcBlock + 1) % blocks_count;
        }

        for (size_t i = blocks_count; i < new_count; i++) {
            new_blocks[i] = (Block*)new unsigned char[sizeof(Block)];
        }

        beginBlock = 0;
        delete[] blocks;

        blocks_count = new_count;
        blocks = new_blocks;
    }

    Block** blocks;
    size_t blocks_count;

    size_t beginBlock;
    size_t beginPos;
    size_t endBlock;
    size_t endPos;

public:
    class Iterator {
        friend class Deque<T>;

    private:
        Deque<T>* parent;
        size_t pos;

        Iterator(Deque<T>* parent, size_t pos) : parent(parent), pos(pos) {}

    public:
        T& operator*() const { return parent->at(pos); }
        T* operator->() const { return &parent->at(pos); }

        Iterator& operator++() {
            pos++;
            return *this;
        }
        Iterator& operator--() {
            pos--;
            return *this;
        }
        Iterator operator++(int) {
            Iterator res = *this;
            pos++;
            return res;
        }
        Iterator operator--(int) {
            Iterator res = *this;
            pos--;
            return res;
        }

        bool operator==(const Iterator& other) const { return pos == other.pos; }
        bool operator!=(const Iterator& other) const { return pos != other.pos; }

        Iterator operator+=(size_t n) {
            pos += n;
            return *this;
        }
        Iterator operator-=(size_t n) {
            pos -= n;
            return *this;
        }
        Iterator operator+(size_t n) const {
            Iterator res = *this;
            res.pos += n;
            return res;
        }
        Iterator operator-(size_t n) const {
            Iterator res = *this;
            res.pos -= n;
            return res;
        }
        
        bool operator<(const Iterator& other) const { return pos < other.pos; }
        bool operator>(const Iterator& other) const { return pos > other.pos; }
        bool operator<=(const Iterator& other) const { return pos <= other.pos; }
        bool operator>=(const Iterator& other) const { return pos >= other.pos; }
        ptrdiff_t operator-(const Iterator& other) const { 
            return static_cast<ptrdiff_t>(pos) - static_cast<ptrdiff_t>(other.pos); 
        }
    };

    Iterator begin() { return Iterator(this, 0); }
    Iterator end() { return Iterator(this, size()); }
};

#endif // DEQUE_H