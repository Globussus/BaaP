#ifndef AVLTREE_H
#define AVLTREE_H

#include <QString>
#include <QVector>

struct Node {
    QString data;
    int key;
    unsigned char height;
    Node* left;
    Node* right;
    
    Node(const QString& str, int k) {
        data = str;
        key = k;
        left = right = nullptr;
        height = 1;
    }
};

class AVLTree {
public:
    AVLTree();
    AVLTree(const AVLTree& other);
    ~AVLTree();
    
    AVLTree& operator=(const AVLTree& other);
    
    void insert(const QString& data, int key);
    bool remove(int key);
    Node* find(int key);
    bool contains(int key);
    
    QVector<Node*> getInOrder();
    QVector<Node*> getPreOrder();
    QVector<Node*> getPostOrder();
    
    Node* getRoot() { return root; }
    bool isEmpty() { return root == nullptr; }
    int getSize();
    void clear();
    
    int getTotalCharacters();

private:
    Node* root;

    unsigned char getHeight(Node* p);
    int getBalanceFactor(Node* p);
    void fixHeight(Node* p);
    Node* rotateRight(Node* p);
    Node* rotateLeft(Node* q);
    Node* balance(Node* p);
    Node* insert(Node* p, const QString& data, int key);
    Node* findMin(Node* p);
    Node* removeMin(Node* p);
    Node* remove(Node* p, int key);
    
    void inOrder(Node* p, QVector<Node*>& result);
    void preOrder(Node* p, QVector<Node*>& result);
    void postOrder(Node* p, QVector<Node*>& result);
    void clear(Node* p);
    Node* copy(Node* p);
    
    int countTotalCharacters(Node* p);
};

#endif