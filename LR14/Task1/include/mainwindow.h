#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextBrowser>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QWidget>
#include "ship.h"
#include "userinputdialog.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initUserInput(Ship ship);

private slots:
    void onInputButtonClicked();

private:
    Ship strInit;
    Ship codeInit;
    Ship ptrInit;
    Ship refInit;
    Ship *ptr;
    Ship &ref;

    QTextBrowser *strBrowser;
    QTextBrowser *codeBrowser;
    QTextBrowser *ptrBrowser;
    QTextBrowser *refBrowser;
    QTextBrowser *userBrowser;
    QPushButton *inputButton;
    UserInputDialog *inputDialog;

    void initWithStr();
    void initWithCode();
    void initWithPtr();
    void initWithRef();
};

#endif