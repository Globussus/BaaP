#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <sstream>
#include <random>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , currentStructure(StructureType::BST_MAP) {
    setupUi();
    initializeSampleData();
}

void MainWindow::setupUi() {
    setWindowTitle("Лабораторная работа - Структуры данных");
    setMinimumSize(1000, 700);

    auto centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    auto mainLayout = new QVBoxLayout(centralWidget);

    // Выбор структуры
    auto topLayout = new QHBoxLayout();
    topLayout->addWidget(new QLabel("Структура:"));
    
    structureCombo = new QComboBox();
    structureCombo->addItem("BST Map (словарь)");
    structureCombo->addItem("BST Set (множество)");
    structureCombo->addItem("Unordered Map (хеш-таблица)");
    topLayout->addWidget(structureCombo);
    topLayout->addStretch();
    
    sizeLabel = new QLabel("Размер: 0");
    topLayout->addWidget(sizeLabel);
    mainLayout->addLayout(topLayout);

    // Панель ввода
    auto inputGroup = new QGroupBox("Операции");
    auto inputLayout = new QVBoxLayout(inputGroup);

    auto fieldsLayout = new QHBoxLayout();
    fieldsLayout->addWidget(new QLabel("Ключ:"));
    keyInput = new QLineEdit();
    keyInput->setPlaceholderText("Введите ключ");
    keyInput->setMinimumWidth(150);
    fieldsLayout->addWidget(keyInput);
    
    fieldsLayout->addWidget(new QLabel("Значение:"));
    valueInput = new QLineEdit();
    valueInput->setPlaceholderText("Введите значение");
    valueInput->setMinimumWidth(150);
    fieldsLayout->addWidget(valueInput);
    
    fieldsLayout->addWidget(new QLabel("Размер таблицы:"));
    hashSizeSpin = new QSpinBox();
    hashSizeSpin->setRange(1, 1000);
    hashSizeSpin->setValue(8);
    fieldsLayout->addWidget(hashSizeSpin);
    
    fieldsLayout->addStretch();
    inputLayout->addLayout(fieldsLayout);

    auto buttonsLayout = new QHBoxLayout();
    insertBtn = new QPushButton("Добавить");
    eraseBtn = new QPushButton("Удалить");
    findByKeyBtn = new QPushButton("Найти по ключу");
    clearBtn = new QPushButton("Очистить");
    randomBtn = new QPushButton("Случайные 5");
    rehashBtn = new QPushButton("Рехешировать");
    showIterBtn = new QPushButton("Обход");
    
    buttonsLayout->addWidget(insertBtn);
    buttonsLayout->addWidget(eraseBtn);
    buttonsLayout->addWidget(findByKeyBtn);
    buttonsLayout->addWidget(clearBtn);
    buttonsLayout->addWidget(randomBtn);
    buttonsLayout->addWidget(rehashBtn);
    buttonsLayout->addWidget(showIterBtn);
    buttonsLayout->addStretch();
    inputLayout->addLayout(buttonsLayout);
    
    mainLayout->addWidget(inputGroup);

    // Дерево
    treeWidget = new QTreeWidget();
    treeWidget->setAnimated(true);
    treeWidget->setIndentation(30);
    treeWidget->header()->setStretchLastSection(true);
    treeWidget->setColumnWidth(0, 300);
    treeWidget->setColumnWidth(1, 600);
    treeWidget->setColumnWidth(2, 300);
    mainLayout->addWidget(treeWidget);

    // Хеш-таблица
    hashTableWidget = new QTableWidget();
    hashTableWidget->setColumnCount(3);
    hashTableWidget->setHorizontalHeaderLabels({"Индекс", "Ключ", "Значение"});
    hashTableWidget->horizontalHeader()->setStretchLastSection(true);
    hashTableWidget->setColumnWidth(0, 80);
    hashTableWidget->setColumnWidth(1, 100);
    hashTableWidget->setVisible(false);
    hashTableWidget->setAlternatingRowColors(true);
    mainLayout->addWidget(hashTableWidget);

    // Сигналы
    connect(structureCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onStructureChanged);
    connect(insertBtn, &QPushButton::clicked, this, &MainWindow::onInsert);
    connect(eraseBtn, &QPushButton::clicked, this, &MainWindow::onErase);
    connect(findByKeyBtn, &QPushButton::clicked, this, &MainWindow::onFindByKey);
    connect(clearBtn, &QPushButton::clicked, this, &MainWindow::onClear);
    connect(randomBtn, &QPushButton::clicked, this, &MainWindow::onRandomInsert);
    connect(rehashBtn, &QPushButton::clicked, this, &MainWindow::onRehash);
    connect(showIterBtn, &QPushButton::clicked, this, &MainWindow::onShowIter);
}

void MainWindow::initializeSampleData() {
    bstMap[50] = "Пятьдесят";
    bstMap[30] = "Тридцать";
    bstMap[70] = "Семьдесят";
    bstMap[20] = "Двадцать";
    bstMap[40] = "Сорок";

    bstSet.insert(50);
    bstSet.insert(30);
    bstSet.insert(70);
    bstSet.insert(20);
    bstSet.insert(40);

    unorderedMap[50] = "Пятьдесят";
    unorderedMap[30] = "Тридцать";
    unorderedMap[70] = "Семьдесят";
    unorderedMap[20] = "Двадцать";
    unorderedMap[40] = "Сорок";

    refreshDisplay();
}

void MainWindow::refreshDisplay() {
    updateTreeView();
    updateHashTableView();
    updateStatus();
}

void MainWindow::updateTreeView() {
    treeWidget->clear();
    
    bool isHash = (currentStructure == StructureType::UNORDERED_MAP);
    treeWidget->setVisible(!isHash);
    hashTableWidget->setVisible(isHash);
    rehashBtn->setVisible(isHash);
    hashSizeSpin->setVisible(isHash);
    valueInput->setVisible(currentStructure != StructureType::BST_SET);
    showIterBtn->setVisible(!isHash);
    
    if (currentStructure == StructureType::BST_SET) {
        treeWidget->setHeaderLabels({"Ключ"});
        treeWidget->setColumnCount(1);
        treeWidget->setColumnWidth(0, 300);
    } else if (currentStructure == StructureType::BST_MAP) {
        treeWidget->setHeaderLabels({"Ключ", "Значение"});
        treeWidget->setColumnCount(2);
        treeWidget->setColumnWidth(0, 300);
        treeWidget->setColumnWidth(1, 600);
    }
    
    if (currentStructure == StructureType::BST_MAP && !bstMap.empty()) {
        addBstNodesToWidget(nullptr, bstMap.getRoot());
    } else if (currentStructure == StructureType::BST_SET && !bstSet.empty()) {
        addBstNodesToWidget(nullptr, bstSet.getRoot());
    }
    
    treeWidget->expandAll();
}

template<typename NodeType>
void MainWindow::addBstNodesToWidget(QTreeWidgetItem* parent, std::shared_ptr<NodeType> node) {
    if (!node) return;

    QTreeWidgetItem* item = parent ? new QTreeWidgetItem(parent) : new QTreeWidgetItem(treeWidget);
    item->setText(0, QString::number(node->data.first));
    
    // Для Map добавляем значение во вторую колонку
    if constexpr (!std::is_same_v<decltype(node->data.second), const char&> &&
                  !std::is_same_v<decltype(node->data.second), char&> &&
                  !std::is_same_v<decltype(node->data.second), char>) {
        item->setText(1, node->data.second);
    }

    if (node->left) addBstNodesToWidget(item, node->left);
    if (node->right) addBstNodesToWidget(item, node->right);
}

void MainWindow::updateHashTableView() {
    hashTableWidget->setRowCount(0);
    
    if (currentStructure == StructureType::UNORDERED_MAP) {
        const auto& buckets = unorderedMap.getBuckets();
        int row = 0;
        
        for (size_t i = 0; i < buckets.size(); ++i) {
            bool firstInBucket = true;
            for (const auto& pair : buckets[i]) {
                hashTableWidget->insertRow(row);
                
                auto* indexItem = new QTableWidgetItem(firstInBucket ? QString::number(i) : "");
                indexItem->setTextAlignment(Qt::AlignCenter);
                hashTableWidget->setItem(row, 0, indexItem);
                
                auto* keyItem = new QTableWidgetItem(QString::number(pair.first));
                keyItem->setTextAlignment(Qt::AlignCenter);
                hashTableWidget->setItem(row, 1, keyItem);
                
                auto* valueItem = new QTableWidgetItem(pair.second);
                hashTableWidget->setItem(row, 2, valueItem);
                
                firstInBucket = false;
                ++row;
            }
            
            if (buckets[i].begin() == buckets[i].end()) {
                hashTableWidget->insertRow(row);
                auto* indexItem = new QTableWidgetItem(QString::number(i));
                indexItem->setTextAlignment(Qt::AlignCenter);
                hashTableWidget->setItem(row, 0, indexItem);
                hashTableWidget->setItem(row, 1, new QTableWidgetItem("—"));
                hashTableWidget->setItem(row, 2, new QTableWidgetItem("пусто"));
                ++row;
            }
        }
    }
}

QString MainWindow::getIterOutput() {
    std::ostringstream oss;
    
    if (currentStructure == StructureType::BST_MAP) {
        oss << "Обход элементов (in-order):\n\n";
        int index = 0;
        for (auto it = bstMap.begin(); it != bstMap.end(); ++it) {
            oss << ++index << ". Ключ: " << it->first 
                << ", Значение: " << it->second.toStdString() << "\n";
        }
    } else if (currentStructure == StructureType::BST_SET) {
        oss << "Обход элементов (in-order):\n\n";
        int index = 0;
        for (auto it = bstSet.begin(); it != bstSet.end(); ++it) {
            oss << ++index << ". Ключ: " << it->first << "\n";
        }
    }
    
    return QString::fromStdString(oss.str());
}

void MainWindow::updateStatus() {
    size_t size = 0;
    QString name;
    
    switch (currentStructure) {
        case StructureType::BST_MAP:
            size = bstMap.size();
            name = "BST Map";
            break;
        case StructureType::BST_SET:
            size = bstSet.size();
            name = "BST Set";
            break;
        case StructureType::UNORDERED_MAP:
            size = unorderedMap.size();
            name = "Unordered Map";
            break;
    }
    
    sizeLabel->setText(QString("%1 | Размер: %2").arg(name).arg(size));
}

void MainWindow::onStructureChanged(int index) {
    currentStructure = static_cast<StructureType>(index);
    refreshDisplay();
}

void MainWindow::onInsert() {
    if (keyInput->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите ключ");
        return;
    }

    bool ok;
    int key = keyInput->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Ключ должен быть целым числом");
        return;
    }

    switch (currentStructure) {
        case StructureType::BST_MAP:
            bstMap.insert(key, valueInput->text());
            break;
        case StructureType::BST_SET:
            bstSet.insert(key);
            break;
        case StructureType::UNORDERED_MAP:
            unorderedMap.insert(key, valueInput->text());
            break;
    }

    refreshDisplay();
}

void MainWindow::onErase() {
    if (keyInput->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите ключ для удаления");
        return;
    }

    bool ok;
    int key = keyInput->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Ключ должен быть целым числом");
        return;
    }

    bool removed = false;
    switch (currentStructure) {
        case StructureType::BST_MAP:
            removed = bstMap.remove(key);
            break;
        case StructureType::BST_SET:
            removed = bstSet.remove(key);
            break;
        case StructureType::UNORDERED_MAP:
            removed = unorderedMap.erase(key);
            break;
    }

    if (!removed) {
        QMessageBox::information(this, "Информация", 
            QString("Ключ %1 не найден").arg(key));
    }

    refreshDisplay();
}

void MainWindow::onFindByKey() {
    bool ok;
    int key = QInputDialog::getInt(this, "Поиск по ключу", "Введите ключ:", 0, -1000000, 1000000, 1, &ok);
    
    if (!ok) return;

    switch (currentStructure) {
        case StructureType::BST_MAP: {
            if (bstMap.contains(key)) {
                QMessageBox::information(this, "Результат поиска", 
                    QString("Ключ: %1\nЗначение: %2").arg(key).arg(bstMap[key]));
            } else {
                QMessageBox::information(this, "Результат поиска", 
                    QString("Ключ %1 не найден").arg(key));
            }
            break;
        }
        case StructureType::BST_SET: {
            if (bstSet.contains(key)) {
                QMessageBox::information(this, "Результат поиска", 
                    QString("Элемент с ключом %1 присутствует в множестве").arg(key));
            } else {
                QMessageBox::information(this, "Результат поиска", 
                    QString("Элемент с ключом %1 отсутствует в множестве").arg(key));
            }
            break;
        }
        case StructureType::UNORDERED_MAP: {
            auto* value = unorderedMap.find(key);
            if (value) {
                QMessageBox::information(this, "Результат поиска", 
                    QString("Ключ: %1\nЗначение: %2").arg(key).arg(*value));
            } else {
                QMessageBox::information(this, "Результат поиска", 
                    QString("Ключ %1 не найден").arg(key));
            }
            break;
        }
    }
}

void MainWindow::onClear() {
    auto reply = QMessageBox::question(this, "Подтверждение",
        "Вы уверены, что хотите очистить структуру?",
        QMessageBox::Yes | QMessageBox::No);
        
    if (reply == QMessageBox::Yes) {
        switch (currentStructure) {
            case StructureType::BST_MAP:
                bstMap.clear();
                break;
            case StructureType::BST_SET:
                bstSet.clear();
                break;
            case StructureType::UNORDERED_MAP:
                unorderedMap.clear();
                break;
        }
        refreshDisplay();
    }
}

void MainWindow::onRandomInsert() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);
    
    QStringList values = {"Яблоко", "Машина", "Дом", "Кот", "Сон"};

    for (int i = 0; i < 5; ++i) {
        int key = dist(gen);
        switch (currentStructure) {
            case StructureType::BST_MAP:
                bstMap[key] = values[i];
                break;
            case StructureType::BST_SET:
                bstSet.insert(key);
                break;
            case StructureType::UNORDERED_MAP:
                unorderedMap[key] = values[i];
                break;
        }
    }

    refreshDisplay();
}

void MainWindow::onRehash() {
    if (currentStructure == StructureType::UNORDERED_MAP) {
        int newSize = hashSizeSpin->value();
        unorderedMap.rehash(newSize);
        refreshDisplay();
    }
}

void MainWindow::onShowIter() {
    QString output = getIterOutput();
    
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Обход");
    msgBox.setText(output);
    msgBox.exec();
}