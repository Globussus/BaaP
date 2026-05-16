#include "mainwindow.h"
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , arrayHeap(std::make_unique<ArrayHeap<int>>())
    , listHeap(std::make_unique<ListHeap<int>>())
    , usingArrayHeap(true) {
    
    setupUI();
    setWindowTitle("Бинарная куча");
    setMinimumSize(800, 600);
    
    updateDisplay();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    
    // ==================== Выбор типа кучи ====================
    typeGroupBox = new QGroupBox("Тип кучи");
    typeLayout = new QHBoxLayout(typeGroupBox);
    
    typeLabel = new QLabel("Тип реализации:");
    heapTypeComboBox = new QComboBox();
    heapTypeComboBox->addItem("На основе массива (Array-based)");
    heapTypeComboBox->addItem("На основе списка (List-based)");
    
    typeLayout->addWidget(typeLabel);
    typeLayout->addWidget(heapTypeComboBox);
    typeLayout->addStretch();
    
    mainLayout->addWidget(typeGroupBox);
    
    // ==================== Ввод и операции ====================
    inputGroupBox = new QGroupBox("Операции с кучей");
    inputLayout = new QHBoxLayout(inputGroupBox);
    
    valueLabel = new QLabel("Значение:");
    valueLineEdit = new QLineEdit();
    valueLineEdit->setPlaceholderText("Целое число");
    valueLineEdit->setFixedWidth(150);
    valueLineEdit->setValidator(new QIntValidator(this));
    
    pushButton = new QPushButton("Добавить (push)");
    popButton = new QPushButton("Извлечь (pop)");
    topButton = new QPushButton("Верхний элемент (top)");
    clearButton = new QPushButton("Очистить");
    randomButton = new QPushButton("Случайная куча");
    
    inputLayout->addWidget(valueLabel);
    inputLayout->addWidget(valueLineEdit);
    inputLayout->addWidget(pushButton);
    inputLayout->addWidget(popButton);
    inputLayout->addWidget(topButton);
    inputLayout->addWidget(clearButton);
    inputLayout->addWidget(randomButton);
    inputLayout->addStretch();
    
    mainLayout->addWidget(inputGroupBox);
    
    // ==================== Информационная панель ====================
    infoGroupBox = new QGroupBox("Информация");
    infoLayout = new QHBoxLayout(infoGroupBox);
    
    sizeLabel = new QLabel("Размер: 0");
    topLabel = new QLabel("Максимум: -");
    
    infoLayout->addWidget(sizeLabel);
    infoLayout->addWidget(topLabel);
    infoLayout->addStretch();
    
    mainLayout->addWidget(infoGroupBox);
    
    // ==================== Отображение дерева ====================
    treeWidget = new QTreeWidget();
    treeWidget->setHeaderLabels(QStringList() << "Ключ (значение)" << "Позиция в куче");
    treeWidget->setColumnWidth(0, 200);
    treeWidget->header()->setStretchLastSection(true);
    treeWidget->setIndentation(30);
    
    mainLayout->addWidget(treeWidget);
    
    // Подключение сигналов
    connect(heapTypeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &MainWindow::onHeapTypeChanged);
    connect(pushButton, &QPushButton::clicked, this, &MainWindow::onPushClicked);
    connect(popButton, &QPushButton::clicked, this, &MainWindow::onPopClicked);
    connect(topButton, &QPushButton::clicked, this, &MainWindow::onTopClicked);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::onClearClicked);
    connect(randomButton, &QPushButton::clicked, this, &MainWindow::onRandomClicked);
}

void MainWindow::onHeapTypeChanged(int index) {
    switchHeapType(index == 0);
}

void MainWindow::switchHeapType(bool useArray) {
    usingArrayHeap = useArray;
    updateDisplay();
}

void MainWindow::onPushClicked() {
    int value = getValueFromInput();
    if (value == -1) return;
    
    try {
        if (usingArrayHeap) {
            arrayHeap->push(value);
        } else {
            listHeap->push(value);
        }
        updateDisplay();
        valueLineEdit->clear();
        showMessage("Успех", QString("Добавлено значение: %1").arg(value));
    } catch (const std::exception& e) {
        showMessage("Ошибка", e.what(), true);
    }
}

void MainWindow::onPopClicked() {
    try {
        int value;
        if (usingArrayHeap) {
            if (arrayHeap->empty()) {
                showMessage("Ошибка", "Куча пуста!", true);
                return;
            }
            value = arrayHeap->pop();
        } else {
            if (listHeap->empty()) {
                showMessage("Ошибка", "Куча пуста!", true);
                return;
            }
            value = listHeap->pop();
        }
        updateDisplay();
        showMessage("Успех", QString("Извлечено значение: %1").arg(value));
    } catch (const std::exception& e) {
        showMessage("Ошибка", e.what(), true);
    }
}

void MainWindow::onTopClicked() {
    try {
        int value;
        if (usingArrayHeap) {
            if (arrayHeap->empty()) {
                showMessage("Ошибка", "Куча пуста!", true);
                return;
            }
            value = arrayHeap->top();
        } else {
            if (listHeap->empty()) {
                showMessage("Ошибка", "Куча пуста!", true);
                return;
            }
            value = listHeap->top();
        }
        showMessage("Верхний элемент", QString("Максимальное значение: %1").arg(value));
    } catch (const std::exception& e) {
        showMessage("Ошибка", e.what(), true);
    }
}

void MainWindow::onClearClicked() {
    if (usingArrayHeap) {
        if (arrayHeap->empty()) {
            showMessage("Ошибка", "Куча уже пуста!", true);
            return;
        }
        arrayHeap->clear();
    } else {
        if (listHeap->empty()) {
            showMessage("Ошибка", "Куча уже пуста!", true);
            return;
        }
        listHeap->clear();
    }
    updateDisplay();
    showMessage("Успех", "Куча очищена");
}

void MainWindow::onRandomClicked() {
    QRandomGenerator* generator = QRandomGenerator::global();
    int count = generator->bounded(10, 21); // 10-20 элементов
    
    try {
        if (usingArrayHeap) {
            arrayHeap->clear();
            for (int i = 0; i < count; i++) {
                arrayHeap->push(generator->bounded(1, 101));
            }
        } else {
            listHeap->clear();
            for (int i = 0; i < count; i++) {
                listHeap->push(generator->bounded(1, 101));
            }
        }
        updateDisplay();
        showMessage("Успех", QString("Сгенерировано %1 случайных элементов").arg(count));
    } catch (const std::exception& e) {
        showMessage("Ошибка", e.what(), true);
    }
}

void MainWindow::updateDisplay() {
    updateTreeDisplay();
    
    size_t heapSize;
    bool isEmpty;
    
    if (usingArrayHeap) {
        heapSize = arrayHeap->size();
        isEmpty = arrayHeap->empty();
        sizeLabel->setText(QString("Размер: %1").arg(heapSize));
        if (!isEmpty) {
            topLabel->setText(QString("Максимум: %1").arg(arrayHeap->top()));
        } else {
            topLabel->setText("Максимум: -");
        }
    } else {
        heapSize = listHeap->size();
        isEmpty = listHeap->empty();
        sizeLabel->setText(QString("Размер: %1").arg(heapSize));
        if (!isEmpty) {
            topLabel->setText(QString("Максимум: %1").arg(listHeap->top()));
        } else {
            topLabel->setText("Максимум: -");
        }
    }
    
    // Обновление статусной строки
    QString heapType = usingArrayHeap ? "Array-based" : "List-based";
    statusBar()->showMessage(QString("Тип: %1 | Состояние: %2 | Элементов: %3")
                              .arg(heapType)
                              .arg(isEmpty ? "пуста" : "не пуста")
                              .arg(heapSize));
}

void MainWindow::updateTreeDisplay() {
    treeWidget->clear();
    
    bool isEmpty;
    std::vector<int> elements;
    
    if (usingArrayHeap) {
        isEmpty = arrayHeap->empty();
        if (!isEmpty) {
            elements = arrayHeap->getAllElements();
        }
    } else {
        isEmpty = listHeap->empty();
        if (!isEmpty) {
            elements = listHeap->getAllElements();
        }
    }
    
    if (isEmpty) {
        treeWidget->addTopLevelItem(new QTreeWidgetItem(QStringList() << "Куча пуста" << ""));
        return;
    }
    
    // Создание корневого элемента
    QTreeWidgetItem* rootItem = new QTreeWidgetItem();
    rootItem->setText(0, QString::number(elements[0]));
    rootItem->setText(1, "корень (индекс 0)");
    
    addNodeToTreeWidget(0, rootItem);
    treeWidget->addTopLevelItem(rootItem);
    treeWidget->expandAll();
}

void MainWindow::addNodeToTreeWidget(int index, QTreeWidgetItem* parentItem) {
    std::vector<int> elements;
    
    if (usingArrayHeap) {
        elements = arrayHeap->getAllElements();
    } else {
        elements = listHeap->getAllElements();
    }
    
    int leftChildIndex = 2 * index + 1;
    int rightChildIndex = 2 * index + 2;
    
    // Левый потомок
    if (leftChildIndex < static_cast<int>(elements.size())) {
        QTreeWidgetItem* leftItem = new QTreeWidgetItem();
        leftItem->setText(0, QString::number(elements[leftChildIndex]));
        leftItem->setText(1, QString("левый потомок (индекс %1)").arg(leftChildIndex));
        parentItem->addChild(leftItem);
        addNodeToTreeWidget(leftChildIndex, leftItem);
    }
    
    // Правый потомок
    if (rightChildIndex < static_cast<int>(elements.size())) {
        QTreeWidgetItem* rightItem = new QTreeWidgetItem();
        rightItem->setText(0, QString::number(elements[rightChildIndex]));
        rightItem->setText(1, QString("правый потомок (индекс %1)").arg(rightChildIndex));
        parentItem->addChild(rightItem);
        addNodeToTreeWidget(rightChildIndex, rightItem);
    }
}

void MainWindow::showMessage(const QString& title, const QString& message, bool isError) {
    if (isError) {
        QMessageBox::critical(this, title, message);
    } else {
        QMessageBox::information(this, title, message);
    }
}

int MainWindow::getValueFromInput() {
    QString text = valueLineEdit->text().trimmed();
    if (text.isEmpty()) {
        showMessage("Ошибка", "Введите значение", true);
        return -1;
    }
    
    bool ok;
    int value = text.toInt(&ok);
    if (!ok) {
        showMessage("Ошибка", "Неверное целое число", true);
        return -1;
    }
    
    return value;
}