#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <sstream>

inline int hashFunctionHorner(const std::string& s, int tableSize, const int key) {
    int hashResult = 0;
    for (int i = 0; i < s.size(); ++i) {
        hashResult = (key * hashResult + s[i]) % tableSize;
    }
    hashResult = (hashResult * 2 + 1) % tableSize;
    return hashResult;
}

struct HashFunction {
    int operator()(const std::string& s, int tableSize) const {
        return hashFunctionHorner(s, tableSize, tableSize - 1);
    }
};

template <class TKey, class TValue>
struct KeyValuePair {
    TKey key;
    TValue value;
    
    KeyValuePair() : key(), value() {}
    KeyValuePair(const TKey& k, const TValue& v) : key(k), value(v) {}
    
    bool operator==(const KeyValuePair& other) const {
        return key == other.key;
    }
};

template <class TKey, class TValue, class THash = HashFunction>
class HashTable {
    static const int defaultSize = 8;
    constexpr static const double rehashSize = 0.75;

    using T = KeyValuePair<TKey, TValue>;

    struct Node {
        T value;
        Node* next;
        Node(const T& value_) : value(value_), next(nullptr) {}
    };

    struct Stack {
        Node* top;
        Stack() : top(nullptr) {}

        void push(const T& value) {
            Node* newNode = new Node(value);
            newNode->next = top;
            top = newNode;
        }

        bool pop(T& value) {
            if (top == nullptr) {
                return false;
            }
            Node* temp = top;
            value = temp->value;
            top = top->next;
            delete temp;
            return true;
        }

        bool peek(T& value) const {
            if (top == nullptr) {
                return false;
            }
            value = top->value;
            return true;
        }

        bool removeValue(const TKey& key) {
            if (top == nullptr) {
                return false;
            }
            if (top->value.key == key) {
                Node* temp = top;
                top = top->next;
                delete temp;
                return true;
            }
            Node* current = top;
            while (current->next != nullptr) {
                if (current->next->value.key == key) {
                    Node* temp = current->next;
                    current->next = current->next->next;
                    delete temp;
                    return true;
                }
                current = current->next;
            }
            return false;
        }

        bool contains(const TKey& key) const {
            Node* current = top;
            while (current != nullptr) {
                if (current->value.key == key) {
                    return true;
                }
                current = current->next;
            }
            return false;
        }

        TValue* findValue(const TKey& key) const {
            Node* current = top;
            while (current != nullptr) {
                if (current->value.key == key) {
                    return &(current->value.value);
                }
                current = current->next;
            }
            return nullptr;
        }

        int size() const {
            int count = 0;
            Node* current = top;
            while (current != nullptr) {
                ++count;
                current = current->next;
            }
            return count;
        }

        std::string toString() const {
            std::ostringstream oss;
            Node* current = top;
            bool first = true;
            while (current != nullptr) {
                if (!first) {
                    oss << " -> ";
                }
                oss << "[" << current->value.key << ":" << current->value.value << "]";
                first = false;
                current = current->next;
            }
            return oss.str();
        }

        void clear() {
            while (top != nullptr) {
                Node* temp = top;
                top = top->next;
                delete temp;
            }
        }
    };

    Stack* arr;
    int bufferSize;
    int elementCount;

    void resize() {
        int pastBufferSize = bufferSize;
        bufferSize *= 2;
        elementCount = 0;
        Stack* arr2 = new Stack[bufferSize];
        std::swap(arr, arr2);
        for (int i = 0; i < pastBufferSize; ++i) {
            T value;
            while (arr2[i].pop(value)) {
                add(value.key, value.value);
            }
        }
        delete[] arr2;
    }

public:
    HashTable() {
        bufferSize = defaultSize;
        elementCount = 0;
        arr = new Stack[bufferSize];
    }

    ~HashTable() {
        for (int i = 0; i < bufferSize; ++i) {
            arr[i].clear();
        }
        delete[] arr;
    }

    bool add(const TKey& key, const TValue& value, const THash& hash = THash()) {
        if (elementCount + 1 > int(rehashSize * bufferSize)) {
            resize();
        }
        int h = hash(key, bufferSize);
        if (arr[h].contains(key)) {
            return false;
        }
        arr[h].push(T(key, value));
        ++elementCount;
        return true;
    }

    bool remove(const TKey& key, const THash& hash = THash()) {
        int h = hash(key, bufferSize);
        if (arr[h].removeValue(key)) {
            --elementCount;
            return true;
        }
        return false;
    }

    TValue* find(const TKey& key, const THash& hash = THash()) {
        int h = hash(key, bufferSize);
        return arr[h].findValue(key);
    }

    std::string print() const {
        std::ostringstream oss;
        for (int i = 0; i < bufferSize; ++i) {
            oss << "[" << i << "]: ";
            std::string stackContent = arr[i].toString();
            if (stackContent.empty()) {
                oss << "(empty)";
            } else {
                oss << stackContent;
            }
            oss << "\n";
        }
        return oss.str();
    }

    int getBufferSize() const {
        return bufferSize;
    }

    int getElementCount() const {
        return elementCount;
    }

    class Iterator {
        int tableIndex;
        Node* currentNode;
        const HashTable* table;
    public:
        Iterator(const HashTable* t, int idx, Node* node)
            : table(t), tableIndex(idx), currentNode(node) {
            if (currentNode == nullptr && tableIndex < table->bufferSize) {
                advanceToNext();
            }
        }

        bool hasNext() const {
            return currentNode != nullptr;
        }

        T next() {
            T val = currentNode->value;
            currentNode = currentNode->next;
            if (currentNode == nullptr) {
                ++tableIndex;
                advanceToNext();
            }
            return val;
        }

    private:
        void advanceToNext() {
            while (tableIndex < table->bufferSize && table->arr[tableIndex].top == nullptr) {
                ++tableIndex;
            }
            if (tableIndex < table->bufferSize) {
                currentNode = table->arr[tableIndex].top;
            } else {
                currentNode = nullptr;
            }
        }
    };

    Iterator getIterator() const {
        return Iterator(this, 0, nullptr);
    }
};

#endif // HASHTABLE_H