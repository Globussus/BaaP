#include "mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QStringList>
#include <QRandomGenerator>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setupUI();
    updateTreeDisplay();
    updateStatus();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    setWindowTitle("Task2");
    setMinimumSize(1000, 600);
    
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(5);
    
    // Панель ввода
    QGroupBox* inputGroup = new QGroupBox("Ввод данных");
    QHBoxLayout* inputLayout = new QHBoxLayout(inputGroup);
    
    inputLayout->addWidget(new QLabel("Ключ:"));
    keyLineEdit = new QLineEdit();
    keyLineEdit->setPlaceholderText("Целочисленный ключ");
    keyLineEdit->setFixedWidth(100);
    inputLayout->addWidget(keyLineEdit);
    
    inputLayout->addWidget(new QLabel("Строка:"));
    dataLineEdit = new QLineEdit();
    dataLineEdit->setPlaceholderText("Строковое значение");
    dataLineEdit->setMinimumWidth(200);
    inputLayout->addWidget(dataLineEdit);
    
    QPushButton* addButton = new QPushButton("Добавить");
    inputLayout->addWidget(addButton);
    
    QPushButton* removeButton = new QPushButton("Удалить");
    inputLayout->addWidget(removeButton);
    
    QPushButton* findButton = new QPushButton("Найти");
    inputLayout->addWidget(findButton);
    
    mainLayout->addWidget(inputGroup);
    
    // Панель операций
    QGroupBox* operationsGroup = new QGroupBox("Операции");
    QHBoxLayout* operationsLayout = new QHBoxLayout(operationsGroup);
    
    QPushButton* balanceButton = new QPushButton("Балансировка");
    QPushButton* clearButton = new QPushButton("Очистить");
    QPushButton* loadArrayButton = new QPushButton("Загрузить массив");
    QPushButton* randomButton = new QPushButton("Случайные");
    
    operationsLayout->addWidget(balanceButton);
    operationsLayout->addWidget(clearButton);
    operationsLayout->addWidget(loadArrayButton);
    operationsLayout->addWidget(randomButton);
    
    mainLayout->addWidget(operationsGroup);
    
    // Панель обходов
    QGroupBox* traversalGroup = new QGroupBox("Обходы дерева");
    QHBoxLayout* traversalLayout = new QHBoxLayout(traversalGroup);
    
    QPushButton* preOrderButton = new QPushButton("Прямой обход");
    QPushButton* postOrderButton = new QPushButton("Обратный обход");
    QPushButton* inOrderButton = new QPushButton("По возрастанию");
    QPushButton* countCharsButton = new QPushButton("Подсчёт символов");
    
    traversalLayout->addWidget(preOrderButton);
    traversalLayout->addWidget(postOrderButton);
    traversalLayout->addWidget(inOrderButton);
    traversalLayout->addWidget(countCharsButton);
    
    mainLayout->addWidget(traversalGroup);
    
    // Панель статуса
    QHBoxLayout* statusLayout = new QHBoxLayout();
    statusLabel = new QLabel("Размер дерева: 0");
    charCountLabel = new QLabel("Всего символов: 0");
    statusLayout->addWidget(statusLabel);
    statusLayout->addStretch();
    statusLayout->addWidget(charCountLabel);
    mainLayout->addLayout(statusLayout);
    
    // Отображение дерева
    treeWidget = new QTreeWidget();
    treeWidget->setHeaderLabels(QStringList() << "Ключ" << "Данные" << "Высота");
    treeWidget->setColumnWidth(0, 240);
    treeWidget->setColumnWidth(1, 500);
    treeWidget->setColumnWidth(2, 180);
    treeWidget->header()->setStretchLastSection(true);
    
    mainLayout->addWidget(treeWidget);
    
    // Подключение сигналов
    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddButtonClicked);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveButtonClicked);
    connect(findButton, &QPushButton::clicked, this, &MainWindow::onFindButtonClicked);
    connect(balanceButton, &QPushButton::clicked, this, &MainWindow::onBalanceButtonClicked);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::onClearButtonClicked);
    connect(loadArrayButton, &QPushButton::clicked, this, &MainWindow::onLoadArrayButtonClicked);
    connect(randomButton, &QPushButton::clicked, this, &MainWindow::onRandomButtonClicked);
    connect(preOrderButton, &QPushButton::clicked, this, &MainWindow::onShowPreOrder);
    connect(postOrderButton, &QPushButton::clicked, this, &MainWindow::onShowPostOrder);
    connect(inOrderButton, &QPushButton::clicked, this, &MainWindow::onShowInOrder);
    connect(countCharsButton, &QPushButton::clicked, this, &MainWindow::onCountCharacters);
}

void MainWindow::updateTreeDisplay() {
    treeWidget->clear();
    
    if (tree.isEmpty()) {
        treeWidget->addTopLevelItem(new QTreeWidgetItem(QStringList() << "Дерево пусто"));
        return;
    }
    
    Node* root = tree.getRoot();
    QTreeWidgetItem* rootItem = new QTreeWidgetItem();
    rootItem->setText(0, QString::number(root->key));
    rootItem->setText(1, root->data);
    rootItem->setText(2, QString::number(root->height));
    
    addNodeToTreeWidget(root, rootItem);
    treeWidget->addTopLevelItem(rootItem);
    treeWidget->expandAll();
}

void MainWindow::addNodeToTreeWidget(Node* node, QTreeWidgetItem* parentItem) {
    if (node->left) {
        QTreeWidgetItem* leftItem = new QTreeWidgetItem();
        leftItem->setText(0, QString::number(node->left->key));
        leftItem->setText(1, node->left->data);
        leftItem->setText(2, QString::number(node->left->height));
        parentItem->addChild(leftItem);
        addNodeToTreeWidget(node->left, leftItem);
    }
    
    if (node->right) {
        QTreeWidgetItem* rightItem = new QTreeWidgetItem();
        rightItem->setText(0, QString::number(node->right->key));
        rightItem->setText(1, node->right->data);
        rightItem->setText(2, QString::number(node->right->height));
        parentItem->addChild(rightItem);
        addNodeToTreeWidget(node->right, rightItem);
    }
}

void MainWindow::updateStatus() {
    statusLabel->setText(QString("Размер дерева: %1").arg(tree.getSize()));
    updateCharCount();
}

void MainWindow::updateCharCount() {
    int totalChars = tree.getTotalCharacters();
    charCountLabel->setText(QString("Всего символов: %1").arg(totalChars));
}

void MainWindow::onAddButtonClicked() {
    bool keyOk;
    int key = keyLineEdit->text().toInt(&keyOk);
    QString data = dataLineEdit->text();
    
    if (!keyOk) {
        QMessageBox::warning(this, "Ошибка", "Неверный целочисленный ключ!");
        return;
    }
    
    if (data.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Строка не может быть пустой!");
        return;
    }
    
    if (tree.contains(key)) {
        QMessageBox::warning(this, "Ошибка", QString("Узел с ключом %1 уже существует!").arg(key));
        return;
    }
    
    tree.insert(data, key);
    updateTreeDisplay();
    updateStatus();
    
    keyLineEdit->clear();
    dataLineEdit->clear();
}

void MainWindow::onRemoveButtonClicked() {
    if (tree.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Дерево пусто!");
        return;
    }
    
    bool ok;
    int key = QInputDialog::getInt(this, "Удаление", "Введите ключ для удаления:", 0, -99999, 99999, 1, &ok);
    
    if (ok) {
        if (tree.remove(key)) {
            updateTreeDisplay();
            updateStatus();
            QMessageBox::information(this, "Успех", QString("Узел с ключом %1 удалён!").arg(key));
        } else {
            QMessageBox::warning(this, "Ошибка", QString("Узел с ключом %1 не найден!").arg(key));
        }
    }
}

void MainWindow::onFindButtonClicked() {
    if (tree.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Дерево пусто!");
        return;
    }
    
    bool ok;
    int key = QInputDialog::getInt(this, "Поиск", "Введите ключ для поиска:", 0, -99999, 99999, 1, &ok);
    
    if (ok) {
        Node* node = tree.find(key);
        if (node) {
            QMessageBox::information(this, "Результат", 
                QString("Узел найден!\nКлюч: %1\nСтрока: \"%2\"\nВысота: %3")
                .arg(key).arg(node->data).arg(node->height));
        } else {
            QMessageBox::warning(this, "Результат", QString("Узел с ключом %1 не найден!").arg(key));
        }
    }
}

void MainWindow::onBalanceButtonClicked() {
    if (tree.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Дерево пусто!");
        return;
    }
    
    // Получаем все узлы в порядке возрастания ключей
    QVector<Node*> nodes = tree.getInOrder();
    
    // Создаём новое дерево, копируя данные из старых узлов
    AVLTree newTree;
    for (Node* node : nodes) {
        newTree.insert(node->data, node->key);
    }
    
    // Очищаем текущее дерево (но не удаляем узлы, так как они будут использованы)
    // Используем прямое присваивание через указатели без удаления старых узлов
    tree = newTree;
    
    updateTreeDisplay();
    QMessageBox::information(this, "Балансировка", "Дерево успешно сбалансировано!");
}

void MainWindow::onClearButtonClicked() {
    if (tree.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Дерево уже пусто!");
        return;
    }
    
    if (QMessageBox::question(this, "Очистка", "Вы уверены?") == QMessageBox::Yes) {
        while (!tree.isEmpty()) {
            tree.remove(tree.getInOrder().first()->key);
        }
        updateTreeDisplay();
        updateStatus();
        QMessageBox::information(this, "Очистка", "Дерево очищено!");
    }
}

void MainWindow::onLoadArrayButtonClicked() {
    bool ok;
    QString text = QInputDialog::getText(this, "Загрузка массива", 
        "Введите данные в формате:\nключ-значение/ключ-значение\n\nПример:\n1-Привет/2-Мир/3-AVL дерево\n\nИли многострочный вариант:\n1-Привет\n2-Мир\n3-AVL дерево",
        QLineEdit::Normal, "1-Строка1/2-Строка2/3-Строка3", &ok);
    
    if (ok && !text.isEmpty()) {
        tree.clear();
        
        QStringList pairs;
        // Поддерживаем как разделение через / так и через перенос строки
        if (text.contains('/')) {
            pairs = text.split("/", Qt::SkipEmptyParts);
        } else {
            pairs = text.split("\n", Qt::SkipEmptyParts);
        }
        
        int successCount = 0;
        QString errors;
        
        for (const QString& pair : pairs) {
            QString trimmedPair = pair.trimmed();
            if (trimmedPair.isEmpty()) continue;
            
            int dashPos = trimmedPair.indexOf('-');
            if (dashPos > 0) {
                QString keyStr = trimmedPair.left(dashPos).trimmed();
                QString data = trimmedPair.mid(dashPos + 1).trimmed();
                
                bool keyOk;
                int key = keyStr.toInt(&keyOk);
                
                if (keyOk && !data.isEmpty()) {
                    if (!tree.contains(key)) {
                        tree.insert(data, key);
                        successCount++;
                    } else {
                        errors += QString("Ключ %1 уже существует, пропущен: %2\n").arg(key).arg(trimmedPair);
                    }
                } else {
                    errors += QString("Ошибка в паре: %1 (нужен формат ключ-значение)\n").arg(trimmedPair);
                }
            } else {
                errors += QString("Нет дефиса в паре: %1\n").arg(trimmedPair);
            }
        }
        
        updateTreeDisplay();
        updateStatus();
        
        if (successCount > 0) {
            QString msg = QString("Загружено %1 элементов").arg(successCount);
            if (!errors.isEmpty()) {
                msg += "\n\nОшибки:\n" + errors;
            }
            QMessageBox::information(this, "Загрузка", msg);
        } else {
            QMessageBox::warning(this, "Ошибка", 
                "Не удалось загрузить ни одного элемента.\n\n" + errors +
                "\nПравильный формат: ключ-значение\nПример: 1-Привет/2-Мир/3-Дерево");
        }
    }
}

void MainWindow::onRandomButtonClicked() {
    bool ok;
    int count = QInputDialog::getInt(this, "Случайные данные", 
        "Введите количество элементов (1-30):", 10, 1, 30, 1, &ok);
    
    if (ok) {
        while (!tree.isEmpty()) {
            tree.remove(tree.getInOrder().first()->key);
        }
        
        QRandomGenerator* gen = QRandomGenerator::global();
        QStringList words = {"Яблоко", "Банан", "Вишня", "Дерево", "Слон", "Гром", 
                            "Дом", "Медведь", "Пчела", "Крот", "Машина"};
        
        for (int i = 0; i < count; i++) {
            int key = gen->bounded(1, 1000);
            QString word = words[gen->bounded(words.size())] + QString::number(gen->bounded(1, 100));
            
            if (!tree.contains(key)) {
                tree.insert(word, key);
            } else {
                i--;
            }
        }
        
        updateTreeDisplay();
        updateStatus();
        QMessageBox::information(this, "Генерация", QString("Сгенерировано %1 случайных элементов!").arg(count));
    }
}

void MainWindow::onShowPreOrder() {
    QVector<Node*> nodes = tree.getPreOrder();
    if (nodes.isEmpty()) {
        QMessageBox::information(this, "Прямой обход", "Дерево пусто!");
        return;
    }
    
    QString result;
    for (Node* node : nodes) {
        result += QString("Ключ: %1, Строка: \"%2\"\n").arg(node->key).arg(node->data);
    }
    
    QMessageBox::information(this, "Прямой обход (корень-левый-правый)", result);
}

void MainWindow::onShowPostOrder() {
    QVector<Node*> nodes = tree.getPostOrder();
    if (nodes.isEmpty()) {
        QMessageBox::information(this, "Обратный обход", "Дерево пусто!");
        return;
    }
    
    QString result;
    for (Node* node : nodes) {
        result += QString("Ключ: %1, Строка: \"%2\"\n").arg(node->key).arg(node->data);
    }
    
    QMessageBox::information(this, "Обратный обход (левый-правый-корень)", result);
}

void MainWindow::onShowInOrder() {
    QVector<Node*> nodes = tree.getInOrder();
    if (nodes.isEmpty()) {
        QMessageBox::information(this, "Обход по возрастанию", "Дерево пусто!");
        return;
    }
    
    QString result;
    for (Node* node : nodes) {
        result += QString("Ключ: %1, Строка: \"%2\"\n").arg(node->key).arg(node->data);
    }
    
    QMessageBox::information(this, "Обход в порядке возрастания ключей", result);
}

void MainWindow::onCountCharacters() {
    int totalChars = tree.getTotalCharacters();
    QString message = QString("Общее количество символов во всех строках: %1")
                      .arg(totalChars);
    
    QMessageBox::information(this, "Подсчёт символов", message);
}