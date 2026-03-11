#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QHeaderView>
#include <QMessageBox>
#include <QVector>
#include "date.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onOpen();
    void onAdd();
    void onCalcNext();
    void onCalcWeek();
    void onCalcDiff();
    void onCalcBday();
    void onDelete();

private:
    QVector<Date*> dates;
    QString filePath;

    QTableWidget *table;
    QLineEdit *bdayInput;
    QLineEdit *newDateInput;

    void updateTableBase();
};
#endif
