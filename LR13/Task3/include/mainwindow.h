#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "bitset.h"

class BitSet;
class QLineEdit;
class QSpinBox;
class QTextEdit;
class String;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override = default;

private slots:
    void onSetBitsetSizeClicked();
    void onAllClicked();
    void onAnyClicked();
    void onNoneClicked();
    void onCountClicked();
    void onSizeClicked();
    void onTestClicked();
    void onSetClicked();
    void onResetClicked();
    void onFlipClicked();
    void onToggleBitClicked();
    void onToULongClicked();
    void onToULongLongClicked();
    void onOperatorNotClicked();
    void onOperatorAndClicked();
    void onOperatorOrClicked();
    void onShiftLeftClicked();
    void onShiftRightClicked();

private:
    void setupUi();
    void updateBitsetDisplay();
    void logResult(const String& msg);
    void logResult(const QString& msg);
    bool parseBitsetFromString(BitSet& bs, const QString& str);

    std::unique_ptr<BitSet> bitset_;
    std::unique_ptr<BitSet> secondBitset_;
    QLineEdit* bitsetInput_;
    QLineEdit* secondBitsetInput_;
    QSpinBox* sizeSpinBox_;
    QSpinBox* indexSpinBox_;
    QTextEdit* resultOutput_;
    QTextEdit* logOutput_;
};

#endif  