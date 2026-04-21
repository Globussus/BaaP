#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include "myString.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() = default;

private slots:
    void executeFunction();

private:
    QComboBox* functionSelector;
    QLineEdit* input1;
    QLineEdit* input2;
    QLineEdit* inputNumber;
    QPushButton* executeButton;
    QTextEdit* outputLog;

    void setupUi();
    void logMessage(const QString& msg);
};

#endif