#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QDateTime>
#include <random>
#include <set>
#include <algorithm>
#include <chrono>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    demoTable = new HashTable<std::string, std::string>(16);
    setupUI();
    updateTableDisplay();
}

MainWindow::~MainWindow() {
    delete demoTable;
}

void MainWindow::setupUI() {
    setWindowTitle("Хеш-таблица — Открытая адресация");
    resize(1100, 700);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    // Левая панель
    QVBoxLayout* leftLayout = new QVBoxLayout();

    // Операции
    QGroupBox* operationsGroup = new QGroupBox("Операции");
    QVBoxLayout* opLayout = new QVBoxLayout(operationsGroup);

    QHBoxLayout* keyLayout = new QHBoxLayout();
    keyLayout->addWidget(new QLabel("Ключ:"));
    keyInput = new QLineEdit();
    keyLayout->addWidget(keyInput);
    opLayout->addLayout(keyLayout);

    QHBoxLayout* valueLayout = new QHBoxLayout();
    valueLayout->addWidget(new QLabel("Значение:"));
    valueInput = new QLineEdit();
    valueLayout->addWidget(valueInput);
    opLayout->addLayout(valueLayout);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    addBtn = new QPushButton("Добавить");
    removeBtn = new QPushButton("Удалить");
    findBtn = new QPushButton("Найти");
    btnLayout->addWidget(addBtn);
    btnLayout->addWidget(removeBtn);
    btnLayout->addWidget(findBtn);
    opLayout->addLayout(btnLayout);

    // Заполнение
    QHBoxLayout* fillLayout = new QHBoxLayout();
    fillLayout->addWidget(new QLabel("Элементов:"));
    fillCountSpin = new QSpinBox();
    fillCountSpin->setRange(1, 5000);
    fillCountSpin->setValue(10);
    fillLayout->addWidget(fillCountSpin);
    fillRandomBtn = new QPushButton("Заполнить");
    fillLayout->addWidget(fillRandomBtn);
    clearBtn = new QPushButton("Очистить");
    fillLayout->addWidget(clearBtn);
    opLayout->addLayout(fillLayout);

    infoLabel = new QLabel("Размер: 16 | Элементов: 0 | Загрузка: 0.00");
    opLayout->addWidget(infoLabel);

    statusLabel = new QLabel("Готово");
    statusLabel->setStyleSheet("QLabel { color: blue; }");
    opLayout->addWidget(statusLabel);

    leftLayout->addWidget(operationsGroup);

    // Отображение таблицы
    QGroupBox* displayGroup = new QGroupBox("Содержимое таблицы");
    QVBoxLayout* displayLayout = new QVBoxLayout(displayGroup);
    tableDisplay = new QTextEdit();
    tableDisplay->setReadOnly(true);
    tableDisplay->setFont(QFont("Courier New", 9));
    tableDisplay->setMinimumHeight(150);
    displayLayout->addWidget(tableDisplay);
    leftLayout->addWidget(displayGroup);

    // Кнопка исследования
    researchBtn = new QPushButton("Запустить исследование");
    researchBtn->setMinimumHeight(35);
    researchBtn->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; font-weight: bold; font-size: 14px; }");
    leftLayout->addWidget(researchBtn);

    mainLayout->addLayout(leftLayout, 1);

    // Правая панель — графики
    QVBoxLayout* rightLayout = new QVBoxLayout();

    QGroupBox* timeGroup = new QGroupBox("Среднее время поиска");
    QVBoxLayout* timeLayout = new QVBoxLayout(timeGroup);
    timeGraph = new GraphWidget();
    timeGraph->setMinimumHeight(280);
    timeLayout->addWidget(timeGraph);
    rightLayout->addWidget(timeGroup);

    QGroupBox* probeGroup = new QGroupBox("Среднее число проб");
    QVBoxLayout* probeLayout = new QVBoxLayout(probeGroup);
    probeGraph = new GraphWidget();
    probeGraph->setMinimumHeight(280);
    probeLayout->addWidget(probeGraph);
    rightLayout->addWidget(probeGroup);

    mainLayout->addLayout(rightLayout, 2);

    // Сигналы
    connect(addBtn, &QPushButton::clicked, this, &MainWindow::onAddElement);
    connect(removeBtn, &QPushButton::clicked, this, &MainWindow::onRemoveElement);
    connect(findBtn, &QPushButton::clicked, this, &MainWindow::onFindElement);
    connect(fillRandomBtn, &QPushButton::clicked, this, &MainWindow::onFillRandom);
    connect(clearBtn, &QPushButton::clicked, this, &MainWindow::onClearTable);
    connect(researchBtn, &QPushButton::clicked, this, &MainWindow::onRunResearch);
}

void MainWindow::updateTableDisplay() {
    tableDisplay->setPlainText(QString::fromStdString(demoTable->print()));
    double lf = static_cast<double>(demoTable->getElementCount()) / demoTable->getBufferSize();
    infoLabel->setText(QString("Размер: %1 | Элементов: %2 | Загрузка: %3")
        .arg(demoTable->getBufferSize())
        .arg(demoTable->getElementCount())
        .arg(lf, 0, 'f', 2));
}

void MainWindow::onAddElement() {
    std::string key = keyInput->text().toStdString();
    std::string value = valueInput->text().toStdString();

    if (key.empty()) {
        statusLabel->setText("Ошибка: ключ не может быть пустым");
        return;
    }

    if (demoTable->add(key, value)) {
        statusLabel->setText(QString("Добавлено: [%1 : %2]").arg(key.c_str()).arg(value.c_str()));
    } else {
        statusLabel->setText(QString("Ошибка: ключ '%1' уже существует").arg(key.c_str()));
    }
    updateTableDisplay();
}

void MainWindow::onRemoveElement() {
    std::string key = keyInput->text().toStdString();
    if (key.empty()) {
        statusLabel->setText("Ошибка: ключ не может быть пустым");
        return;
    }
    if (demoTable->remove(key)) {
        statusLabel->setText(QString("Удалён: %1").arg(key.c_str()));
    } else {
        statusLabel->setText(QString("Не найден: %1").arg(key.c_str()));
    }
    updateTableDisplay();
}

void MainWindow::onFindElement() {
    std::string key = keyInput->text().toStdString();
    if (key.empty()) {
        statusLabel->setText("Ошибка: ключ не может быть пустым");
        return;
    }

    std::vector<int> probes = demoTable->getProbeSequence(key);
    std::string* val = demoTable->find(key);
    if (val != nullptr) {
        QString pstr;
        for (size_t i = 0; i < probes.size(); ++i) {
            pstr += QString::number(probes[i]);
            if (i < probes.size() - 1) pstr += " → ";
        }
        statusLabel->setText(QString("Найден: %1 → %2 | Пробы: %3 (всего %4)")
            .arg(key.c_str()).arg(val->c_str()).arg(pstr).arg(probes.size()));
    } else {
        statusLabel->setText(QString("Не найден: %1 | Проверено ячеек: %2").arg(key.c_str()).arg(probes.size()));
    }
}

void MainWindow::onFillRandom() {
    int count = fillCountSpin->value();
    int maxCanAdd = static_cast<int>(demoTable->getBufferSize() * 0.75) - demoTable->getElementCount();
    if (count > maxCanAdd) count = maxCanAdd;
    if (count <= 0) {
        statusLabel->setText("Таблица заполнена");
        return;
    }

    std::mt19937 rng(static_cast<unsigned>(QDateTime::currentMSecsSinceEpoch()));
    int added = 0;
    for (int i = 0; i < count; ++i) {
        std::string key = std::to_string(rng() % 99999);
        std::string value = std::to_string(rng() % 99999);
        if (demoTable->add(key, value)) {
            ++added;
        }
    }
    statusLabel->setText(QString("Добавлено %1 случайных элементов").arg(added));
    updateTableDisplay();
}

void MainWindow::onClearTable() {
    delete demoTable;
    demoTable = new HashTable<std::string, std::string>(16);
    statusLabel->setText("Таблица очищена");
    updateTableDisplay();
}

void MainWindow::onRunResearch() {
    statusLabel->setText("Идёт исследование...");
    researchBtn->setEnabled(false);
    QApplication::processEvents();
    runTimeResearch();
    researchBtn->setEnabled(true);
    statusLabel->setText("Исследование завершено");
}

void MainWindow::runTimeResearch() {
    QVector<int> sizes = {16, 64, 128, 2048};
    QVector<double> times;
    QVector<double> probes;
    const int searches = 500;

    std::mt19937 rng(42); // фиксированный seed для повторяемости

    for (int size : sizes) {
        HashTable<std::string, std::string> ht(size);
        std::set<std::string> keys;

        // Заполняем таблицу на 60%
        int toFill = size * 0.6;
        for (int i = 0; i < toFill; ++i) {
            std::string k;
            do {
                k = std::to_string(rng() % 1000000);
            } while (keys.count(k));
            keys.insert(k);
            ht.add(k, std::to_string(rng() % 1000));
        }

        // Ключи для поиска
        std::vector<std::string> searchKeys;
        int n = 0;
        for (const auto& k : keys) {
            if (n >= searches / 2) break;
            searchKeys.push_back(k);
            ++n;
        }
        while (static_cast<int>(searchKeys.size()) < searches) {
            std::string k = "nx" + std::to_string(rng() % 1000000);
            if (!keys.count(k)) searchKeys.push_back(k);
        }
        std::shuffle(searchKeys.begin(), searchKeys.end(), rng);

        // Замер времени
        auto t1 = std::chrono::high_resolution_clock::now();
        for (const auto& k : searchKeys) {
            ht.find(k);
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        double ns = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
        times.append(ns / searches);

        // Замер проб
        double totalP = 0;
        for (const auto& k : searchKeys) {
            totalP += ht.getProbeSequence(k).size();
        }
        probes.append(totalP / searches);
    }

    QVector<double> x;
    for (int s : sizes) x.append(s);

    timeGraph->setData(x, times,
        "Среднее время поиска от размера таблицы",
        "Размер таблицы", "Время (нс)", QColor(70, 130, 180));

    probeGraph->setData(x, probes,
        "Среднее число проб от размера таблицы",
        "Размер таблицы", "Число проб", QColor(220, 80, 60));
}