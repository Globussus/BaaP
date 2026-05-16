#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QSpinBox>
#include <vector>
#include <string>
#include "hashtable.h"
#include "graphwidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onRunResearch();
    void onAddElement();
    void onRemoveElement();
    void onFindElement();
    void onFillRandom();
    void onClearTable();

private:
    void setupUI();
    void updateTableDisplay();
    void runTimeResearch();

    HashTable<std::string, std::string>* demoTable;

    QLineEdit* keyInput;
    QLineEdit* valueInput;
    QTextEdit* tableDisplay;
    GraphWidget* timeGraph;
    GraphWidget* probeGraph;
    QPushButton* addBtn;
    QPushButton* removeBtn;
    QPushButton* findBtn;
    QPushButton* fillRandomBtn;
    QPushButton* clearBtn;
    QPushButton* researchBtn;
    QSpinBox* fillCountSpin;
    QLabel* statusLabel;
    QLabel* infoLabel;
};

#endif // MAINWINDOW_H