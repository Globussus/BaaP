#include "mainwindow.h"
#include <random>
#include <ctime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    setWindowTitle("Задание 1");
    resize(800, 600);
    srand(time(nullptr));
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    
    // Группа управления
    QGroupBox* controlGroup = new QGroupBox("Управление очередью", this);
    QVBoxLayout* controlLayout = new QVBoxLayout(controlGroup);
    
    // Строка для добавления элементов
    QHBoxLayout* addLayout = new QHBoxLayout();
    QLabel* valueLabel = new QLabel("Значение:", this);
    valueSpinBox = new QSpinBox(this);
    valueSpinBox->setRange(-1000, 1000);
    pushBackBtn = new QPushButton("Push Back", this);
    pushFrontBtn = new QPushButton("Push Front", this);
    
    addLayout->addWidget(valueLabel);
    addLayout->addWidget(valueSpinBox);
    addLayout->addWidget(pushBackBtn);
    addLayout->addWidget(pushFrontBtn);
    
    // Строка для удаления элементов
    QHBoxLayout* removeLayout = new QHBoxLayout();
    popBackBtn = new QPushButton("Pop Back", this);
    popFrontBtn = new QPushButton("Pop Front", this);
    clearBtn = new QPushButton("Очистить очередь", this);
    clearBtn->setStyleSheet("QPushButton { background-color: #f44336; color: white; font-weight: bold; padding: 5px; }");
    
    removeLayout->addWidget(popBackBtn);
    removeLayout->addWidget(popFrontBtn);
    removeLayout->addWidget(clearBtn);
    
    // Строка для генерации случайных элементов
    QHBoxLayout* generateLayout = new QHBoxLayout();
    QLabel* countLabel = new QLabel("Количество:", this);
    randomCountSpinBox = new QSpinBox(this);
    randomCountSpinBox->setRange(1, 100);
    randomCountSpinBox->setValue(10);
    generateBtn = new QPushButton("Сгенерировать случайные числа", this);
    
    generateLayout->addWidget(countLabel);
    generateLayout->addWidget(randomCountSpinBox);
    generateLayout->addWidget(generateBtn);
    
    // Кнопка очистки ВСЕХ очередей
    QHBoxLayout* clearAllLayout = new QHBoxLayout();
    QPushButton* clearAllBtn = new QPushButton("Очистить ВСЕ очереди", this);
    clearAllBtn->setStyleSheet("QPushButton { background-color: #ff6f00; color: white; font-weight: bold; padding: 8px; }");
    clearAllLayout->addWidget(clearAllBtn);
    
    // Строка для решения задачи
    QHBoxLayout* solveLayout = new QHBoxLayout();
    solveBtn = new QPushButton("Решить задачу (Вариант 7)", this);
    solveBtn->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; font-weight: bold; padding: 8px; }");
    solveLayout->addWidget(solveBtn);
    
    controlLayout->addLayout(addLayout);
    controlLayout->addLayout(removeLayout);
    controlLayout->addLayout(generateLayout);
    controlLayout->addLayout(clearAllLayout);
    controlLayout->addLayout(solveLayout);
    
    // Группа отображения
    QHBoxLayout* displayLayout = new QHBoxLayout();
    
    // Исходная очередь
    QVBoxLayout* dequeLayout = new QVBoxLayout();
    QLabel* dequeLabel = new QLabel("Исходная очередь (Дек):", this);
    dequeList = new QListWidget(this);
    dequeLayout->addWidget(dequeLabel);
    dequeLayout->addWidget(dequeList);
    
    // Первое кольцо
    QVBoxLayout* firstRingLayout = new QVBoxLayout();
    QLabel* firstRingLabel = new QLabel("Первое кольцо (между min и max):", this);
    firstRingList = new QListWidget(this);
    firstRingLayout->addWidget(firstRingLabel);
    firstRingLayout->addWidget(firstRingList);
    
    // Второе кольцо
    QVBoxLayout* secondRingLayout = new QVBoxLayout();
    QLabel* secondRingLabel = new QLabel("Второе кольцо (остальные):", this);
    secondRingList = new QListWidget(this);
    secondRingLayout->addWidget(secondRingLabel);
    secondRingLayout->addWidget(secondRingList);
    
    displayLayout->addLayout(dequeLayout);
    displayLayout->addLayout(firstRingLayout);
    displayLayout->addLayout(secondRingLayout);
    
    mainLayout->addWidget(controlGroup);
    mainLayout->addLayout(displayLayout);
    
    // Подключение сигналов
    connect(pushBackBtn, &QPushButton::clicked, this, &MainWindow::onPushBack);
    connect(pushFrontBtn, &QPushButton::clicked, this, &MainWindow::onPushFront);
    connect(popBackBtn, &QPushButton::clicked, this, &MainWindow::onPopBack);
    connect(popFrontBtn, &QPushButton::clicked, this, &MainWindow::onPopFront);
    connect(generateBtn, &QPushButton::clicked, this, &MainWindow::onGenerateRandom);
    connect(clearBtn, &QPushButton::clicked, this, &MainWindow::onClearDeque);
    connect(clearAllBtn, &QPushButton::clicked, this, &MainWindow::onClearAll);
    connect(solveBtn, &QPushButton::clicked, this, &MainWindow::onSolve);
    
    updateDisplay();
}

void MainWindow::onPushBack()
{
    deque.pushBack(valueSpinBox->value());
    updateDisplay();
}

void MainWindow::onPushFront()
{
    deque.pushFront(valueSpinBox->value());
    updateDisplay();
}

void MainWindow::onPopBack()
{
    try {
        int value = deque.popBack();
        updateDisplay();
        QMessageBox::information(this, "Pop Back", QString("Удален элемент: %1").arg(value));
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void MainWindow::onPopFront()
{
    try {
        int value = deque.popFront();
        updateDisplay();
        QMessageBox::information(this, "Pop Front", QString("Удален элемент: %1").arg(value));
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void MainWindow::onGenerateRandom()
{
    int count = randomCountSpinBox->value();
    for (int i = 0; i < count; i++) {
        deque.pushBack(rand() % 201 - 100);
    }
    updateDisplay();
}

void MainWindow::onClearDeque()
{
    deque.clear();
    updateDisplay();
    QMessageBox::information(this, "Очистка", "Исходная очередь очищена");
}

void MainWindow::onClearAll()
{
    firstRing.clear();
    secondRing.clear();
    deque.clear();
    updateDisplay();
    QMessageBox::information(this, "Очистка", "Все очереди очищены");
}

void MainWindow::onSolve()
{
    if (deque.isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", 
                           "Очередь пуста. Добавьте элементы перед решением задачи.");
        return;
    }
    
    firstRing.clear();
    secondRing.clear();
    
    deque.splitByMinMax(firstRing, secondRing);
    updateDisplay();
    
    QMessageBox::information(this, "Решение", 
                           "Задача решена! Элементы распределены по кольцам.\n"
                           "Первое кольцо - элементы между min и max.\n"
                           "Второе кольцо - остальные элементы.");
}

void MainWindow::updateDisplay()
{
    displayDeque(dequeList, deque, "Очередь пуста");
    displayDeque(firstRingList, firstRing, "Кольцо пусто");
    displayDeque(secondRingList, secondRing, "Кольцо пусто");
}

void MainWindow::displayDeque(QListWidget* list, const Deque& d, const QString& emptyMsg)
{
    list->clear();
    if (d.isEmpty()) {
        list->addItem(emptyMsg);
    } else {
        // Прямой обход по указателям, не изменяя дек!
        ListElement* current = d.head;
        while (current != nullptr) {
            list->addItem(QString::number(current->value));
            current = current->next;
        }
    }
}