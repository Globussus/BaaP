#ifndef LIST_HEAP_H_
#define LIST_HEAP_H_

#include <memory>
#include <stdexcept>
#include <sstream>
#include <vector>

template<typename T>
struct ListNode {
    std::shared_ptr<T> data;
    std::shared_ptr<ListNode<T>> next;
    
    explicit ListNode(const T& value) : data(std::make_shared<T>(value)), next(nullptr) {}
    explicit ListNode(T&& value) : data(std::make_shared<T>(std::move(value))), next(nullptr) {}
};

template<typename T>
class ListHeap {
public:
    ListHeap() : head_(nullptr), size_(0) {}
    
    ~ListHeap() = default;
    
    // Добавление элемента
    void push(const T& value) {
        auto newNode = std::make_shared<ListNode<T>>(value);
        
        if (!head_) {
            head_ = newNode;
        } else {
            auto current = head_;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        
        size_++;
        siftUp(getNodeAtIndex(size_ - 1));
    }
    
    void push(T&& value) {
        auto newNode = std::make_shared<ListNode<T>>(std::move(value));
        
        if (!head_) {
            head_ = newNode;
        } else {
            auto current = head_;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        
        size_++;
        siftUp(getNodeAtIndex(size_ - 1));
    }
    
    // Удаление максимума
    T pop() {
        if (empty()) {
            throw std::out_of_range("Heap is empty");
        }
        
        T result = *head_->data;
        
        if (size_ == 1) {
            head_.reset();
        } else {
            auto lastNode = getNodeAtIndex(size_ - 1);
            head_->data = lastNode->data;
            
            auto secondLast = getNodeAtIndex(size_ - 2);
            secondLast->next.reset();
        }
        
        size_--;
        
        if (!empty()) {
            siftDown(head_);
        }
        
        return result;
    }
    
    // Нахождение максимума
    const T& top() const {
        if (empty()) {
            throw std::out_of_range("Heap is empty");
        }
        return *head_->data;
    }
    
    bool empty() const {
        return size_ == 0;
    }
    
    size_t size() const {
        return size_;
    }
    
    void clear() {
        head_.reset();
        size_ = 0;
    }
    
    std::vector<T> getAllElements() const {
        std::vector<T> result;
        auto current = head_;
        while (current) {
            result.push_back(*current->data);
            current = current->next;
        }
        return result;
    }
    
    std::string toString() const {
        std::stringstream ss;
        ss << "[";
        auto current = head_;
        bool first = true;
        while (current) {
            if (!first) ss << ", ";
            ss << *current->data;
            first = false;
            current = current->next;
        }
        ss << "]";
        return ss.str();
    }
    
private:
    std::shared_ptr<ListNode<T>> head_;
    size_t size_;
    
    // Просеивание вверх для max-heap
    void siftUp(std::shared_ptr<ListNode<T>> node) {
        size_t index = 0;
        auto current = head_;
        while (current != node && current) {
            current = current->next;
            index++;
        }
        
        while (index > 0) {
            size_t parentIndex = (index - 1) / 2;
            auto parent = getNodeAtIndex(parentIndex);
            
            if (*parent->data >= *node->data) {
                break;
            }
            
            std::swap(parent->data, node->data);
            node = parent;
            index = parentIndex;
        }
    }
    
    // Просеивание вниз для max-heap
    void siftDown(std::shared_ptr<ListNode<T>> node) {
        size_t index = 0;
        auto current = head_;
        while (current != node && current) {
            current = current->next;
            index++;
        }
        
        while (true) {
            size_t leftIndex = 2 * index + 1;
            size_t rightIndex = 2 * index + 2;
            size_t largest = index;
            
            if (leftIndex < size_) {
                auto leftNode = getNodeAtIndex(leftIndex);
                if (*leftNode->data > *getNodeAtIndex(largest)->data) {
                    largest = leftIndex;
                }
            }
            
            if (rightIndex < size_) {
                auto rightNode = getNodeAtIndex(rightIndex);
                if (*rightNode->data > *getNodeAtIndex(largest)->data) {
                    largest = rightIndex;
                }
            }
            
            if (largest == index) {
                break;
            }
            
            auto largestNode = getNodeAtIndex(largest);
            std::swap(node->data, largestNode->data);
            node = largestNode;
            index = largest;
        }
    }
    
    std::shared_ptr<ListNode<T>> getNodeAtIndex(size_t index) const {
        if (index >= size_) {
            return nullptr;
        }
        
        auto current = head_;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
        return current;
    }
};

#endif  // LIST_HEAP_H_