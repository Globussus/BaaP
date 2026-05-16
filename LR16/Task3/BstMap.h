#ifndef BST_MAP_H
#define BST_MAP_H

#include "BinarySearchTree.h"

template<typename KeyType, typename ValueType>
class Map : public BinarySearchTree<KeyType, ValueType> {
public:
    using PairType = typename BinarySearchTree<KeyType, ValueType>::PairType;
    using iterator = typename BinarySearchTree<KeyType, ValueType>::iterator;
    using listIterator = typename BinarySearchTree<KeyType, ValueType>::listIterator;
    
    Map() : BinarySearchTree<KeyType, ValueType>() {}
    
    void insert(const KeyType& key, const ValueType& value) override {
        BinarySearchTree<KeyType, ValueType>::insert(key, value);
    }
    
    using BinarySearchTree<KeyType, ValueType>::remove;
    using BinarySearchTree<KeyType, ValueType>::contains;
    using BinarySearchTree<KeyType, ValueType>::operator[];
    using BinarySearchTree<KeyType, ValueType>::size;
    using BinarySearchTree<KeyType, ValueType>::clear;
    using BinarySearchTree<KeyType, ValueType>::begin;
    using BinarySearchTree<KeyType, ValueType>::end;
    using BinarySearchTree<KeyType, ValueType>::beginList;
    using BinarySearchTree<KeyType, ValueType>::endList;
    using BinarySearchTree<KeyType, ValueType>::empty;
    using BinarySearchTree<KeyType, ValueType>::find;
    using BinarySearchTree<KeyType, ValueType>::getRoot;
};

#endif // BST_MAP_H