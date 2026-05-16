#ifndef ARRAY_HEAP_H_
#define ARRAY_HEAP_H_

#include <memory>
#include <vector>
#include <stdexcept>
#include <sstream>

template<typename T>
class ArrayHeap {
public:
    ArrayHeap() : heap_() {}
    
    explicit ArrayHeap(size_t capacity) {
        heap_.reserve(capacity);
    }
    
    ~ArrayHeap() = default;

    // Добавление элемента
    void push(const T& value) {
        auto node = std::make_shared<T>(value);
        heap_.push_back(node);
        siftUp(heap_.size() - 1);
    }
    
    void push(T&& value) {
        auto node = std::make_shared<T>(std::move(value));
        heap_.push_back(node);
        siftUp(heap_.size() - 1);
    }
    
    // Удаление максимума
    T pop() {
        if (empty()) {
            throw std::out_of_range("Heap is empty");
        }
        
        T result = *heap_[0];
        heap_[0] = heap_.back();
        heap_.pop_back();
        
        if (!empty()) {
            siftDown(0);
        }
        
        return result;
    }
    
    // Нахождение максимума
    const T& top() const {
        if (empty()) {
            throw std::out_of_range("Heap is empty");
        }
        return *heap_[0];
    }
    
    bool empty() const {
        return heap_.empty();
    }
    
    size_t size() const {
        return heap_.size();
    }
    
    void clear() {
        heap_.clear();
    }
    
    std::vector<T> getAllElements() const {
        std::vector<T> result;
        for (const auto& ptr : heap_) {
            result.push_back(*ptr);
        }
        return result;
    }
    
    std::string toString() const {
        std::stringstream ss;
        ss << "[";
        for (size_t i = 0; i < heap_.size(); i++) {
            if (i > 0) ss << ", ";
            ss << *heap_[i];
        }
        ss << "]";
        return ss.str();
    }

private:
    std::vector<std::shared_ptr<T>> heap_;
    
    // Просеивание вверх для max-heap (больший элемент поднимается вверх)
    void siftUp(size_t index) {
        while (index > 0) {
            size_t parent = (index - 1) / 2;
            if (*heap_[parent] >= *heap_[index]) {
                break;
            }
            std::swap(heap_[parent], heap_[index]);
            index = parent;
        }
    }
    
    // Просеивание вниз для max-heap (меньший элемент опускается вниз)
    void siftDown(size_t index) {
        size_t heapSize = heap_.size();
        
        while (true) {
            size_t left = 2 * index + 1;
            size_t right = 2 * index + 2;
            size_t largest = index;
            
            if (left < heapSize && *heap_[left] > *heap_[largest]) {
                largest = left;
            }
            
            if (right < heapSize && *heap_[right] > *heap_[largest]) {
                largest = right;
            }
            
            if (largest == index) {
                break;
            }
            
            std::swap(heap_[index], heap_[largest]);
            index = largest;
        }
    }
};

#endif  // ARRAY_HEAP_H_