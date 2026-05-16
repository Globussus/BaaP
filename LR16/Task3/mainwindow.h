#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QTreeWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include "BstMap.h"
#include "BstSet.h"
#include "UnorderedMap.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    enum class StructureType {
        BST_MAP,
        BST_SET,
        UNORDERED_MAP
    };

    // UI компоненты
    QComboBox* structureCombo;
    QTreeWidget* treeWidget;
    QTableWidget* hashTableWidget;
    QLineEdit* keyInput;
    QLineEdit* valueInput;
    QSpinBox* hashSizeSpin;
    QLabel* sizeLabel;
    QPushButton* insertBtn;
    QPushButton* eraseBtn;
    QPushButton* findByKeyBtn;
    QPushButton* clearBtn;
    QPushButton* randomBtn;
    QPushButton* rehashBtn;
    QPushButton* showIterBtn;

    // Структуры данных
    Map<int, QString> bstMap;
    Set<int> bstSet;
    UnorderedMap<int, QString> unorderedMap;
    StructureType currentStructure;

    void setupUi();
    void initializeSampleData();
    void refreshDisplay();
    void updateTreeView();
    void updateHashTableView();
    void updateStatus();

    template<typename NodeType>
    void addBstNodesToWidget(QTreeWidgetItem* parent, std::shared_ptr<NodeType> node);

    QString getIterOutput();

private slots:
    void onStructureChanged(int index);
    void onInsert();
    void onErase();
    void onFindByKey();
    void onClear();
    void onRandomInsert();
    void onRehash();
    void onShowIter();
};

#endif // MAINWINDOW_H