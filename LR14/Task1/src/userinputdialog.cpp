#include "userinputdialog.h"

UserInputDialog::UserInputDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Ввод данных");
    resize(576, 337);
    setupUi();
}

UserInputDialog::~UserInputDialog() {}

void UserInputDialog::setupUi() {
    QGridLayout *gridLayout = new QGridLayout(this);

    QLabel *nameLabel = new QLabel("Название:", this);
    nameEdit = new QLineEdit(this);
    nameEdit->setMaxLength(Ship::maxNameSize - 1);
    gridLayout->addWidget(nameLabel, 0, 0);
    gridLayout->addWidget(nameEdit, 0, 1);

    QLabel *crewLabel = new QLabel("Экипаж:", this);
    crewSizeSpin = new QSpinBox(this);
    crewSizeSpin->setMaximum(999);
    gridLayout->addWidget(crewLabel, 1, 0);
    gridLayout->addWidget(crewSizeSpin, 1, 1);

    QLabel *classLabel = new QLabel("Класс:", this);
    classEdit = new QLineEdit(this);
    classEdit->setMaxLength(1);
    gridLayout->addWidget(classLabel, 2, 0);
    gridLayout->addWidget(classEdit, 2, 1);

    QLabel *displacementLabel = new QLabel("Водоизмещение:", this);
    displacementSpin = new QDoubleSpinBox(this);
    displacementSpin->setMaximum(99999.99);
    gridLayout->addWidget(displacementLabel, 3, 0);
    gridLayout->addWidget(displacementSpin, 3, 1);

    QLabel *activeLabel = new QLabel("Активен:", this);
    activeCheck = new QCheckBox(this);
    gridLayout->addWidget(activeLabel, 4, 0);
    gridLayout->addWidget(activeCheck, 4, 1);

    QLabel *cargoLabel = new QLabel("Вес груза:", this);
    QHBoxLayout *cargoLayout = new QHBoxLayout();
    cargoSpin0 = new QSpinBox(this);
    cargoSpin1 = new QSpinBox(this);
    cargoSpin2 = new QSpinBox(this);
    cargoSpin3 = new QSpinBox(this);
    cargoSpin4 = new QSpinBox(this);
    cargoSpin0->setMaximum(9999);
    cargoSpin1->setMaximum(9999);
    cargoSpin2->setMaximum(9999);
    cargoSpin3->setMaximum(9999);
    cargoSpin4->setMaximum(9999);
    cargoLayout->addWidget(cargoSpin0);
    cargoLayout->addWidget(cargoSpin1);
    cargoLayout->addWidget(cargoSpin2);
    cargoLayout->addWidget(cargoSpin3);
    cargoLayout->addWidget(cargoSpin4);
    gridLayout->addWidget(cargoLabel, 5, 0);
    gridLayout->addLayout(cargoLayout, 5, 1);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    gridLayout->addWidget(buttonBox, 6, 0, 1, 2);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &UserInputDialog::onButtonBoxAccepted);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void UserInputDialog::onButtonBoxAccepted() {
    if (nameEdit->text().isEmpty() || classEdit->text().isEmpty()) {
        QMessageBox::information(nullptr, "Неверный ввод", "Все поля должны быть заполнены", QMessageBox::Ok | QMessageBox::NoButton);
        return;
    }

    QByteArray utf8Name = nameEdit->text().toUtf8();
    int len = utf8Name.length();
    for (int i = 0; i < len; ++i) {
        input.name[i] = utf8Name.at(i);
    }
    input.name[len] = '\0';

    input.crewSize = crewSizeSpin->value();
    input.displacement = displacementSpin->value();
    QString classStr = classEdit->text();
    input.shipClass = isValidClass(classStr.at(0).toLatin1()) ? classStr.at(0).toLatin1() : 'E';
    input.isActive = activeCheck->isChecked();

    input.cargoWeights[0] = cargoSpin0->value();
    input.cargoWeights[1] = cargoSpin1->value();
    input.cargoWeights[2] = cargoSpin2->value();
    input.cargoWeights[3] = cargoSpin3->value();
    input.cargoWeights[4] = cargoSpin4->value();

    emit inputInit(input);
    close();
}

bool UserInputDialog::isValidClass(const char symbol) {
    switch(symbol){
        case 'A':
        case 'a':
        case 'B':
        case 'b':
        case 'C':
        case 'c':
        case 'D':
        case 'd':
        case 'E':
        case 'e':
            return true;
        default:
            return false;
    }
}