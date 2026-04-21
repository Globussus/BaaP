#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include "keyboard.h"
#include "text.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Text *text;
    Keyboard *keyboard;
    QTimer *timer;
    QLabel *timerLabel;
    QLabel *wordsPerMinute;
    QPushButton *openFileButton;
    int seconds;

private slots:
    void changeLanguage(const QString &item);
    void statusUpdate();
    void openFile();
};

#endif