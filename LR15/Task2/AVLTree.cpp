#include "AVLTree.h"
#include <algorithm>

unsigned char AVLTree::getHeight(Node* p) {
    return p ? p->height : 0;
}

int AVLTree::getBalanceFactor(Node* p) {
    return getHeight(p->right) - getHeight(p->left);
}

void AVLTree::fixHeight(Node* p) {
    unsigned char heightLeft = getHeight(p->left);
    unsigned char heightRight = getHeight(p->right);
    p->height = (heightLeft > heightRight ? heightLeft : heightRight) + 1;
}

Node* AVLTree::rotateRight(Node* p) {
    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixHeight(p);
    fixHeight(q);
    return q;
}

Node* AVLTree::rotateLeft(Node* q) {
    Node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixHeight(q);
    fixHeight(p);
    return p;
}

Node* AVLTree::balance(Node* p) {
    fixHeight(p);
    if (getBalanceFactor(p) == 2) {
        if (getBalanceFactor(p->right) < 0) {
            p->right = rotateRight(p->right);
        }
        return rotateLeft(p);
    }
    if (getBalanceFactor(p) == -2) {
        if (getBalanceFactor(p->left) > 0) {
            p->left = rotateLeft(p->left);
        }
        return rotateRight(p);
    }
    return p;
}

Node* AVLTree::insert(Node* p, const QString& data, int key) {
    if (!p) {
        return new Node(data, key);
    }
    if (key < p->key) {
        p->left = insert(p->left, data, key);
    } else if (key > p->key) {
        p->right = insert(p->right, data, key);
    }
    return balance(p);
}

Node* AVLTree::findMin(Node* p) {
    return p->left ? findMin(p->left) : p;
}

Node* AVLTree::removeMin(Node* p) {
    if (!p->left) {
        return p->right;
    }
    p->left = removeMin(p->left);
    return balance(p);
}

Node* AVLTree::remove(Node* p, int key) {
    if (!p) {
        return nullptr;
    }
    if (key < p->key) {
        p->left = remove(p->left, key);
    } else if (key > p->key) {
        p->right = remove(p->right, key);
    } else {
        Node* left = p->left;
        Node* right = p->right;
        delete p;
        if (!right) {
            return left;
        }
        Node* min = findMin(right);
        min->right = removeMin(right);
        min->left = left;
        return balance(min);
    }
    return balance(p);
}

void AVLTree::inOrder(Node* p, QVector<Node*>& result) {
    if (!p) return;
    inOrder(p->left, result);
    result.append(p);
    inOrder(p->right, result);
}

void AVLTree::preOrder(Node* p, QVector<Node*>& result) {
    if (!p) return;
    result.append(p);
    preOrder(p->left, result);
    preOrder(p->right, result);
}

void AVLTree::postOrder(Node* p, QVector<Node*>& result) {
    if (!p) return;
    postOrder(p->left, result);
    postOrder(p->right, result);
    result.append(p);
}

void AVLTree::clear(Node* p) {
    if (!p) return;
    clear(p->left);
    clear(p->right);
    delete p;
}

Node* AVLTree::copy(Node* p) {
    if (!p) return nullptr;
    Node* newNode = new Node(p->data, p->key);
    newNode->height = p->height;
    newNode->left = copy(p->left);
    newNode->right = copy(p->right);
    return newNode;
}

int AVLTree::countTotalCharacters(Node* p) {
    if (!p) return 0;
    return p->data.length() + countTotalCharacters(p->left) + countTotalCharacters(p->right);
}

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::AVLTree(const AVLTree& other) {
    root = copy(other.root);
}

AVLTree::~AVLTree() {
    clear(root);
}

AVLTree& AVLTree::operator=(const AVLTree& other) {
    if (this != &other) {
        clear(root);
        root = copy(other.root);
    }
    return *this;
}

void AVLTree::insert(const QString& data, int key) {
    root = insert(root, data, key);
}

bool AVLTree::remove(int key) {
    if (!contains(key)) {
        return false;
    }
    root = remove(root, key);
    return true;
}

Node* AVLTree::find(int key) {
    Node* current = root;
    while (current) {
        if (key == current->key) {
            return current;
        }
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return nullptr;
}

bool AVLTree::contains(int key) {
    return find(key) != nullptr;
}

QVector<Node*> AVLTree::getInOrder() {
    QVector<Node*> result;
    inOrder(root, result);
    return result;
}

QVector<Node*> AVLTree::getPreOrder() {
    QVector<Node*> result;
    preOrder(root, result);
    return result;
}

QVector<Node*> AVLTree::getPostOrder() {
    QVector<Node*> result;
    postOrder(root, result);
    return result;
}

int AVLTree::getSize() {
    return getInOrder().size();
}

void AVLTree::clear() {
    clear(root);
    root = nullptr;
}

int AVLTree::getTotalCharacters() {
    return countTotalCharacters(root);
}