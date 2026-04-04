#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QInputDialog>
#include <QMessageBox>
#include <QComboBox>
#include <QStringList>
#include <stdexcept>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Vector и Pair");
    resize(1200, 850);
    
    setupUI();
    connectSignals();
    updateTables();
}

MainWindow::~MainWindow() = default;

void MainWindow::setupUI() {
    auto* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    auto* mainLayout = new QVBoxLayout(centralWidget);

    auto* selectorGroup = new QGroupBox("Выбор контейнера для операций");
    auto* selectorLayout = new QHBoxLayout(selectorGroup);
    vectorSelector = new QComboBox();
    vectorSelector->addItem("(Vector<int>)", 0);
    vectorSelector->addItem("(Vector<Pair<int, double>>)", 1);
    selectorLayout->addWidget(new QLabel("Работать с:"));
    selectorLayout->addWidget(vectorSelector);
    mainLayout->addWidget(selectorGroup);

    auto* tablesLayout = new QHBoxLayout();
    table1_ = new QTableWidget();
    table2_ = new QTableWidget();
    tablesLayout->addWidget(table1_);
    tablesLayout->addWidget(table2_);
    mainLayout->addLayout(tablesLayout);

    auto* btnGroup = new QGroupBox("Методы управления");
    auto* grid = new QGridLayout(btnGroup);

    btnPushBack = new QPushButton("Push Back");
    btnPopBack = new QPushButton("Pop Back");
    btnInsert = new QPushButton("Insert");
    btnErase = new QPushButton("Erase");
    btnResize = new QPushButton("Resize");
    btnClear = new QPushButton("Clear");
    btnAssign = new QPushButton("Assign");
    btnSwap = new QPushButton("Swap");
    btnAt = new QPushButton("At");
    btnFrontBack = new QPushButton("Front/Back");
    btnReserve = new QPushButton("Reserve");

    grid->addWidget(btnPushBack, 0, 0); grid->addWidget(btnPopBack, 0, 1); grid->addWidget(btnInsert, 0, 2);
    grid->addWidget(btnErase, 1, 0);   grid->addWidget(btnResize, 1, 1); grid->addWidget(btnClear, 1, 2);
    grid->addWidget(btnAssign, 2, 0);  grid->addWidget(btnSwap, 2, 1);   grid->addWidget(btnAt, 2, 2);
    grid->addWidget(btnFrontBack, 3, 0); grid->addWidget(btnReserve, 3, 1);
    
    mainLayout->addWidget(btnGroup);
}

void MainWindow::connectSignals() {
    connect(btnPushBack, &QPushButton::clicked, this, &MainWindow::demonstratePushBack);
    connect(btnPopBack, &QPushButton::clicked, this, &MainWindow::demonstratePopBack);
    connect(btnInsert, &QPushButton::clicked, this, &MainWindow::demonstrateInsert);
    connect(btnErase, &QPushButton::clicked, this, &MainWindow::demonstrateErase);
    connect(btnResize, &QPushButton::clicked, this, &MainWindow::demonstrateResize);
    connect(btnClear, &QPushButton::clicked, this, &MainWindow::demonstrateClear);
    connect(btnAssign, &QPushButton::clicked, this, &MainWindow::demonstrateAssign);
    connect(btnSwap, &QPushButton::clicked, this, &MainWindow::demonstrateSwap);
    connect(btnAt, &QPushButton::clicked, this, &MainWindow::demonstrateAt);
    connect(btnFrontBack, &QPushButton::clicked, this, &MainWindow::demonstrateFrontBack);
}

void MainWindow::updateTables() {
    table1_->clear();
    table1_->setRowCount(data_.first.size());
    table1_->setColumnCount(1);
    table1_->setHorizontalHeaderLabels({"int"});
    for(size_t i = 0; i < data_.first.size(); ++i)
        table1_->setItem(i, 0, new QTableWidgetItem(QString::number(data_.first[i])));

    table2_->clear();
    table2_->setRowCount(data_.second.size());
    table2_->setColumnCount(2);
    table2_->setHorizontalHeaderLabels({"int", "double"});
    for(size_t i = 0; i < data_.second.size(); ++i) {
        table2_->setItem(i, 0, new QTableWidgetItem(QString::number(data_.second[i].first)));
        table2_->setItem(i, 1, new QTableWidgetItem(QString::number(data_.second[i].second, 'f', 2)));
    }
}

void MainWindow::demonstrateInsert() {
    int target = vectorSelector->currentIndex();
    size_t currentSize = (target == 0) ? data_.first.size() : data_.second.size();
    
    bool ok;
    int idx = QInputDialog::getInt(this, "Insert", "Введите индекс для вставки:", 0, 0, currentSize, 1, &ok);
    if (!ok) return;

    if (target == 0) {
        int val = QInputDialog::getInt(this, "Insert (Vector 1)", "Введите число (int):", 0, -1000, 1000, 1, &ok);
        if (ok) {
            auto it = data_.first.begin();
            for(int i = 0; i < idx; ++i) ++it;
            data_.first.insert(it, val);
        }
    } else {
        int v1 = QInputDialog::getInt(this, "Insert (Vector 2)", "Введите целое (int):", 0, -1000, 1000, 1, &ok);
        if (!ok) return;
        double v2 = QInputDialog::getDouble(this, "Insert (Vector 2)", "Введите дробное (double):", 0.0, -1000, 1000, 2, &ok);
        if (ok) {
            auto it = data_.second.begin();
            for(int i = 0; i < idx; ++i) ++it;
            data_.second.insert(it, Pair<int, double>(v1, v2));
        }
    }
    updateTables();
}

#include <stdexcept>

void MainWindow::demonstrateSwap() {
    int target = vectorSelector->currentIndex();
    bool ok;
    
    int count = QInputDialog::getInt(this, "Swap", 
        "Введите количество элементов для нового вектора:", 1, 1, 100, 1, &ok);
    
    if (!ok) return;

    try {
        if (target == 0) {
            Vector<int> temp;
            for (int i = 0; i < count; ++i) {
                QString valStr = QInputDialog::getText(this, "Ввод элементов", 
                    QString("Элемент [%1] (int):").arg(i), QLineEdit::Normal, "", &ok);
                
                if (!ok) return;

                bool canConvert;
                int val = valStr.toInt(&canConvert);
                
                if (!canConvert) {
                    throw std::invalid_argument("Значение '" + valStr.toStdString() + "' не является целым числом!");
                }
                temp.push_back(val);
            }
            data_.first.swap(temp);
            QMessageBox::information(this, "Успех", "Обмен для Матрицы 1 выполнен.");
            
        } else {
            Vector<Pair<int, double>> temp;
            for (int i = 0; i < count; ++i) {
                QString intStr = QInputDialog::getText(this, "Ввод Pair", 
                    QString("Пара [%1] - Введите INT:").arg(i), QLineEdit::Normal, "", &ok);
                if (!ok) return;

                bool canConvertInt;
                int v1 = intStr.toInt(&canConvertInt);
                if (!canConvertInt) {
                    throw std::invalid_argument("Значение '" + intStr.toStdString() + "' не является целым числом (int)!");
                }

                QString doubleStr = QInputDialog::getText(this, "Ввод Pair", 
                    QString("Пара [%1] - Введите DOUBLE:").arg(i), QLineEdit::Normal, "", &ok);
                if (!ok) return;

                bool canConvertDouble;
                double v2 = doubleStr.toDouble(&canConvertDouble);
                if (!canConvertDouble) {
                    throw std::invalid_argument("Значение '" + doubleStr.toStdString() + "' не является числом (double)!");
                }

                temp.push_back(Pair<int, double>(v1, v2));
            }
            data_.second.swap(temp);
            QMessageBox::information(this, "Успех", "Обмен для Матрицы 2 выполнен.");
        }
        
        updateTables();

    } catch (const std::invalid_argument& e) {
        QMessageBox::critical(this, "Ошибка типа данных", 
            QString("Ошибка: %1").arg(e.what()));
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", e.what());
    } catch (...) {
        QMessageBox::critical(this, "Ошибка", "Произошла непредвиденная ошибка.");
    }
}

void MainWindow::demonstratePushBack() {
    bool ok;
    if (vectorSelector->currentIndex() == 0) {
        int val = QInputDialog::getInt(this, "Push", "Значение:", 0, -1000, 1000, 1, &ok);
        if(ok) data_.first.push_back(val);
    } else {
        int v1 = QInputDialog::getInt(this, "Push", "int:", 0, -1000, 1000, 1, &ok);
        double v2 = QInputDialog::getDouble(this, "Push", "double:", 0.0, -1000, 1000, 2, &ok);
        if(ok) data_.second.push_back(Pair<int, double>(v1, v2));
    }
    updateTables();
}

void MainWindow::demonstratePopBack() {
    if (vectorSelector->currentIndex() == 0 && !data_.first.empty()) data_.first.pop_back();
    else if (vectorSelector->currentIndex() == 1 && !data_.second.empty()) data_.second.pop_back();
    updateTables();
}

void MainWindow::demonstrateErase() {
    int target = vectorSelector->currentIndex();
    size_t size = (target == 0) ? data_.first.size() : data_.second.size();
    if (size == 0) return;
    bool ok;
    int idx = QInputDialog::getInt(this, "Erase", "Индекс:", 0, 0, size - 1, 1, &ok);
    if (ok) {
        if (target == 0) {
            auto it = data_.first.begin();
            for(int i = 0; i < idx; ++i) ++it;
            data_.first.erase(it);
        } else {
            auto it = data_.second.begin();
            for(int i = 0; i < idx; ++i) ++it;
            data_.second.erase(it);
        }
        updateTables();
    }
}

void MainWindow::demonstrateResize() {
    bool ok;
    int n = QInputDialog::getInt(this, "Resize", "Размер:", 0, 0, 100, 1, &ok);
    if (ok) {
        if (vectorSelector->currentIndex() == 0) data_.first.resize(n, 0);
        else data_.second.resize(n, Pair<int, double>(0, 0.0));
        updateTables();
    }
}

void MainWindow::demonstrateAssign() {
    bool ok;
    int n = QInputDialog::getInt(this, "Assign", "Кол-во:", 5, 1, 50, 1, &ok);
    if (ok) {
        if (vectorSelector->currentIndex() == 0) data_.first.assign(n, 1);
        else data_.second.assign(n, Pair<int, double>(1, 1.0));
        updateTables();
    }
}

void MainWindow::demonstrateAt() {
    int target = vectorSelector->currentIndex();
    size_t size = (target == 0) ? data_.first.size() : data_.second.size();
    if (size == 0) return;
    bool ok;
    int idx = QInputDialog::getInt(this, "At", "Индекс:", 0, 0, size - 1, 1, &ok);
    if (ok) {
        if (target == 0) QMessageBox::information(this, "At", QString::number(data_.first.at(idx)));
        else QMessageBox::information(this, "At", QString("(%1, %2)").arg(data_.second.at(idx).first).arg(data_.second.at(idx).second));
    }
}

void MainWindow::demonstrateFrontBack() {
    if (vectorSelector->currentIndex() == 0 && !data_.first.empty())
        QMessageBox::information(this, "Front/Back", QString("F: %1, B: %2").arg(data_.first.front()).arg(data_.first.back()));
    else if (!data_.second.empty())
        QMessageBox::information(this, "Front/Back", "Элементы в таблице 2");
}

void MainWindow::demonstrateClear() {
    if (vectorSelector->currentIndex() == 0) data_.first.clear();
    else data_.second.clear();
    updateTables();
}