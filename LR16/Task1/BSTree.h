#ifndef BSTREE_H
#define BSTREE_H

#include <QString>
#include <QVector>
#include <QPair>

struct Node {
    QString data;
    int key;
    Node* left;
    Node* right;
    
    Node(const QString& str, int k) {
        data = str;
        key = k;
        left = right = nullptr;
    }
};

class BSTree {
public:
    BSTree();
    BSTree(const BSTree& other);
    ~BSTree();
    
    BSTree& operator=(const BSTree& other);
    
    // Основные операции
    void add(const QString& data, int key);
    bool remove(int key);
    Node* find(int key);
    bool contains(int key);
    QVector<Node*> traverse(); // in-order обход
    
    // Операции с поддеревьями
    bool insertSubtree(Node* subtreeRoot);
    Node* removeSubtree(int key);
    
    // Операции с ветвями
    bool insertBranch(const QString& data, int key, int parentKey, bool asLeftChild);
    bool removeBranch(int key);
    
    // Вставка в определенную позицию
    bool insertAtPosition(const QString& data, int key, int parentKey, bool asLeftChild);
    
    // Поиск наименьшего общего предка
    Node* findLCA(int key1, int key2);
    
    // Вспомогательные методы
    Node* getRoot() { return root; }
    bool isEmpty() { return root == nullptr; }
    int getSize();
    void clear();

private:
    Node* root;
    
    // Приватные рекурсивные вспомогательные функции
    Node* add(Node* p, const QString& data, int key);
    Node* findMin(Node* p);
    Node* remove(Node* p, int key);
    void traverse(Node* p, QVector<Node*>& result);
    void clear(Node* p);
    Node* copy(Node* p);
    
    Node* findParent(Node* p, int key, Node* parent = nullptr);
    Node* findNode(Node* p, int key);
    Node* findLCA(Node* p, int key1, int key2);
};

#endif // BSTREE_H