#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {
    setupUi();
}

void MainWindow::setupUi() {
    setWindowTitle("Хеш-таблица на массиве стеков");
    setMinimumSize(600, 500);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Группа управления
    QGroupBox* controlGroup = new QGroupBox("Управление", this);
    QVBoxLayout* controlLayout = new QVBoxLayout(controlGroup);

    // Строка для ввода ключа
    QHBoxLayout* keyInputLayout = new QHBoxLayout();
    QLabel* keyLabel = new QLabel("Ключ:", this);
    keyInput = new QLineEdit(this);
    keyInput->setPlaceholderText("Введите ключ (целое число)");
    keyInputLayout->addWidget(keyLabel);
    keyInputLayout->addWidget(keyInput);
    controlLayout->addLayout(keyInputLayout);

    // Строка для ввода значения
    QHBoxLayout* valueInputLayout = new QHBoxLayout();
    QLabel* valueLabel = new QLabel("Значение:", this);
    valueInput = new QLineEdit(this);
    valueInput->setPlaceholderText("Введите значение");
    valueInputLayout->addWidget(valueLabel);
    valueInputLayout->addWidget(valueInput);
    controlLayout->addLayout(valueInputLayout);

    // Кнопки операций
    QHBoxLayout* buttonLayout1 = new QHBoxLayout();
    addButton = new QPushButton("Добавить", this);
    removeButton = new QPushButton("Удалить", this);
    findButton = new QPushButton("Найти", this);
    buttonLayout1->addWidget(addButton);
    buttonLayout1->addWidget(removeButton);
    buttonLayout1->addWidget(findButton);
    controlLayout->addLayout(buttonLayout1);

    // Кнопки специальных операций
    QHBoxLayout* buttonLayout2 = new QHBoxLayout();
    fillRandomButton = new QPushButton("Заполнить случайными (10)", this);
    findMaxButton = new QPushButton("Найти максимальный ключ", this);
    printButton = new QPushButton("Показать таблицу", this);
    buttonLayout2->addWidget(fillRandomButton);
    buttonLayout2->addWidget(findMaxButton);
    buttonLayout2->addWidget(printButton);
    controlLayout->addLayout(buttonLayout2);

    controlGroup->setLayout(controlLayout);
    mainLayout->addWidget(controlGroup);

    // Область вывода
    QGroupBox* outputGroup = new QGroupBox("Вывод (Memo)", this);
    QVBoxLayout* outputLayout = new QVBoxLayout(outputGroup);
    outputText = new QTextEdit(this);
    outputText->setReadOnly(true);
    outputText->setFont(QFont("Courier New", 10));
    outputLayout->addWidget(outputText);
    outputGroup->setLayout(outputLayout);
    mainLayout->addWidget(outputGroup);

    // Подключаем сигналы
    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddClicked);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveClicked);
    connect(findButton, &QPushButton::clicked, this, &MainWindow::onFindClicked);
    connect(fillRandomButton, &QPushButton::clicked, this, &MainWindow::onFillRandomClicked);
    connect(findMaxButton, &QPushButton::clicked, this, &MainWindow::onFindMaxClicked);
    connect(printButton, &QPushButton::clicked, this, &MainWindow::onPrintClicked);
}

void MainWindow::printToOutput(const std::string& text) {
    outputText->append(QString::fromStdString(text));
}

void MainWindow::onAddClicked() {
    QString keyText = keyInput->text().trimmed();
    QString valueText = valueInput->text().trimmed();
    
    if (keyText.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите ключ");
        return;
    }
    if (valueText.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите значение");
        return;
    }
    
    std::string key = keyText.toStdString();
    std::string value = valueText.toStdString();
    
    if (hashTable.add(key, value)) {
        printToOutput("Добавлена пара: ключ=" + key + ", значение=" + value);
        keyInput->clear();
        valueInput->clear();
    } else {
        printToOutput("Ключ " + key + " уже существует в таблице");
    }
}

void MainWindow::onRemoveClicked() {
    QString keyText = keyInput->text().trimmed();
    
    if (keyText.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите ключ для удаления");
        return;
    }
    
    std::string key = keyText.toStdString();
    if (hashTable.remove(key)) {
        printToOutput("Удален ключ: " + key);
        keyInput->clear();
    } else {
        printToOutput("Ключ " + key + " не найден в таблице");
    }
}

void MainWindow::onFindClicked() {
    QString keyText = keyInput->text().trimmed();
    
    if (keyText.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите ключ для поиска");
        return;
    }
    
    std::string key = keyText.toStdString();
    auto value = hashTable.find(key);
    if (value != nullptr) {
        printToOutput("Найдено: ключ=" + key + ", значение=" + *value);
    } else {
        printToOutput("Ключ " + key + " не найден в таблице");
    }
}

void MainWindow::onFillRandomClicked() {
    for (int i = 0; i < 10; ++i) {
        int randomKey = QRandomGenerator::global()->bounded(1, 100);
        std::string key = std::to_string(randomKey);
        std::string value = "Value_" + std::to_string(randomKey);
        hashTable.add(key, value);
    }
    printToOutput("=== Таблица заполнена 10 случайными парами ключ-значение ===");
    onPrintClicked();
}

void MainWindow::onFindMaxClicked() {
    try {
        std::string maxKey = hashTable.findMaxKey();
        printToOutput("=== Максимальный ключ в таблице: " + maxKey + " ===");
    } catch (const std::runtime_error& e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void MainWindow::onPrintClicked() {
    std::string tableStr = hashTable.print();
    outputText->clear();
    printToOutput("=== Текущее состояние хеш-таблицы ===");
    printToOutput("Размер таблицы: " + std::to_string(hashTable.getBufferSize()) +
                  ", элементов: " + std::to_string(hashTable.getElementCount()));
    printToOutput(tableStr);
}