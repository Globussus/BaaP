#include "mainwindow.h"
#include <cstring>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ptr(&ptrInit),
      ref(refInit) {
    setWindowTitle("Задание 1");
    resize(800, 300);
    setMinimumSize(800, 300);
    setMaximumSize(800, 300);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QGridLayout *gridLayout = new QGridLayout(centralWidget);

    QLabel *strLabel = new QLabel("<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">Явная инициализация: </span></p></body></html>", this);
    QLabel *codeLabel = new QLabel("<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">Инициализация в коде: </span></p></body></html>", this);
    QLabel *ptrLabel = new QLabel("<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">Через указатель: </span></p></body></html>", this);
    QLabel *refLabel = new QLabel("<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">Через ссылку: </span></p></body></html>", this);
    QLabel *userLabel = new QLabel("<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">Ввод пользователя: </span></p></body></html>", this);

    strBrowser = new QTextBrowser(this);
    codeBrowser = new QTextBrowser(this);
    ptrBrowser = new QTextBrowser(this);
    refBrowser = new QTextBrowser(this);
    userBrowser = new QTextBrowser(this);

    gridLayout->addWidget(strLabel, 0, 0);
    gridLayout->addWidget(codeLabel, 0, 1);
    gridLayout->addWidget(userLabel, 0, 2);
    gridLayout->addWidget(strBrowser, 1, 0);
    gridLayout->addWidget(codeBrowser, 1, 1);
    gridLayout->addWidget(userBrowser, 1, 2);
    gridLayout->addWidget(ptrLabel, 2, 0);
    gridLayout->addWidget(refLabel, 2, 1);
    gridLayout->addWidget(ptrBrowser, 3, 0);
    gridLayout->addWidget(refBrowser, 3, 1);

    inputButton = new QPushButton("Ввод", this);
    gridLayout->addWidget(inputButton, 4, 0);

    inputDialog = new UserInputDialog(this);
    connect(inputDialog, &UserInputDialog::inputInit, this, &MainWindow::initUserInput);
    connect(inputButton, &QPushButton::clicked, this, &MainWindow::onInputButtonClicked);

    initWithStr();
    initWithCode();
    initWithPtr();
    initWithRef();
}

MainWindow::~MainWindow() {}

void MainWindow::initWithStr() {
    strInit = {15, 1200.5, 'A', true, {0}, {10, 20, 30, 40, 50}};
    strcpy(strInit.name, "Корабль");

    QString str = QString::number(strInit.crewSize) + " | " + QString::number(strInit.displacement) + " | " + strInit.shipClass + " | " + (strInit.isActive ? "true" : "false") + " | " + QString(strInit.name) + " | ";
    for (int i = 0; i < Ship::maxLevelsSize; ++i) {
        str += QString::number(strInit.cargoWeights[i]) + (i == Ship::maxLevelsSize - 1 ? "" : ", ");
    }
    strBrowser->setText(str);
}

void MainWindow::initWithCode() {
    codeInit.crewSize = 20;
    codeInit.displacement = 2500.0;
    codeInit.shipClass = 'B';
    codeInit.isActive = false;
    strcpy(codeInit.name, "Лодка");

    int codeInitCargo[] = {5, 10, 15, 20, 25};
    for (int i = 0; i < Ship::maxLevelsSize; ++i) {
        codeInit.cargoWeights[i] = codeInitCargo[i];
    }

    QString str = QString::number(codeInit.crewSize) + " | " + QString::number(codeInit.displacement) + " | " + codeInit.shipClass + " | " + (codeInit.isActive ? "true" : "false") + " | " + QString(codeInit.name) + " | ";
    for (int i = 0; i < Ship::maxLevelsSize; ++i) {
        str += QString::number(codeInit.cargoWeights[i]) + (i == Ship::maxLevelsSize - 1 ? "" : ", ");
    }
    codeBrowser->setText(str);
}

void MainWindow::initWithPtr() {
    ptr->crewSize = 8;
    ptr->displacement = 800.75;
    ptr->shipClass = 'C';
    ptr->isActive = true;
    strcpy(ptr->name, "Парусник");

    int ptrInitCargo[] = {2, 4, 6, 8, 10};
    for (int i = 0; i < Ship::maxLevelsSize; ++i) {
        ptr->cargoWeights[i] = ptrInitCargo[i];
    }

    QString str = QString::number(ptr->crewSize) + " | " + QString::number(ptr->displacement) + " | " + ptr->shipClass + " | " + (ptr->isActive ? "true" : "false") + " | " + QString(ptr->name) + " | ";
    for (int i = 0; i < Ship::maxLevelsSize; ++i) {
        str += QString::number(ptr->cargoWeights[i]) + (i == Ship::maxLevelsSize - 1 ? "" : ", ");
    }
    ptrBrowser->setText(str);
}

void MainWindow::initWithRef() {
    ref.crewSize = 30;
    ref.displacement = 5000.0;
    ref.shipClass = 'D';
    ref.isActive = true;
    strcpy(ref.name, "Фрегат");

    int refInitCargo[] = {12, 24, 36, 48, 60};
    for (int i = 0; i < Ship::maxLevelsSize; ++i) {
        ref.cargoWeights[i] = refInitCargo[i];
    }

    QString str = QString::number(ref.crewSize) + " | " + QString::number(ref.displacement) + " | " + ref.shipClass + " | " + (ref.isActive ? "true" : "false") + " | " + QString(ref.name) + " | ";
    for (int i = 0; i < Ship::maxLevelsSize; ++i) {
        str += QString::number(ref.cargoWeights[i]) + (i == Ship::maxLevelsSize - 1 ? "" : ", ");
    }
    refBrowser->setText(str);
}

void MainWindow::initUserInput(Ship ship) {
    QString str = QString::number(ship.crewSize) + " | " + QString::number(ship.displacement) + " | " + ship.shipClass + " | " + (ship.isActive ? "true" : "false") + " | " + QString(ship.name) + " | ";
    for (int i = 0; i < Ship::maxLevelsSize; ++i) {
        str += QString::number(ship.cargoWeights[i]) + (i == Ship::maxLevelsSize - 1 ? "" : ", ");
    }
    userBrowser->setText(str);
}

void MainWindow::onInputButtonClicked() {
    inputDialog->setWindowModality(Qt::ApplicationModal);
    inputDialog->show();
}