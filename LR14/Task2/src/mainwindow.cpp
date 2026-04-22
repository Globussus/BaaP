#include "mainwindow.h"
#include <QApplication>
#include <QInputDialog>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), writingToBin(false) {
    setWindowTitle("Лабораторная работа 20");
    resize(800, 600);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QLabel *titleLabel = new QLabel("Меню", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    menuCombo = new QComboBox(this);
    menuCombo->addItem("1. Запись абзаца текста");
    menuCombo->addItem("2. Чтение текста");
    menuCombo->addItem("3. Запись массива char");
    menuCombo->addItem("4. Чтение массива char");
    menuCombo->addItem("5. Запись структуры Ship в текстовый файл");
    menuCombo->addItem("6. Чтение структур Ship из текстового файла");
    menuCombo->addItem("7. Запись структуры Ship в бинарный файл");
    menuCombo->addItem("8. Чтение структур Ship из бинарного файла");
    menuCombo->addItem("9. Дозапись предложения");
    menuCombo->addItem("10. Чтение строк");
    menuCombo->addItem("11. Выход");
    mainLayout->addWidget(menuCombo);

    executeButton = new QPushButton("Выполнить", this);
    mainLayout->addWidget(executeButton);

    outputText = new QTextEdit(this);
    outputText->setReadOnly(true);
    mainLayout->addWidget(outputText);

    inputDialog = new UserInputDialog(this);
    connect(inputDialog, &UserInputDialog::inputInit, this, &MainWindow::onUserInputShip);
    connect(executeButton, &QPushButton::clicked, this, &MainWindow::onExecuteClicked);
}

MainWindow::~MainWindow() {}

void MainWindow::onExecuteClicked() {
    int index = menuCombo->currentIndex();
    switch (index) {
        case 0:
            writeTextFile();
            break;
        case 1:
            readTextFile();
            break;
        case 2:
            writeArrayFile();
            break;
        case 3:
            readArrayFile();
            break;
        case 4:
            writingToBin = false;
            inputDialog->setWindowModality(Qt::ApplicationModal);
            inputDialog->show();
            break;
        case 5:
            readShipTextFile();
            break;
        case 6:
            writingToBin = true;
            inputDialog->setWindowModality(Qt::ApplicationModal);
            inputDialog->show();
            break;
        case 7:
            readShipBinFile();
            break;
        case 8:
            appendSentenceFile();
            break;
        case 9:
            readLinesFile();
            break;
        case 10:
            QApplication::quit();
            break;
    }
}

void MainWindow::writeTextFile() {
    bool ok;
    QString text = QInputDialog::getText(this, "Ввод текста", "Введите абзац текста:", QLineEdit::Normal, "", &ok);
    if (!ok) return;

    std::wofstream wfile("ГлобажЛаб20.txt");
    wfile.imbue(std::locale(""));
    std::wstring wstr = text.toStdWString();
    for (wchar_t wc : wstr) {
        wfile << wc;
    }
    wfile.close();
    outputText->append("Текст записан в ГлобажЛаб20.txt");
}

void MainWindow::readTextFile() {
    std::wifstream wfile("ГлобажЛаб20.txt");
    if (!wfile.is_open()) {
        outputText->append("Ошибка открытия файла ГлобажЛаб20.txt");
        return;
    }
    wfile.imbue(std::locale(""));
    std::wstring wstr;
    wchar_t wc;
    while (wfile.get(wc)) {
        wstr += wc;
    }
    wfile.close();
    outputText->append("Содержимое ГлобажЛаб20.txt:");
    outputText->append(QString::fromStdWString(wstr));
}

void MainWindow::writeArrayFile() {
    bool ok;
    int size = QInputDialog::getInt(this, "Размер массива", "Введите размер массива:", 1, 1, 100, 1, &ok);
    if (!ok) return;

    QString elements = QInputDialog::getText(this, "Элементы массива", "Введите элементы через '-':", QLineEdit::Normal, "", &ok);
    if (!ok) return;

    std::ofstream file("ГлобажЛаб20_0.txt");
    QStringList list = elements.split('-');
    int count = std::min(size, static_cast<int>(list.size()));
    for (int i = 0; i < count; ++i) {
        if (list[i].size() > 0) {
            file << list[i].toStdString()[0];
            if (i < count - 1) {
                file << '-';
            }
        }
    }
    file.close();
    outputText->append("Массив записан в ГлобажЛаб20_0.txt");
}

void MainWindow::readArrayFile() {
    std::ifstream file("ГлобажЛаб20_0.txt");
    if (!file.is_open()) {
        outputText->append("Ошибка открытия файла ГлобажЛаб20_0.txt");
        return;
    }
    char ch;
    QString result;
    while (file >> ch) {
        if (ch != '-') {
            result += ch;
            result += ' ';
        }
    }
    file.close();
    outputText->append("Массив из ГлобажЛаб20_0.txt:");
    outputText->append(result);
}

void MainWindow::onUserInputShip(Ship ship) {
    if (writingToBin) {
        std::ofstream file("ГлобажЛаб20_2.bin", std::ios::app | std::ios::binary);
        file.write(reinterpret_cast<char*>(&ship), sizeof(Ship));
        file.close();
        outputText->append("Структура записана в ГлобажЛаб20_2.bin");
    } else {
        std::ofstream file("ГлобажЛаб20_1.txt", std::ios::app);
        file << ship.crewSize << ' '
             << ship.displacement << ' '
             << ship.shipClass << ' '
             << (ship.isActive ? 1 : 0) << ' '
             << ship.name << ' ';
        for (int i = 0; i < Ship::maxLevelsSize; ++i) {
            file << ship.cargoWeights[i];
            if (i < Ship::maxLevelsSize - 1) {
                file << ' ';
            }
        }
        file << '\n';
        file.close();
        outputText->append("Структура записана в ГлобажЛаб20_1.txt");
    }
}

void MainWindow::readShipTextFile() {
    std::ifstream file("ГлобажЛаб20_1.txt");
    if (!file.is_open()) {
        outputText->append("Ошибка открытия файла ГлобажЛаб20_1.txt");
        return;
    }
    outputText->append("Структуры из ГлобажЛаб20_1.txt:");
    Ship ship;
    int activeInt;
    while (file >> ship.crewSize >> ship.displacement >> ship.shipClass >> activeInt >> ship.name) {
        ship.isActive = activeInt;
        for (int i = 0; i < Ship::maxLevelsSize; ++i) {
            file >> ship.cargoWeights[i];
        }
        QString str = QString::number(ship.crewSize) + "|"
                    + QString::number(ship.displacement) + "|"
                    + ship.shipClass + "|"
                    + (ship.isActive ? "true" : "false") + "|"
                    + QString(ship.name) + "|";
        for (int i = 0; i < Ship::maxLevelsSize; ++i) {
            str += QString::number(ship.cargoWeights[i]);
            if (i < Ship::maxLevelsSize - 1) {
                str += ",";
            }
        }
        outputText->append(str);
    }
    file.close();
}

void MainWindow::readShipBinFile() {
    std::ifstream file("ГлобажЛаб20_2.bin", std::ios::binary);
    if (!file.is_open()) {
        outputText->append("Ошибка открытия файла ГлобажЛаб20_2.bin");
        return;
    }
    outputText->append("Структуры из ГлобажЛаб20_2.bin:");
    Ship ship;
    while (file.read(reinterpret_cast<char*>(&ship), sizeof(Ship))) {
        QString str = QString::number(ship.crewSize) + ";"
                    + QString::number(ship.displacement) + ";"
                    + ship.shipClass + ";"
                    + (ship.isActive ? "true" : "false") + ";"
                    + QString(ship.name) + ";";
        for (int i = 0; i < Ship::maxLevelsSize; ++i) {
            str += QString::number(ship.cargoWeights[i]);
            if (i < Ship::maxLevelsSize - 1) {
                str += ",";
            }
        }
        outputText->append(str);
    }
    file.close();
}

void MainWindow::appendSentenceFile() {
    bool ok;
    QString sentence = QInputDialog::getText(this, "Ввод предложения", "Введите предложение:", QLineEdit::Normal, "", &ok);
    if (!ok) return;

    std::ofstream file("ГлобажЛаб20_3.txt", std::ios::app);
    file << sentence.toStdString() << '\n';
    file.close();
    outputText->append("Предложение добавлено в ГлобажЛаб20_3.txt");
}

void MainWindow::readLinesFile() {
    std::ifstream file("ГлобажЛаб20_3.txt");
    if (!file.is_open()) {
        outputText->append("Ошибка открытия файла ГлобажЛаб20_3.txt");
        return;
    }
    outputText->append("Строки из ГлобажЛаб20_3.txt:");
    std::string line;
    while (std::getline(file, line)) {
        outputText->append(QString::fromStdString(line));
    }
    file.close();
}