#ifndef BST_SET_H
#define BST_SET_H

#include "BinarySearchTree.h"

template<typename KeyType>
class Set : public BinarySearchTree<KeyType, char> {
public:
    using iterator = typename BinarySearchTree<KeyType, char>::iterator;
    using listIterator = typename BinarySearchTree<KeyType, char>::listIterator;
    
    Set() : BinarySearchTree<KeyType, char>() {}
    
    void insert(const KeyType& key) {
        BinarySearchTree<KeyType, char>::insert(key, '0');
    }
    
    using BinarySearchTree<KeyType, char>::remove;
    using BinarySearchTree<KeyType, char>::contains;
    using BinarySearchTree<KeyType, char>::size;
    using BinarySearchTree<KeyType, char>::clear;
    using BinarySearchTree<KeyType, char>::begin;
    using BinarySearchTree<KeyType, char>::end;
    using BinarySearchTree<KeyType, char>::beginList;
    using BinarySearchTree<KeyType, char>::endList;
    using BinarySearchTree<KeyType, char>::empty;
    using BinarySearchTree<KeyType, char>::find;
    using BinarySearchTree<KeyType, char>::getRoot;
};

#endif // BST_SET_H