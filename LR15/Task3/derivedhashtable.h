#ifndef DERIVEDHASHTABLE_H
#define DERIVEDHASHTABLE_H

#include "hashtable.h"
#include <string>
#include <limits>

template <class TKey, class TValue, class THash = HashFunction>
class DerivedHashTable : public HashTable<TKey, TValue, THash> {
public:
    TKey findMaxKey() const {
        if (this->getElementCount() == 0) {
            throw std::runtime_error("Table is empty");
        }
        auto it = this->getIterator();
        if (!it.hasNext()) {
            throw std::runtime_error("Table is empty");
        }
        auto firstPair = it.next();
        TKey maxKey = firstPair.key;
        while (it.hasNext()) {
            auto pair = it.next();
            if (pair.key > maxKey) {
                maxKey = pair.key;
            }
        }
        return maxKey;
    }
};

#endif // DERIVEDHASHTABLE_H