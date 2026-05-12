#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStatusBar>
#include <QMessageBox>
#include "deque.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private:
    Deque<int> deque;

    QListWidget *listWidget;
    QLabel *lblSize;
    QLabel *lblEmpty;
    
    QSpinBox *spinValue;
    QSpinBox *spinIndex;
    
    QPushButton *btnPushBack;
    QPushButton *btnPushFront;
    QPushButton *btnPopBack;
    QPushButton *btnPopFront;
    QPushButton *btnClear;
    QPushButton *btnAt;
    QPushButton *btnIteratorDemo;

private slots:
    void onPushBack();
    void onPushFront();
    void onPopBack();
    void onPopFront();
    void onClear();
    void onAt();
    void onIteratorDemo();

private:
    void setupUI();
    void updateDisplay();
    void updateStatusBar();
    void showMessage(const QString &title, const QString &message);
};

#endif // MAINWINDOW_H