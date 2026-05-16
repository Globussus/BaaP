#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QTreeWidget>
#include <QGroupBox>
#include <QMessageBox>
#include <QInputDialog>
#include <QHeaderView>
#include <QStatusBar>
#include <memory>
#include "array_heap.h"
#include "list_heap.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onHeapTypeChanged(int index);
    void onPushClicked();
    void onPopClicked();
    void onTopClicked();
    void onClearClicked();
    void onRandomClicked();

private:
    // UI Components
    QWidget* centralWidget;
    QVBoxLayout* mainLayout;
    
    // Панель выбора типа кучи
    QGroupBox* typeGroupBox;
    QHBoxLayout* typeLayout;
    QLabel* typeLabel;
    QComboBox* heapTypeComboBox;
    
    // Панель ввода
    QGroupBox* inputGroupBox;
    QHBoxLayout* inputLayout;
    QLabel* valueLabel;
    QLineEdit* valueLineEdit;
    QPushButton* pushButton;
    QPushButton* popButton;
    QPushButton* topButton;
    QPushButton* clearButton;
    QPushButton* randomButton;
    
    // Панель информации
    QGroupBox* infoGroupBox;
    QHBoxLayout* infoLayout;
    QLabel* sizeLabel;
    QLabel* topLabel;
    QLabel* complexityLabel;
    
    // Отображение кучи
    QTreeWidget* treeWidget;
    
    // Heap instances
    std::unique_ptr<ArrayHeap<int>> arrayHeap;
    std::unique_ptr<ListHeap<int>> listHeap;
    bool usingArrayHeap;
    
    // Helper methods
    void setupUI();
    void updateDisplay();
    void updateTreeDisplay();
    void addNodeToTreeWidget(int index, QTreeWidgetItem* parentItem);
    void showMessage(const QString& title, const QString& message, bool isError = false);
    int getValueFromInput();
    void switchHeapType(bool useArray);
};

#endif // MAINWINDOW_H