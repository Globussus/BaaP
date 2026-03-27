#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QVector>
#include <QPushButton>

class MainWindow: public QMainWindow {
    Q_OBJECT
    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
    private slots:
        void handleFirstTask();
        void handleSecondTask();
        void handleThirdTask();
    private: 
        QLabel *firstTaskLabel;
        QLabel *secondTaskLabel;
        QLabel *thirdTaskLabel;
};

#endif