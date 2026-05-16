#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <utility>
#include <stdexcept>
#include <functional>

template<typename KeyType, typename ValueType>
class BinarySearchTree {
public:
    using PairType = std::pair<const KeyType, ValueType>;
    
    struct Node {
        PairType data;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        std::weak_ptr<Node> parent;
        std::shared_ptr<Node> nextInList;
        std::weak_ptr<Node> prevInList;
        
        Node(const KeyType& key, const ValueType& value)
            : data(key, value), left(nullptr), right(nullptr), nextInList(nullptr) {}
        
        Node(const KeyType& key)
            : data(key, ValueType{}), left(nullptr), right(nullptr), nextInList(nullptr) {}
    };
    
private:
    std::shared_ptr<Node> root;
    std::shared_ptr<Node> listHead;
    std::shared_ptr<Node> listTail;
    size_t nodeCount;
    
    void updateListLinks() {
        listHead = nullptr;
        listTail = nullptr;
        std::shared_ptr<Node> prev = nullptr;
        
        traverseInOrder(root, [this, &prev](std::shared_ptr<Node> node) {
            if (!listHead) {
                listHead = node;
            }
            node->prevInList = prev;
            if (prev) {
                prev->nextInList = node;
            }
            prev = node;
        });
        
        listTail = prev;
        if (listTail) {
            listTail->nextInList = nullptr;
        }
    }
    
    template<typename Func>
    void traverseInOrder(std::shared_ptr<Node> node, Func func) {
        if (!node) return;
        traverseInOrder(node->left, func);
        func(node);
        traverseInOrder(node->right, func);
    }
    
    std::shared_ptr<Node> insertNode(std::shared_ptr<Node> node, const KeyType& key,
                                     const ValueType& value, std::shared_ptr<Node> parent = nullptr) {
        if (!node) {
            auto newNode = std::make_shared<Node>(key, value);
            newNode->parent = parent;
            ++nodeCount;
            return newNode;
        }
        
        if (key < node->data.first) {
            node->left = insertNode(node->left, key, value, node);
        } else if (key > node->data.first) {
            node->right = insertNode(node->right, key, value, node);
        }
        return node;
    }
    
    std::shared_ptr<Node> findNode(std::shared_ptr<Node> node, const KeyType& key) const {
        if (!node) return nullptr;
        if (key == node->data.first) return node;
        if (key < node->data.first) return findNode(node->left, key);
        return findNode(node->right, key);
    }
    
    std::shared_ptr<Node> findMinNode(std::shared_ptr<Node> node) const {
        if (!node) return nullptr;
        while (node->left) node = node->left;
        return node;
    }
    
    std::shared_ptr<Node> removeNode(std::shared_ptr<Node> node, const KeyType& key) {
        if (!node) return nullptr;
        
        if (key < node->data.first) {
            node->left = removeNode(node->left, key);
        } else if (key > node->data.first) {
            node->right = removeNode(node->right, key);
        } else {
            --nodeCount;
            
            if (!node->left && !node->right) {
                return nullptr;
            } else if (!node->left) {
                if (node->right) {
                    node->right->parent = node->parent;
                }
                return node->right;
            } else if (!node->right) {
                if (node->left) {
                    node->left->parent = node->parent;
                }
                return node->left;
            } else {
                auto minNode = findMinNode(node->right);
                node->data.second = minNode->data.second;
                node->right = removeNode(node->right, minNode->data.first);
                return node;
            }
        }
        return node;
    }
    
    void clearTree(std::shared_ptr<Node>& node) {
        if (!node) return;
        clearTree(node->left);
        clearTree(node->right);
        node.reset();
    }
    
    std::shared_ptr<Node> deepCopy(std::shared_ptr<Node> src, std::shared_ptr<Node> parent = nullptr) {
        if (!src) return nullptr;
        auto newNode = std::make_shared<Node>(src->data.first, src->data.second);
        newNode->parent = parent;
        newNode->left = deepCopy(src->left, newNode);
        newNode->right = deepCopy(src->right, newNode);
        return newNode;
    }

public:
    class TreeIterator {
    private:
        std::shared_ptr<Node> currentNode;
        const BinarySearchTree* tree;
        
        friend class BinarySearchTree;
        
        TreeIterator(std::shared_ptr<Node> node, const BinarySearchTree* t)
            : currentNode(node), tree(t) {}
        
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = PairType;
        using difference_type = std::ptrdiff_t;
        using pointer = PairType*;
        using reference = PairType&;
        
        TreeIterator() : currentNode(nullptr), tree(nullptr) {}
        
        reference operator*() const {
            return currentNode->data;
        }
        
        pointer operator->() const {
            return &(currentNode->data);
        }
        
        TreeIterator& operator++() {
            if (!currentNode) return *this;
            
            if (currentNode->right) {
                currentNode = tree->findMinNode(currentNode->right);
            } else {
                auto parent = currentNode->parent.lock();
                while (parent && currentNode == parent->right) {
                    currentNode = parent;
                    parent = currentNode->parent.lock();
                }
                currentNode = parent;
            }
            return *this;
        }
        
        TreeIterator operator++(int) {
            TreeIterator temp = *this;
            ++(*this);
            return temp;
        }
        
        TreeIterator& operator--() {
            if (!currentNode) {
                if (tree && tree->root) {
                    currentNode = tree->root;
                    while (currentNode->right) {
                        currentNode = currentNode->right;
                    }
                }
                return *this;
            }
            
            if (currentNode->left) {
                currentNode = currentNode->left;
                while (currentNode->right) {
                    currentNode = currentNode->right;
                }
            } else {
                auto parent = currentNode->parent.lock();
                while (parent && currentNode == parent->left) {
                    currentNode = parent;
                    parent = currentNode->parent.lock();
                }
                currentNode = parent;
            }
            return *this;
        }
        
        TreeIterator operator--(int) {
            TreeIterator temp = *this;
            --(*this);
            return temp;
        }
        
        bool operator==(const TreeIterator& other) const {
            return currentNode == other.currentNode;
        }
        
        bool operator!=(const TreeIterator& other) const {
            return !(*this == other);
        }
    };
    
    class ListIterator {
    private:
        std::shared_ptr<Node> currentNode;
        
        friend class BinarySearchTree;
        
        ListIterator(std::shared_ptr<Node> node) : currentNode(node) {}
        
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = PairType;
        using difference_type = std::ptrdiff_t;
        using pointer = PairType*;
        using reference = PairType&;
        
        ListIterator() : currentNode(nullptr) {}
        
        reference operator*() const {
            return currentNode->data;
        }
        
        pointer operator->() const {
            return &(currentNode->data);
        }
        
        ListIterator& operator++() {
            if (currentNode) {
                currentNode = currentNode->nextInList;
            }
            return *this;
        }
        
        ListIterator operator++(int) {
            ListIterator temp = *this;
            ++(*this);
            return temp;
        }
        
        ListIterator& operator--() {
            if (currentNode) {
                currentNode = currentNode->prevInList.lock();
            }
            return *this;
        }
        
        ListIterator operator--(int) {
            ListIterator temp = *this;
            --(*this);
            return temp;
        }
        
        bool operator==(const ListIterator& other) const {
            return currentNode == other.currentNode;
        }
        
        bool operator!=(const ListIterator& other) const {
            return !(*this == other);
        }
    };
    
    using iterator = TreeIterator;
    using listIterator = ListIterator;
    
    BinarySearchTree() : root(nullptr), listHead(nullptr), listTail(nullptr), nodeCount(0) {}
    
    BinarySearchTree(const BinarySearchTree& other)
        : root(nullptr), listHead(nullptr), listTail(nullptr), nodeCount(0) {
        root = deepCopy(other.root);
        nodeCount = other.nodeCount;
        updateListLinks();
    }
    
    BinarySearchTree& operator=(const BinarySearchTree& other) {
        if (this != &other) {
            clear();
            root = deepCopy(other.root);
            nodeCount = other.nodeCount;
            updateListLinks();
        }
        return *this;
    }
    
    ~BinarySearchTree() {
        clear();
    }
    
    virtual void insert(const KeyType& key, const ValueType& value) {
        root = insertNode(root, key, value);
        updateListLinks();
    }
    
    virtual void insert(const PairType& pair) {
        insert(pair.first, pair.second);
    }
    
    virtual bool remove(const KeyType& key) {
        if (!contains(key)) return false;
        root = removeNode(root, key);
        updateListLinks();
        return true;
    }
    
    ValueType& at(const KeyType& key) {
        auto node = findNode(root, key);
        if (!node) {
            throw std::out_of_range("Key not found in tree");
        }
        return node->data.second;
    }
    
    const ValueType& at(const KeyType& key) const {
        auto node = findNode(root, key);
        if (!node) {
            throw std::out_of_range("Key not found in tree");
        }
        return node->data.second;
    }
    
    ValueType& operator[](const KeyType& key) {
        auto node = findNode(root, key);
        if (!node) {
            insert(key, ValueType{});
            node = findNode(root, key);
        }
        return node->data.second;
    }
    
    const ValueType& operator[](const KeyType& key) const {
        auto node = findNode(root, key);
        if (!node) {
            throw std::out_of_range("Key not found");
        }
        return node->data.second;
    }
    
    bool contains(const KeyType& key) const {
        return findNode(root, key) != nullptr;
    }
    
    virtual void updateIterators() {
        updateListLinks();
    }
    
    bool empty() const {
        return root == nullptr;
    }
    
    size_t size() const {
        return nodeCount;
    }
    
    void clear() {
        clearTree(root);
        listHead = nullptr;
        listTail = nullptr;
        nodeCount = 0;
    }
    
    iterator begin() const {
        if (!root) return iterator(nullptr, this);
        auto node = root;
        while (node->left) node = node->left;
        return iterator(node, this);
    }
    
    iterator end() const {
        return iterator(nullptr, this);
    }
    
    listIterator beginList() const {
        return listIterator(listHead);
    }
    
    listIterator endList() const {
        return listIterator(nullptr);
    }
    
    iterator find(const KeyType& key) const {
        auto node = findNode(root, key);
        return iterator(node, this);
    }
    
    std::shared_ptr<Node> getRoot() const {
        return root;
    }
};

#endif // BINARY_SEARCH_TREE_H