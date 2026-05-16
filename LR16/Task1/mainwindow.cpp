#include "mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QStringList>
#include <QHeaderView>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), extractedSubtree(nullptr) {
    setupUI();
    updateTreeDisplay();
    updateStatus();
}

MainWindow::~MainWindow() {
    if (extractedSubtree) {
        BSTree tempTree;
        tempTree.insertSubtree(extractedSubtree);
        tempTree.clear();
    }
}

void MainWindow::setupUI() {
    setWindowTitle("Бинарное дерево поиска");
    setMinimumSize(1000, 700);

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

    QPushButton* traverseButton = new QPushButton("Обход");
    inputLayout->addWidget(traverseButton);

    mainLayout->addWidget(inputGroup);

    // Панель операций с поддеревьями
    QGroupBox* subtreeGroup = new QGroupBox("Операции с поддеревьями");
    QVBoxLayout* subtreeMainLayout = new QVBoxLayout(subtreeGroup);
    
    QHBoxLayout* subtreeLayout = new QHBoxLayout();
    QPushButton* removeSubtreeButton = new QPushButton("Удалить поддерево");
    QPushButton* insertSubtreeButton = new QPushButton("Вставить поддерево");
    subtreeLayout->addWidget(removeSubtreeButton);
    subtreeLayout->addWidget(insertSubtreeButton);
    subtreeLayout->addStretch();
    subtreeMainLayout->addLayout(subtreeLayout);
    
    // Добавляем информационную метку о состоянии поддерева
    subtreeStatusLabel = new QLabel("Извлеченное поддерево: отсутствует");
    subtreeStatusLabel->setStyleSheet("color: gray; font-style: italic; padding: 2px;");
    subtreeMainLayout->addWidget(subtreeStatusLabel);

    mainLayout->addWidget(subtreeGroup);

    // Панель операций с ветвями
    QGroupBox* branchGroup = new QGroupBox("Операции с ветвями");
    QVBoxLayout* branchLayout = new QVBoxLayout(branchGroup);

    QHBoxLayout* branchInputLayout = new QHBoxLayout();
    branchInputLayout->addWidget(new QLabel("Родительский ключ:"));
    parentKeyLineEdit = new QLineEdit();
    parentKeyLineEdit->setPlaceholderText("Ключ родителя");
    parentKeyLineEdit->setFixedWidth(100);
    branchInputLayout->addWidget(parentKeyLineEdit);

    branchInputLayout->addWidget(new QLabel("Дочерний ключ:"));
    childKeyLineEdit = new QLineEdit();
    childKeyLineEdit->setPlaceholderText("Ключ потомка");
    childKeyLineEdit->setFixedWidth(100);
    branchInputLayout->addWidget(childKeyLineEdit);

    branchInputLayout->addStretch();
    branchLayout->addLayout(branchInputLayout);

    QHBoxLayout* branchButtonLayout = new QHBoxLayout();
    QPushButton* insertBranchButton = new QPushButton("Вставить ветвь");
    QPushButton* removeBranchButton = new QPushButton("Удалить ветвь");
    QPushButton* insertAtPositionButton = new QPushButton("Вставить в позицию");

    branchButtonLayout->addWidget(insertBranchButton);
    branchButtonLayout->addWidget(removeBranchButton);
    branchButtonLayout->addWidget(insertAtPositionButton);
    branchButtonLayout->addStretch();
    branchLayout->addLayout(branchButtonLayout);

    mainLayout->addWidget(branchGroup);

    // Панель поиска LCA
    QGroupBox* lcaGroup = new QGroupBox("Поиск наименьшего общего предка (LCA)");
    QHBoxLayout* lcaLayout = new QHBoxLayout(lcaGroup);

    lcaLayout->addWidget(new QLabel("Ключ 1:"));
    key1LineEdit = new QLineEdit();
    key1LineEdit->setPlaceholderText("Первый ключ");
    key1LineEdit->setFixedWidth(100);
    lcaLayout->addWidget(key1LineEdit);

    lcaLayout->addWidget(new QLabel("Ключ 2:"));
    key2LineEdit = new QLineEdit();
    key2LineEdit->setPlaceholderText("Второй ключ");
    key2LineEdit->setFixedWidth(100);
    lcaLayout->addWidget(key2LineEdit);

    QPushButton* findLCAButton = new QPushButton("Найти LCA");
    lcaLayout->addWidget(findLCAButton);
    lcaLayout->addStretch();

    mainLayout->addWidget(lcaGroup);

    // Панель управления
    QHBoxLayout* controlLayout = new QHBoxLayout();
    QPushButton* clearButton = new QPushButton("Очистить дерево");
    controlLayout->addWidget(clearButton);
    controlLayout->addStretch();

    statusLabel = new QLabel("Размер дерева: 0");
    controlLayout->addWidget(statusLabel);
    mainLayout->addLayout(controlLayout);

    // Отображение дерева
    treeWidget = new QTreeWidget();
    treeWidget->setHeaderLabels(QStringList() << "Ключ" << "Данные");
    treeWidget->setColumnWidth(0, 200);
    treeWidget->header()->setStretchLastSection(true);

    mainLayout->addWidget(treeWidget);

    // Подключение сигналов
    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddClicked);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveClicked);
    connect(findButton, &QPushButton::clicked, this, &MainWindow::onFindClicked);
    connect(traverseButton, &QPushButton::clicked, this, &MainWindow::onTraverseClicked);
    connect(insertSubtreeButton, &QPushButton::clicked, this, &MainWindow::onInsertSubtreeClicked);
    connect(removeSubtreeButton, &QPushButton::clicked, this, &MainWindow::onRemoveSubtreeClicked);
    connect(insertBranchButton, &QPushButton::clicked, this, &MainWindow::onInsertBranchClicked);
    connect(removeBranchButton, &QPushButton::clicked, this, &MainWindow::onRemoveBranchClicked);
    connect(insertAtPositionButton, &QPushButton::clicked, this, &MainWindow::onInsertAtPositionClicked);
    connect(findLCAButton, &QPushButton::clicked, this, &MainWindow::onFindLCAClicked);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::onClearClicked);
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

    addNodeToTreeWidget(root, rootItem);
    treeWidget->addTopLevelItem(rootItem);
    treeWidget->expandAll();
}

void MainWindow::addNodeToTreeWidget(Node* node, QTreeWidgetItem* parentItem) {
    if (node->left) {
        QTreeWidgetItem* leftItem = new QTreeWidgetItem();
        leftItem->setText(0, QString::number(node->left->key));
        leftItem->setText(1, node->left->data);
        parentItem->addChild(leftItem);
        addNodeToTreeWidget(node->left, leftItem);
    }

    if (node->right) {
        QTreeWidgetItem* rightItem = new QTreeWidgetItem();
        rightItem->setText(0, QString::number(node->right->key));
        rightItem->setText(1, node->right->data);
        parentItem->addChild(rightItem);
        addNodeToTreeWidget(node->right, rightItem);
    }
}

void MainWindow::updateStatus() {
    statusLabel->setText(QString("Размер дерева: %1").arg(tree.getSize()));
}

void MainWindow::onAddClicked() {
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

    tree.add(data, key);
    updateTreeDisplay();
    updateStatus();

    keyLineEdit->clear();
    dataLineEdit->clear();
}

void MainWindow::onRemoveClicked() {
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

void MainWindow::onFindClicked() {
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
                QString("Узел найден!\nКлюч: %1\nСтрока: \"%2\"")
                .arg(key).arg(node->data));
        } else {
            QMessageBox::warning(this, "Результат", QString("Узел с ключом %1 не найден!").arg(key));
        }
    }
}

void MainWindow::onTraverseClicked() {
    QVector<Node*> nodes = tree.traverse();
    if (nodes.isEmpty()) {
        QMessageBox::information(this, "Обход дерева", "Дерево пусто!");
        return;
    }

    QString result;
    for (Node* node : nodes) {
        result += QString("Ключ: %1, Строка: \"%2\"\n").arg(node->key).arg(node->data);
    }

    QMessageBox::information(this, "Обход в порядке возрастания ключей", result);
}

void MainWindow::onRemoveSubtreeClicked() {
    if (tree.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Дерево пусто!");
        return;
    }

    bool ok;
    int key = QInputDialog::getInt(this, "Извлечение поддерева", 
        "Введите ключ корня поддерева для извлечения:", 0, -99999, 99999, 1, &ok);

    if (ok) {
        // Очищаем предыдущее извлеченное поддерево, если оно есть
        if (extractedSubtree) {
            BSTree tempTree;
            tempTree.insertSubtree(extractedSubtree);
            tempTree.clear();
            extractedSubtree = nullptr;
        }

        extractedSubtree = tree.removeSubtree(key);
        if (extractedSubtree) {
            updateTreeDisplay();
            updateStatus();
            
            // Обновляем информационную метку
            subtreeStatusLabel->setText(QString("Извлеченное поддерево: корень с ключом %1").arg(key));
            subtreeStatusLabel->setStyleSheet("color: green; font-weight: bold; padding: 2px;");
            
            QMessageBox::information(this, "Успех", 
                QString("Поддерево с корнем %1 извлечено и сохранено.\n"
                        "Теперь вы можете вставить его обратно в дерево.").arg(key));
        } else {
            subtreeStatusLabel->setText("Извлеченное поддерево: отсутствует");
            subtreeStatusLabel->setStyleSheet("color: gray; font-style: italic; padding: 2px;");
            QMessageBox::warning(this, "Ошибка", QString("Узел с ключом %1 не найден!").arg(key));
        }
    }
}

void MainWindow::onInsertSubtreeClicked() {
    if (extractedSubtree) {
        QString message = QString("Вы хотите вставить ранее извлеченное поддерево с корнем %1?").arg(extractedSubtree->key);
        
        if (QMessageBox::question(this, "Вставка поддерева", message) == QMessageBox::Yes) {
            if (tree.insertSubtree(extractedSubtree)) {
                updateTreeDisplay();
                updateStatus();
                
                // Очищаем извлеченное поддерево
                BSTree tempTree;
                tempTree.insertSubtree(extractedSubtree);
                tempTree.clear();
                extractedSubtree = nullptr;
                
                // Обновляем информационную метку
                subtreeStatusLabel->setText("Извлеченное поддерево: отсутствует");
                subtreeStatusLabel->setStyleSheet("color: gray; font-style: italic; padding: 2px;");
                
                QMessageBox::information(this, "Успех", "Поддерево успешно вставлено в дерево!");
            } else {
                QMessageBox::warning(this, "Ошибка", 
                    "Не удалось вставить поддерево. Возможно, ключ корня поддерева уже существует в дереве.");
            }
        }
    } else {
        QMessageBox::information(this, "Информация", 
            "Нет извлеченного поддерева для вставки.\n\n"
            "Инструкция:\n"
            "1. Сначала нажмите кнопку \"Удалить поддерево\"\n"
            "2. Введите ключ узла, поддерево которого хотите извлечь\n"
            "3. Затем нажмите \"Вставить поддерево\" для вставки извлеченного поддерева\n\n"
            "Эта функция позволяет перемещать поддеревья внутри дерева.");
    }
}

void MainWindow::onInsertBranchClicked() {
    bool parentKeyOk, childKeyOk;
    int parentKey = parentKeyLineEdit->text().toInt(&parentKeyOk);
    int childKey = childKeyLineEdit->text().toInt(&childKeyOk);

    if (!parentKeyOk || !childKeyOk) {
        QMessageBox::warning(this, "Ошибка", "Неверные ключи!");
        return;
    }

    if (!tree.contains(parentKey)) {
        QMessageBox::warning(this, "Ошибка", QString("Родительский узел с ключом %1 не найден!").arg(parentKey));
        return;
    }

    if (tree.contains(childKey)) {
        QMessageBox::warning(this, "Ошибка", QString("Узел с ключом %1 уже существует!").arg(childKey));
        return;
    }

    // Запрашиваем строковое значение для нового узла
    QString data = QInputDialog::getText(this, "Значение узла", 
        "Введите строковое значение для нового узла:", QLineEdit::Normal, 
        QString("Ветвь_%1").arg(childKey));

    if (data.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Значение не может быть пустым!");
        return;
    }

    QStringList items;
    items << "Левый потомок" << "Правый потомок";
    bool ok;
    QString choice = QInputDialog::getItem(this, "Выбор позиции", 
        "Выберите позицию для вставки:", items, 0, false, &ok);

    if (ok) {
        bool asLeftChild = (choice == "Левый потомок");
        if (tree.insertBranch(data, childKey, parentKey, asLeftChild)) {
            updateTreeDisplay();
            updateStatus();
            QMessageBox::information(this, "Успех", 
                QString("Ветвь с ключом %1 успешно вставлена как %2 потомок узла %3!")
                .arg(childKey).arg(asLeftChild ? "левый" : "правый").arg(parentKey));
        } else {
            QMessageBox::warning(this, "Ошибка", "Позиция уже занята!");
        }
    }

    parentKeyLineEdit->clear();
    childKeyLineEdit->clear();
}

void MainWindow::onRemoveBranchClicked() {
    bool ok;
    int key = QInputDialog::getInt(this, "Удаление ветви", 
        "Введите ключ узла для удаления всей ветви:", 0, -99999, 99999, 1, &ok);

    if (ok) {
        if (tree.removeBranch(key)) {
            updateTreeDisplay();
            updateStatus();
            QMessageBox::information(this, "Успех", QString("Ветвь с корнем %1 удалена!").arg(key));
        } else {
            QMessageBox::warning(this, "Ошибка", QString("Узел с ключом %1 не найден!").arg(key));
        }
    }
}

void MainWindow::onInsertAtPositionClicked() {
    bool parentKeyOk, childKeyOk;
    int parentKey = parentKeyLineEdit->text().toInt(&parentKeyOk);
    int childKey = childKeyLineEdit->text().toInt(&childKeyOk);

    if (!parentKeyOk || !childKeyOk) {
        QMessageBox::warning(this, "Ошибка", "Неверные ключи!");
        return;
    }

    if (!tree.contains(parentKey)) {
        QMessageBox::warning(this, "Ошибка", QString("Родительский узел с ключом %1 не найден!").arg(parentKey));
        return;
    }

    if (tree.contains(childKey)) {
        QMessageBox::warning(this, "Ошибка", QString("Узел с ключом %1 уже существует!").arg(childKey));
        return;
    }

    QString data = QInputDialog::getText(this, "Вставка в позицию", 
        "Введите строковое значение для нового узла:", QLineEdit::Normal, 
        QString("Узел_%1").arg(childKey));

    if (data.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Значение не может быть пустым!");
        return;
    }

    QStringList items;
    items << "Левый потомок" << "Правый потомок";
    bool ok;
    QString choice = QInputDialog::getItem(this, "Выбор позиции", 
        "Выберите позицию для вставки:", items, 0, false, &ok);

    if (ok) {
        bool asLeftChild = (choice == "Левый потомок");
        if (tree.insertAtPosition(data, childKey, parentKey, asLeftChild)) {
            updateTreeDisplay();
            updateStatus();
            QMessageBox::information(this, "Успех", 
                QString("Элемент с ключом %1 успешно вставлен в указанную позицию как %2 потомок узла %3!")
                .arg(childKey).arg(asLeftChild ? "левый" : "правый").arg(parentKey));
        } else {
            QMessageBox::warning(this, "Ошибка", "Позиция уже занята!");
        }
    }

    parentKeyLineEdit->clear();
    childKeyLineEdit->clear();
}

void MainWindow::onFindLCAClicked() {
    if (tree.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Дерево пусто!");
        return;
    }

    bool key1Ok, key2Ok;
    int key1 = key1LineEdit->text().toInt(&key1Ok);
    int key2 = key2LineEdit->text().toInt(&key2Ok);

    if (!key1Ok || !key2Ok) {
        QMessageBox::warning(this, "Ошибка", "Неверные ключи!");
        return;
    }

    if (!tree.contains(key1)) {
        QMessageBox::warning(this, "Ошибка", QString("Узел с ключом %1 не найден!").arg(key1));
        return;
    }

    if (!tree.contains(key2)) {
        QMessageBox::warning(this, "Ошибка", QString("Узел с ключом %1 не найден!").arg(key2));
        return;
    }

    Node* lca = tree.findLCA(key1, key2);
    if (lca) {
        QMessageBox::information(this, "Результат LCA",
            QString("Наименьший общий предок для узлов %1 и %2:\nКлюч: %3\nСтрока: \"%4\"")
            .arg(key1).arg(key2).arg(lca->key).arg(lca->data));
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось найти общего предка.");
    }

    key1LineEdit->clear();
    key2LineEdit->clear();
}

void MainWindow::onClearClicked() {
    if (tree.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Дерево уже пусто!");
        return;
    }

    if (QMessageBox::question(this, "Очистка", "Вы уверены, что хотите очистить дерево?") == QMessageBox::Yes) {
        if (extractedSubtree) {
            BSTree tempTree;
            tempTree.insertSubtree(extractedSubtree);
            tempTree.clear();
            extractedSubtree = nullptr;
            
            // Обновляем информационную метку
            subtreeStatusLabel->setText("Извлеченное поддерево: отсутствует");
            subtreeStatusLabel->setStyleSheet("color: gray; font-style: italic; padding: 2px;");
        }
        tree.clear();
        updateTreeDisplay();
        updateStatus();
        QMessageBox::information(this, "Очистка", "Дерево очищено!");
    }
}