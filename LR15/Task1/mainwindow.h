#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QGroupBox>
#include <QMessageBox>
#include "deque.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onPushBack();
    void onPushFront();
    void onPopBack();
    void onPopFront();
    void onGenerateRandom();
    void onClearDeque();
    void onClearAll();
    void onSolve();
    void updateDisplay();

private:
    Deque deque;
    Deque firstRing;
    Deque secondRing;
    
    QListWidget* dequeList;
    QListWidget* firstRingList;
    QListWidget* secondRingList;
    QSpinBox* valueSpinBox;
    QSpinBox* randomCountSpinBox;
    QPushButton* pushBackBtn;
    QPushButton* pushFrontBtn;
    QPushButton* popBackBtn;
    QPushButton* popFrontBtn;
    QPushButton* generateBtn;
    QPushButton* clearBtn;
    QPushButton* solveBtn;
    
    void setupUI();
    void displayDeque(QListWidget* list, const Deque& d, const QString& emptyMsg);
};

#endif // MAINWINDOW_H