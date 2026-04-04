#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QTextEdit>
#include "vector.h"
#include "pair.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void demonstratePushBack();
    void demonstratePopBack();
    void demonstrateInsert();
    void demonstrateErase();
    void demonstrateResize();
    void demonstrateClear();
    void demonstrateAssign();
    void demonstrateSwap();
    void demonstrateAt();
    void demonstrateFrontBack();

private:
    void setupUI();
    void connectSignals();
    void updateTables();
    
    Pair<Vector<int>, Vector<Pair<int, double>>> data_;

    QTableWidget *table1_;
    QTableWidget *table2_;
    QLabel *nestedLabel_;
    QComboBox *vectorSelector;
    
    QPushButton *btnPushBack, *btnPopBack, *btnInsert, *btnErase, 
                *btnResize, *btnClear, *btnAssign, *btnSwap, 
                *btnAt, *btnFrontBack, *btnReserve, *btnNested;
};

#endif