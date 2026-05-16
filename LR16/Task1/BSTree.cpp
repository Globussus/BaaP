#include "BSTree.h"

// Публичные методы

BSTree::BSTree() : root(nullptr) {}

BSTree::BSTree(const BSTree& other) {
    root = copy(other.root);
}

BSTree::~BSTree() {
    clear(root);
}

BSTree& BSTree::operator=(const BSTree& other) {
    if (this != &other) {
        clear(root);
        root = copy(other.root);
    }
    return *this;
}

void BSTree::add(const QString& data, int key) {
    root = add(root, data, key);
}

bool BSTree::remove(int key) {
    if (!contains(key)) {
        return false;
    }
    root = remove(root, key);
    return true;
}

Node* BSTree::find(int key) {
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

bool BSTree::contains(int key) {
    return find(key) != nullptr;
}

QVector<Node*> BSTree::traverse() {
    QVector<Node*> result;
    traverse(root, result);
    return result;
}

// Вставка поддерева
bool BSTree::insertSubtree(Node* subtreeRoot) {
    if (!subtreeRoot) {
        return false;
    }
    
    // Проверяем, нет ли уже такого ключа в дереве
    if (contains(subtreeRoot->key)) {
        return false;
    }
    
    // Копируем поддерево и вставляем
    Node* subtreeCopy = copy(subtreeRoot);
    
    if (!root) {
        root = subtreeCopy;
        return true;
    }
    
    // Находим место для вставки корня поддерева
    Node* current = root;
    Node* parent = nullptr;
    
    while (current) {
        parent = current;
        if (subtreeCopy->key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    if (subtreeCopy->key < parent->key) {
        parent->left = subtreeCopy;
    } else {
        parent->right = subtreeCopy;
    }
    
    return true;
}

// Удаление поддерева
Node* BSTree::removeSubtree(int key) {
    Node* target = find(key);
    if (!target) {
        return nullptr;
    }
    
    // Создаем копию поддерева перед удалением
    Node* subtreeCopy = copy(target);
    
    // Если удаляем корень дерева
    if (root && root->key == key) {
        clear(root);
        root = nullptr;
        return subtreeCopy;
    }
    
    // Находим родителя удаляемого узла
    Node* parent = findParent(root, key);
    if (!parent) {
        clear(subtreeCopy);
        return nullptr;
    }
    
    // Отсоединяем поддерево от родителя
    if (parent->left && parent->left->key == key) {
        clear(parent->left);
        parent->left = nullptr;
    } else if (parent->right && parent->right->key == key) {
        clear(parent->right);
        parent->right = nullptr;
    }
    
    return subtreeCopy;
}

// Вставка ветви (новый узел как дочерний для существующего)
bool BSTree::insertBranch(const QString& data, int key, int parentKey, bool asLeftChild) {
    if (contains(key)) {
        return false;
    }
    
    Node* parent = find(parentKey);
    if (!parent) {
        return false;
    }
    
    // Проверяем, не занята ли позиция
    if (asLeftChild && parent->left) {
        return false;
    }
    if (!asLeftChild && parent->right) {
        return false;
    }
    
    Node* newNode = new Node(data, key);
    
    if (asLeftChild) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    
    return true;
}

// Удаление ветви
bool BSTree::removeBranch(int key) {
    Node* target = find(key);
    if (!target) {
        return false;
    }
    
    if (root && root->key == key) {
        clear(root);
        root = nullptr;
        return true;
    }
    
    Node* parent = findParent(root, key);
    if (!parent) {
        return false;
    }
    
    bool isLeftChild = (parent->left && parent->left->key == key);
    
    if (isLeftChild) {
        clear(parent->left);
        parent->left = nullptr;
    } else {
        clear(parent->right);
        parent->right = nullptr;
    }
    
    return true;
}

// Вставка в определенную позицию
bool BSTree::insertAtPosition(const QString& data, int key, int parentKey, bool asLeftChild) {
    return insertBranch(data, key, parentKey, asLeftChild);
}

// Поиск наименьшего общего предка
Node* BSTree::findLCA(int key1, int key2) {
    if (!contains(key1) || !contains(key2)) {
        return nullptr;
    }
    return findLCA(root, key1, key2);
}

int BSTree::getSize() {
    return traverse().size();
}

void BSTree::clear() {
    clear(root);
    root = nullptr;
}

// Приватные методы

Node* BSTree::add(Node* p, const QString& data, int key) {
    if (!p) {
        return new Node(data, key);
    }
    if (key < p->key) {
        p->left = add(p->left, data, key);
    } else if (key > p->key) {
        p->right = add(p->right, data, key);
    }
    return p;
}

Node* BSTree::findMin(Node* p) {
    return p->left ? findMin(p->left) : p;
}

Node* BSTree::remove(Node* p, int key) {
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
        min->right = remove(right, min->key);
        min->left = left;
        return min;
    }
    return p;
}

void BSTree::traverse(Node* p, QVector<Node*>& result) {
    if (!p) return;
    traverse(p->left, result);
    result.append(p);
    traverse(p->right, result);
}

void BSTree::clear(Node* p) {
    if (!p) return;
    clear(p->left);
    clear(p->right);
    delete p;
}

Node* BSTree::copy(Node* p) {
    if (!p) return nullptr;
    Node* newNode = new Node(p->data, p->key);
    newNode->left = copy(p->left);
    newNode->right = copy(p->right);
    return newNode;
}

Node* BSTree::findParent(Node* p, int key, Node* parent) {
    if (!p) return nullptr;
    if (p->key == key) return parent;
    if (key < p->key) return findParent(p->left, key, p);
    return findParent(p->right, key, p);
}

Node* BSTree::findNode(Node* p, int key) {
    if (!p) return nullptr;
    if (p->key == key) return p;
    if (key < p->key) return findNode(p->left, key);
    return findNode(p->right, key);
}

Node* BSTree::findLCA(Node* p, int key1, int key2) {
    if (!p) return nullptr;
    
    if (key1 < p->key && key2 < p->key) {
        return findLCA(p->left, key1, key2);
    }
    
    if (key1 > p->key && key2 > p->key) {
        return findLCA(p->right, key1, key2);
    }
    
    return p;
}