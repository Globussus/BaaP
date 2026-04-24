#ifndef USERINPUTDIALOG_H
#define USERINPUTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QHBoxLayout>
#include "ship.h"

class UserInputDialog : public QDialog {
    Q_OBJECT

public:
    explicit UserInputDialog(QWidget *parent = nullptr);
    ~UserInputDialog();

signals:
    void inputInit(Ship ship);

private slots:
    void onButtonBoxAccepted();

private:
    QLineEdit *nameEdit;
    QLineEdit *classEdit;
    QSpinBox *crewSizeSpin;
    QDoubleSpinBox *displacementSpin;
    QCheckBox *activeCheck;
    QSpinBox *cargoSpin0;
    QSpinBox *cargoSpin1;
    QSpinBox *cargoSpin2;
    QSpinBox *cargoSpin3;
    QSpinBox *cargoSpin4;
    QDialogButtonBox *buttonBox;
    Ship input;

    void setupUi();
    bool isValidClass(const char symbol);
};

#endif