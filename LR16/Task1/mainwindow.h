#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "BSTree.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onAddClicked();
    void onRemoveClicked();
    void onFindClicked();
    void onTraverseClicked();
    void onInsertSubtreeClicked();
    void onRemoveSubtreeClicked();
    void onInsertBranchClicked();
    void onRemoveBranchClicked();
    void onInsertAtPositionClicked();
    void onFindLCAClicked();
    void onClearClicked();

private:
    void setupUI();
    void updateTreeDisplay();
    void updateStatus();
    void addNodeToTreeWidget(Node* node, QTreeWidgetItem* parentItem);

    BSTree tree;
    Node* extractedSubtree;

    QTreeWidget* treeWidget;
    QLineEdit* keyLineEdit;
    QLineEdit* dataLineEdit;
    QLineEdit* parentKeyLineEdit;
    QLineEdit* childKeyLineEdit;
    QLineEdit* key1LineEdit;
    QLineEdit* key2LineEdit;
    QLabel* statusLabel;
    QLabel* subtreeStatusLabel;  // Новая метка для отображения статуса поддерева
};

#endif // MAINWINDOW_H