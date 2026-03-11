#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include "student.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleLoad();
    void handleSave();
    void handleAdd();
    void handleDelete();
    void handleSortAll();
    void handleSortGroup();
    void handleSearch();
    void showGoodStudents();

private:
    QVector<Student*> data;
    QTextEdit *display;
    QLineEdit *inputFio;
    void refreshDisplay(const QVector<Student *> &list);
};

#endif
