#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QRandomGenerator>
#include "derivedhashtable.h"

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() {}

private slots:
    void onAddClicked();
    void onRemoveClicked();
    void onFindClicked();
    void onFillRandomClicked();
    void onFindMaxClicked();
    void onPrintClicked();

private:
    DerivedHashTable<std::string, std::string> hashTable;

    QTextEdit* outputText;
    QLineEdit* keyInput;
    QLineEdit* valueInput;
    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* findButton;
    QPushButton* fillRandomButton;
    QPushButton* findMaxButton;
    QPushButton* printButton;

    void setupUi();
    void printToOutput(const std::string& text);
};

#endif // MAINWINDOW_H