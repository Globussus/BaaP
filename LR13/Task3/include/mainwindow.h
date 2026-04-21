#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bitset.h"
#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QCheckBox>
#include <QLabel>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() = default;

private slots:
    void onAllClicked();
    void onAnyClicked();
    void onNoneClicked();
    void onCountClicked();
    void onSizeClicked();
    void onTestClicked();
    void onResetClicked();
    void onSetClicked();
    void onFlipClicked();
    void onToULongClicked();
    void onToULongLongClicked();
    void onOperatorNotClicked();
    void onOperatorAndClicked();
    void onOperatorOrClicked();
    void onShiftLeftClicked();
    void onShiftRightClicked();
    void onSetBitsetSizeClicked();
    void onToggleBitClicked();

private:
    void setupUi();
    void updateBitsetDisplay();
    void logResult(const String& msg);
    void logResult(const QString& msg);

    QLineEdit* bitsetInput_;
    QLineEdit* secondBitsetInput_;
    QTextEdit* resultOutput_;
    QTextEdit* logOutput_;
    QSpinBox* indexSpinBox_;
    QSpinBox* sizeSpinBox_;
    QCheckBox* useIndexCheckBox_;
    
    std::unique_ptr<BitSet> bitset_;
    std::unique_ptr<BitSet> secondBitset_;
};

#endif