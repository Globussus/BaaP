#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QLabel>
#include "vector.h"
#include "pair.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onPushBack();
    void onPopBack();
    void onClear();
    void onResize();
    void onInsert();
    void onErase();
    void onAt();
    void onFrontBack();
    void onAssign();

    void onPairMake();
    void onPairSetFirst();
    void onPairSetSecond();
    void onShowNested();

private:
    void setupUI();
    void refreshGrids();

    Vector<Pair<Vector<int>, Vector<Pair<int, double>>>> mainData;
    
    QWidget* centralWidget;
    QTableWidget *tableInts;
    QTableWidget *tablePairs;
};

#endif