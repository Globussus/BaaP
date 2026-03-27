#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setupUI();
    Pair<Vector<int>, Vector<Pair<int, double>>> initial;
    mainData.push_back(initial);
    refreshGrids();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    this->resize(1150, 650);
    this->setWindowTitle("Vector и Pair");

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QLabel* label1 = new QLabel("Первая пара (Vector<int>):", centralWidget);
    label1->setGeometry(20, 15, 250, 20);
    tableInts = new QTableWidget(centralWidget);
    tableInts->setGeometry(20, 40, 300, 550);
    tableInts->setColumnCount(1);
    tableInts->setHorizontalHeaderLabels({"Столбец 1"});

    QLabel* label2 = new QLabel("Вторая пара (Vector<Pair<int, double>>):", centralWidget);
    label2->setGeometry(340, 15, 300, 20);
    tablePairs = new QTableWidget(centralWidget);
    tablePairs->setGeometry(340, 40, 360, 550);
    tablePairs->setColumnCount(2);
    tablePairs->setHorizontalHeaderLabels({"Целое", "Дробное"});

    int bx = 720, by = 40, bw = 200, bh = 30;

    QLabel* vHeader = new QLabel("Функции Vector:", centralWidget);
    vHeader->setGeometry(bx, by - 25, bw, 20);
    vHeader->setStyleSheet("font-weight: bold;");

    auto btnV = [&](QString name, auto slot) {
        QPushButton* b = new QPushButton(name, centralWidget);
        b->setGeometry(bx, by, bw, bh);
        connect(b, &QPushButton::clicked, this, slot);
        by += 35;
    };

    btnV("push_back", &MainWindow::onPushBack);
    btnV("pop_back", &MainWindow::onPopBack);
    btnV("insert (в начало)", &MainWindow::onInsert);
    btnV("erase (в начале)", &MainWindow::onErase);
    btnV("assign (5 элементов)", &MainWindow::onAssign);
    btnV("resize", &MainWindow::onResize);
    btnV("at (доступ по индексу)", &MainWindow::onAt);
    btnV("front / back", &MainWindow::onFrontBack);
    btnV("clear", &MainWindow::onClear);

    by += 20;
    QLabel* pHeader = new QLabel("Функции Pair:", centralWidget);
    pHeader->setGeometry(bx, by, bw, 20);
    pHeader->setStyleSheet("font-weight: bold; color: darkblue;");
    by += 25;

    auto btnP = [&](QString name, auto slot) {
        QPushButton* b = new QPushButton(name, centralWidget);
        b->setGeometry(bx, by, bw, bh);
        connect(b, &QPushButton::clicked, this, slot);
        by += 35;
    };

    btnP("make_pair (пересоздать)", &MainWindow::onPairMake);
    btnP("Заполнить first", &MainWindow::onPairSetFirst);
    btnP("Заполнить second", &MainWindow::onPairSetSecond);
    btnP("Вложенная пара (тест)", &MainWindow::onShowNested);
}

void MainWindow::refreshGrids() {
    if (mainData.empty()) return;
    auto& p = mainData[0];
    
    tableInts->setRowCount(p.first.size());
    for(size_t i = 0; i < p.first.size(); ++i) {
        tableInts->setItem(i, 0, new QTableWidgetItem(QString::number(p.first[i])));
    }

    tablePairs->setRowCount(p.second.size());
    for(size_t i = 0; i < p.second.size(); ++i) {
        tablePairs->setItem(i, 0, new QTableWidgetItem(QString::number(p.second[i].first)));
        tablePairs->setItem(i, 1, new QTableWidgetItem(QString::number(p.second[i].second)));
    }
}

void MainWindow::onPushBack() {
    bool ok;
    int val = QInputDialog::getInt(this, "Ввод", "Введите число:", 0, -1000, 1000, 1, &ok);
    if(ok) {
        mainData[0].first.push_back(val);
        refreshGrids();
    }
}

void MainWindow::onPopBack() {
    if(!mainData[0].first.empty()) {
        mainData[0].first.pop_back();
        refreshGrids();
    }
}

void MainWindow::onInsert() {
    bool ok;
    int n = QInputDialog::getInt(this, "Число", "Введите число:", 0, 0, 100, 1, &ok);
    if(ok) {
        mainData[0].first.insert(mainData[0].first.begin(), n);
        refreshGrids();
    }
}

void MainWindow::onErase() {
    if(!mainData[0].first.empty()) {
        mainData[0].first.erase(mainData[0].first.begin());
        refreshGrids();
    }
}

void MainWindow::onAssign() {
    bool ok1, ok2;
    int size = QInputDialog::getInt(this, "Размер", "Введите размер:", 0, 0, 100, 1, &ok1);
    int number = QInputDialog::getInt(this, "Число", "Введите число:", 0, 0, 100, 1, &ok2);
    if (ok1 && ok2) {
        mainData[0].first.assign(size, number);
        refreshGrids();
    }
}

void MainWindow::onResize() {
    bool ok;
    int n = QInputDialog::getInt(this, "Размер", "Новый размер:", 0, 0, 100, 1, &ok);
    if(ok) {
        mainData[0].first.resize(n, 0);
        refreshGrids();
    }
}

void MainWindow::onAt() {
    if(mainData[0].first.empty()) return;
    bool ok;
    int idx = QInputDialog::getInt(this, "Доступ", "Индекс:", 0, 0, mainData[0].first.size()-1, 1, &ok);
    if(ok) {
        QMessageBox::information(this, "Результат", "Значение: " + QString::number(mainData[0].first.at(idx)));
    }
}

void MainWindow::onFrontBack() {
    if(mainData[0].first.empty()) return;
    QString res = QString("Первый: %1\nПоследний: %2")
                  .arg(mainData[0].first.front())
                  .arg(mainData[0].first.back());
    QMessageBox::information(this, "Доступ", res);
}

void MainWindow::onClear() {
    mainData[0].first.clear();
    refreshGrids();
}

void MainWindow::onPairMake() {
    Vector<int> v1;
    Vector<Pair<int, double>> v2;
    mainData[0] = Pair<Vector<int>, Vector<Pair<int, double>>>::make_pair(v1, v2);
    refreshGrids();
}

void MainWindow::onPairSetFirst() {
    mainData[0].first.clear();
    for(int i = 0; i < 5; i++) mainData[0].first.push_back(i * 11);
    refreshGrids();
}

void MainWindow::onPairSetSecond() {
    mainData[0].second.clear();
    mainData[0].second.push_back(Pair<int, double>(1, 1.1));
    mainData[0].second.push_back(Pair<int, double>(2, 2.2));
    refreshGrids();
}

void MainWindow::onShowNested() {
    Pair<Pair<int, int>, Pair<int, int>> a(Pair<int, int>(10, 20), Pair<int, int>(30, 40));
    QString out = QString("Вложенная пара:\n((%1, %2), (%3, %4))")
                  .arg(a.first.first).arg(a.first.second)
                  .arg(a.second.first).arg(a.second.second);
    QMessageBox::information(this, "Тест вложенности", out);
}