#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <sstream>
#include <vector>
#include <utility>

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

    enum State {
        FREE,
        BUSY,
        DELETED
    };

    struct Cell {
        T value;
        State state;
        int originalHash;

        Cell() : value(), state(FREE), originalHash(-1) {}
    };

    Cell* arr;
    int bufferSize;
    int elementCount;

    int linearProbe(int baseHash, int i) const {
        return (baseHash + i) % bufferSize;
    }

    void resize() {
        int pastBufferSize = bufferSize;
        Cell* oldArr = arr;
        
        bufferSize *= 2;
        elementCount = 0;
        arr = new Cell[bufferSize];
        
        for (int i = 0; i < pastBufferSize; ++i) {
            if (oldArr[i].state == BUSY) {
                add(oldArr[i].value.key, oldArr[i].value.value);
            }
        }
        delete[] oldArr;
    }

    int findIndex(const TKey& key, const THash& hash = THash()) const {
        int baseHash = hash(key, bufferSize);
        int h = baseHash;
        int i = 0;

        while (i < bufferSize) {
            if (arr[h].state == FREE) {
                return -1;
            }
            if (arr[h].state == BUSY && arr[h].value.key == key) {
                return h;
            }
            ++i;
            h = linearProbe(baseHash, i);
        }
        return -1;
    }

public:
    HashTable() {
        bufferSize = defaultSize;
        elementCount = 0;
        arr = new Cell[bufferSize];
    }

    HashTable(int size) {
        bufferSize = size;
        if (bufferSize < 1) bufferSize = defaultSize;
        elementCount = 0;
        arr = new Cell[bufferSize];
    }

    ~HashTable() {
        delete[] arr;
    }

    bool add(const TKey& key, const TValue& value, const THash& hash = THash()) {
        if (findIndex(key, hash) != -1) {
            return false;
        }

        if (elementCount + 1 > static_cast<int>(rehashSize * bufferSize)) {
            resize();
        }

        int baseHash = hash(key, bufferSize);
        int h = baseHash;
        int i = 0;
        int firstDeleted = -1;

        while (i < bufferSize) {
            if (arr[h].state == FREE) {
                if (firstDeleted != -1) {
                    h = firstDeleted;
                }
                arr[h].value = T(key, value);
                arr[h].state = BUSY;
                arr[h].originalHash = baseHash;
                ++elementCount;
                return true;
            }
            if (arr[h].state == DELETED && firstDeleted == -1) {
                firstDeleted = h;
            }
            ++i;
            h = linearProbe(baseHash, i);
        }
        
        return false;
    }

    bool remove(const TKey& key, const THash& hash = THash()) {
        int index = findIndex(key, hash);
        if (index != -1) {
            arr[index].state = DELETED;
            --elementCount;
            return true;
        }
        return false;
    }

    TValue* find(const TKey& key, const THash& hash = THash()) {
        int index = findIndex(key, hash);
        if (index != -1) {
            return &(arr[index].value.value);
        }
        return nullptr;
    }

    std::vector<int> getProbeSequence(const TKey& key, const THash& hash = THash()) const {
        std::vector<int> sequence;
        int baseHash = hash(key, bufferSize);
        int h = baseHash;
        int i = 0;

        while (i < bufferSize) {
            sequence.push_back(h);
            if (arr[h].state == FREE) {
                return sequence;
            }
            if (arr[h].state == BUSY && arr[h].value.key == key) {
                return sequence;
            }
            ++i;
            h = linearProbe(baseHash, i);
        }
        return sequence;
    }

    std::vector<std::pair<TKey, int>> getCollisionInfo() const {
        std::vector<std::pair<TKey, int>> collisions;
        for (int i = 0; i < bufferSize; ++i) {
            if (arr[i].state == BUSY) {
                int baseHash = arr[i].originalHash;
                if (baseHash != -1 && baseHash != i) {
                    collisions.push_back(std::make_pair(arr[i].value.key, baseHash));
                }
            }
        }
        return collisions;
    }

    std::string print() const {
        std::ostringstream oss;
        for (int i = 0; i < bufferSize; ++i) {
            oss << "[" << i << "]: ";
            if (arr[i].state == BUSY) {
                oss << "[" << arr[i].value.key << ":" << arr[i].value.value << "]";
                if (arr[i].originalHash != -1 && arr[i].originalHash != i) {
                    oss << " (h'=" << arr[i].originalHash << ")";
                }
            } else if (arr[i].state == DELETED) {
                oss << "(уд)";
            } else {
                oss << "(пусто)";
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
};

#endif // HASHTABLE_H