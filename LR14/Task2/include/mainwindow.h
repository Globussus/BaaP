#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QLabel>
#include "ship.h"
#include "userinputdialog.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onExecuteClicked();
    void onUserInputShip(Ship ship);

private:
    QComboBox *menuCombo;
    QPushButton *executeButton;
    QTextEdit *outputText;
    UserInputDialog *inputDialog;
    bool writingToBin;

    void writeTextFile();
    void readTextFile();
    void writeArrayFile();
    void readArrayFile();
    void readShipTextFile();
    void readShipBinFile();
    void appendSentenceFile();
    void readLinesFile();
};

#endif