#include "mainwindow.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QStatusBar>
#include <QMessageBox>
#include <QListWidget>
#include <QString>
#include <stdexcept>

MainWindow::MainWindow(QWidget *parent) 
    : QMainWindow(parent)
{
    setupUI();
    updateDisplay();
}

void MainWindow::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    
    // Заголовок
    QLabel *title = new QLabel("Задание 5");
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title);
    
    // Горизонтальный layout для основного содержимого
    QHBoxLayout *contentLayout = new QHBoxLayout();
    
    // ЛЕВАЯ ПАНЕЛЬ - ListBox и информация
    QVBoxLayout *leftPanel = new QVBoxLayout();
    
    QLabel *lblListTitle = new QLabel("Содержимое дека:");
    leftPanel->addWidget(lblListTitle);
    
    listWidget = new QListWidget();
    listWidget->setMinimumWidth(300);
    listWidget->setMinimumHeight(200);
    leftPanel->addWidget(listWidget);
    
    // Информация о состоянии
    QGroupBox *infoGroup = new QGroupBox("Информация о состоянии");
    QVBoxLayout *infoLayout = new QVBoxLayout(infoGroup);
    
    lblSize = new QLabel("Размер (size): 0");
    infoLayout->addWidget(lblSize);
    
    lblEmpty = new QLabel("Пуст (empty): ДА");
    infoLayout->addWidget(lblEmpty);
    
    leftPanel->addWidget(infoGroup);
    contentLayout->addLayout(leftPanel);
    
    // ПРАВАЯ ПАНЕЛЬ - кнопки управления
    QVBoxLayout *rightPanel = new QVBoxLayout();
    
    // Группа добавления элементов
    QGroupBox *addGroup = new QGroupBox("Добавление элементов");
    QVBoxLayout *addLayout = new QVBoxLayout(addGroup);
    
    QLabel *lblValue = new QLabel("Значение:");
    addLayout->addWidget(lblValue);
    
    spinValue = new QSpinBox();
    spinValue->setRange(-9999, 9999);
    spinValue->setValue(42);
    addLayout->addWidget(spinValue);
    
    btnPushBack = new QPushButton("push_back() - Добавить в конец");
    connect(btnPushBack, &QPushButton::clicked, this, &MainWindow::onPushBack);
    addLayout->addWidget(btnPushBack);
    
    btnPushFront = new QPushButton("push_front() - Добавить в начало");
    connect(btnPushFront, &QPushButton::clicked, this, &MainWindow::onPushFront);
    addLayout->addWidget(btnPushFront);
    
    rightPanel->addWidget(addGroup);
    
    // Группа удаления элементов
    QGroupBox *removeGroup = new QGroupBox("Удаление элементов");
    QVBoxLayout *removeLayout = new QVBoxLayout(removeGroup);
    
    btnPopBack = new QPushButton("pop_back() - Удалить с конца");
    connect(btnPopBack, &QPushButton::clicked, this, &MainWindow::onPopBack);
    removeLayout->addWidget(btnPopBack);
    
    btnPopFront = new QPushButton("pop_front() - Удалить с начала");
    connect(btnPopFront, &QPushButton::clicked, this, &MainWindow::onPopFront);
    removeLayout->addWidget(btnPopFront);
    
    rightPanel->addWidget(removeGroup);
    
    // Группа доступа по индексу
    QGroupBox *accessGroup = new QGroupBox("Доступ по индексу");
    QVBoxLayout *accessLayout = new QVBoxLayout(accessGroup);
    
    QLabel *lblIndex = new QLabel("Индекс:");
    accessLayout->addWidget(lblIndex);
    
    spinIndex = new QSpinBox();
    spinIndex->setRange(0, 0);
    accessLayout->addWidget(spinIndex);
    
    btnAt = new QPushButton("operator[] - Получить элемент");
    connect(btnAt, &QPushButton::clicked, this, &MainWindow::onAt);
    accessLayout->addWidget(btnAt);
    
    rightPanel->addWidget(accessGroup);
    
    // Группа служебных операций
    QGroupBox *serviceGroup = new QGroupBox("Служебные операции");
    QVBoxLayout *serviceLayout = new QVBoxLayout(serviceGroup);
    
    btnIteratorDemo = new QPushButton("Демонстрация итераторов");
    connect(btnIteratorDemo, &QPushButton::clicked, this, &MainWindow::onIteratorDemo);
    serviceLayout->addWidget(btnIteratorDemo);
    
    btnClear = new QPushButton("clear() - Очистить дек");
    connect(btnClear, &QPushButton::clicked, this, &MainWindow::onClear);
    serviceLayout->addWidget(btnClear);
    
    rightPanel->addWidget(serviceGroup);
    
    rightPanel->addStretch();
    
    contentLayout->addLayout(rightPanel);
    mainLayout->addLayout(contentLayout);
    
    statusBar()->showMessage("Готов к работе");
}

void MainWindow::updateDisplay() {
    listWidget->clear();
    
    if (deque.empty()) {
        listWidget->addItem("Дек пуст");
    } else {
        for (size_t i = 0; i < deque.size(); i++) {
            QString text = QString("[%1] = %2").arg(i).arg(deque[i]);
            
            if (deque.size() == 1) {
                text += " (front & back)";
            } else if (i == 0) {
                text += " ← front";
            } else if (i == deque.size() - 1) {
                text += " ← back";
            }
            
            listWidget->addItem(text);
        }
    }
    
    updateStatusBar();
}

void MainWindow::updateStatusBar() {
    lblSize->setText(QString("Размер (size): %1").arg(deque.size()));
    lblEmpty->setText(QString("Пуст (empty): %1").arg(deque.empty() ? "ДА" : "НЕТ"));
    
    if (!deque.empty()) {
        spinIndex->setRange(0, static_cast<int>(deque.size() - 1));
    } else {
        spinIndex->setRange(0, 0);
    }
}

void MainWindow::showMessage(const QString &title, const QString &message) {
    QMessageBox::information(this, title, message);
}

void MainWindow::onPushBack() {
    int value = spinValue->value();
    deque.push_back(value);
    statusBar()->showMessage(QString("push_back(%1)").arg(value));
    updateDisplay();
    spinValue->setValue(value + 1);
}

void MainWindow::onPushFront() {
    int value = spinValue->value();
    deque.push_front(value);
    statusBar()->showMessage(QString("push_front(%1)").arg(value));
    updateDisplay();
    spinValue->setValue(value + 1);
}

void MainWindow::onPopBack() {
    if (deque.empty()) {
        showMessage("Ошибка", "Дек пуст!");
        return;
    }
    
    int value = deque.back();
    deque.pop_back();
    statusBar()->showMessage(QString("pop_back() удалил %1").arg(value));
    updateDisplay();
}

void MainWindow::onPopFront() {
    if (deque.empty()) {
        showMessage("Ошибка", "Дек пуст!");
        return;
    }
    
    int value = deque.front();
    deque.pop_front();
    statusBar()->showMessage(QString("pop_front() удалил %1").arg(value));
    updateDisplay();
}

void MainWindow::onClear() {
    size_t oldSize = deque.size();
    deque.clear();
    statusBar()->showMessage(QString("clear() удалил %1 элементов").arg(oldSize));
    updateDisplay();
}

void MainWindow::onAt() {
    if (deque.empty()) {
        showMessage("Ошибка", "Дек пуст!");
        return;
    }
    
    size_t index = static_cast<size_t>(spinIndex->value());
    int value = deque[index];
    
    showMessage("Доступ по индексу", 
                QString("Элемент [%1] = %2").arg(index).arg(value));
    
    listWidget->setCurrentRow(static_cast<int>(index));
}

void MainWindow::onIteratorDemo() {
    if (deque.empty()) {
        showMessage("Демонстрация итераторов", "Дек пуст. Добавьте элементы.");
        return;
    }
    
    QString result = "=== Демонстрация итераторов ===\n\n";
    
    // Прямой обход
    result += "1. Прямой обход:\n";
    size_t count = 0;
    for (auto it = deque.begin(); it != deque.end(); ++it) {
        result += QString("  [%1] = %2\n").arg(count).arg(*it);
        count++;
    }
    
    // Обратный обход
    result += "\n2. Обратный обход:\n";
    auto it = deque.end();
    count = deque.size();
    while (it != deque.begin()) {
        --it;
        --count;
        result += QString("  [%1] = %2\n").arg(count).arg(*it);
    }
    
    // Random Access
    result += "\n3. Random Access:\n";
    if (deque.size() >= 3) {
        auto it1 = deque.begin();
        auto it2 = it1 + 2;
        result += QString("  begin + 2 = %1\n").arg(*it2);
        
        auto it3 = it2 - 1;
        result += QString("  (begin+2) - 1 = %1\n").arg(*it3);
        
        auto itMid = deque.begin() + (deque.size() / 2);
        result += QString("  Средний [%1] = %2\n").arg(deque.size() / 2).arg(*itMid);
        
        ptrdiff_t distance = deque.end() - deque.begin();
        result += QString("  end - begin = %1\n").arg(distance);
    }
    
    // Демонстрация без инвалидации
    result += "\n4. Итераторы при resize:\n";
    if (deque.size() >= 2) {
        auto savedIterator = deque.begin() + 1;
        int savedValue = *savedIterator;
        
        result += QString("  Сохранён итератор на [1] = %1\n").arg(savedValue);
        
        for (int i = 0; i < 20; i++) {
            deque.push_back(999 + i);
        }
        
        int newValue = *savedIterator;
        result += QString("  После resize итератор = %1\n").arg(newValue);
        result += QString("  Значение сохранилось: %1\n").arg(savedValue == newValue ? "ДА" : "НЕТ");
        
        for (int i = 0; i < 20; i++) {
            deque.pop_back();
        }
    }
    
    result += "\n✓ Итераторы не инвалидируются при resize";
    
    showMessage("Демонстрация итераторов", result);
    updateDisplay();
}