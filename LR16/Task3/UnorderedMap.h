#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#include <forward_list>
#include <vector>
#include <functional>
#include <utility>
#include <stdexcept>

template<typename KeyType, typename ValueType, typename Hash = std::hash<KeyType>>
class UnorderedMap {
public:
    using PairType = std::pair<const KeyType, ValueType>;
    
private:
    std::vector<std::forward_list<PairType>> buckets;
    size_t elementCount;
    Hash hashFunc;
    double maxLoadFactor;
    
    void rehashInternal(size_t newBucketCount) {
        if (newBucketCount < 1) {
            newBucketCount = 1;
        }
        
        std::vector<std::forward_list<PairType>> newBuckets(newBucketCount);
        
        for (auto& bucket : buckets) {
            for (auto& pair : bucket) {
                size_t index = hashFunc(pair.first) % newBucketCount;
                newBuckets[index].push_front(std::move(pair));
            }
        }
        
        buckets = std::move(newBuckets);
    }
    
    size_t bucketIndex(const KeyType& key) const {
        return hashFunc(key) % buckets.size();
    }
    
    auto findInBucket(const KeyType& key, size_t index) const {
        for (auto it = buckets[index].begin(); it != buckets[index].end(); ++it) {
            if (it->first == key) {
                return it;
            }
        }
        return buckets[index].end();
    }
    
    auto findInBucket(const KeyType& key, size_t index) {
        for (auto it = buckets[index].begin(); it != buckets[index].end(); ++it) {
            if (it->first == key) {
                return it;
            }
        }
        return buckets[index].end();
    }

public:
    explicit UnorderedMap(size_t initialBucketCount = 8, const Hash& hash = Hash())
        : buckets(initialBucketCount), elementCount(0), hashFunc(hash), maxLoadFactor(1.0) {
        if (initialBucketCount < 1) {
            buckets.resize(8);
        }
    }
    
    ValueType& operator[](const KeyType& key) {
        size_t index = bucketIndex(key);
        auto it = findInBucket(key, index);
        
        if (it != buckets[index].end()) {
            return it->second;
        }
        
        if (elementCount + 1 > buckets.size() * maxLoadFactor) {
            rehashInternal(buckets.size() * 2);
            index = bucketIndex(key);
        }
        
        buckets[index].push_front(std::make_pair(key, ValueType{}));
        ++elementCount;
        return buckets[index].front().second;
    }
    
    const ValueType& operator[](const KeyType& key) const {
        size_t index = bucketIndex(key);
        auto it = findInBucket(key, index);
        
        if (it != buckets[index].end()) {
            return it->second;
        }
        
        throw std::out_of_range("Key not found in unordered_map");
    }
    
    void insert(const KeyType& key, const ValueType& value) {
        size_t index = bucketIndex(key);
        auto it = findInBucket(key, index);
        
        if (it != buckets[index].end()) {
            it->second = value;
            return;
        }
        
        if (elementCount + 1 > buckets.size() * maxLoadFactor) {
            rehashInternal(buckets.size() * 2);
            index = bucketIndex(key);
        }
        
        buckets[index].push_front(std::make_pair(key, value));
        ++elementCount;
    }
    
    void insert(const PairType& pair) {
        insert(pair.first, pair.second);
    }
    
    bool erase(const KeyType& key) {
        size_t index = bucketIndex(key);
        auto& bucket = buckets[index];
        
        auto prev = bucket.before_begin();
        auto current = bucket.begin();
        
        while (current != bucket.end()) {
            if (current->first == key) {
                bucket.erase_after(prev);
                --elementCount;
                return true;
            }
            prev = current;
            ++current;
        }
        
        return false;
    }
    
    bool contains(const KeyType& key) const {
        size_t index = bucketIndex(key);
        auto it = findInBucket(key, index);
        return it != buckets[index].end();
    }
    
    ValueType* find(const KeyType& key) {
        size_t index = bucketIndex(key);
        auto it = findInBucket(key, index);
        
        if (it != buckets[index].end()) {
            return &(it->second);
        }
        
        return nullptr;
    }
    
    const ValueType* find(const KeyType& key) const {
        size_t index = bucketIndex(key);
        auto it = findInBucket(key, index);
        
        if (it != buckets[index].end()) {
            return &(it->second);
        }
        
        return nullptr;
    }
    
    void clear() {
        for (auto& bucket : buckets) {
            bucket.clear();
        }
        elementCount = 0;
    }
    
    void rehash(size_t newBucketCount) {
        rehashInternal(newBucketCount);
    }
    
    size_t size() const {
        return elementCount;
    }
    
    size_t bucketCount() const {
        return buckets.size();
    }
    
    bool empty() const {
        return elementCount == 0;
    }
    
    float loadFactor() const {
        return buckets.empty() ? 0.0f : static_cast<float>(elementCount) / buckets.size();
    }
    
    size_t maxBucketSize() const {
        size_t maxSize = 0;
        for (const auto& bucket : buckets) {
            size_t bucketSize = 0;
            for (auto it = bucket.begin(); it != bucket.end(); ++it) {
                ++bucketSize;
            }
            maxSize = std::max(maxSize, bucketSize);
        }
        return maxSize;
    }
    
    size_t collisionCount() const {
        size_t collisions = 0;
        for (const auto& bucket : buckets) {
            size_t bucketSize = 0;
            for (auto it = bucket.begin(); it != bucket.end(); ++it) {
                ++bucketSize;
            }
            if (bucketSize > 1) {
                collisions += bucketSize - 1;
            }
        }
        return collisions;
    }
    
    const std::vector<std::forward_list<PairType>>& getBuckets() const {
        return buckets;
    }
};

#endif // UNORDERED_MAP_H