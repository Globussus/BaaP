#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include "AVLTree.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddButtonClicked();
    void onRemoveButtonClicked();
    void onFindButtonClicked();
    void onBalanceButtonClicked();
    void onClearButtonClicked();
    void onLoadArrayButtonClicked();
    void onRandomButtonClicked();
    void onShowPreOrder();
    void onShowPostOrder();
    void onShowInOrder();
    void onCountCharacters();

private:
    AVLTree tree;
    
    QTreeWidget* treeWidget;
    QLineEdit* keyLineEdit;
    QLineEdit* dataLineEdit;
    QLabel* statusLabel;
    QLabel* charCountLabel;
    
    void setupUI();
    void updateTreeDisplay();
    void addNodeToTreeWidget(Node* node, QTreeWidgetItem* parentItem);
    void updateStatus();
    void updateCharCount();
};

#endif