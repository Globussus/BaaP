#include "mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDate>
#include <QHeaderView>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    table = new QTableWidget(0, 5);
    table->setHorizontalHeaderLabels({"Дата", "След. день", "Неделя", "До ДР", "До след. в списке"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainLayout->addWidget(table);

    QVBoxLayout *bottomLayout = new QVBoxLayout();

    QHBoxLayout *inputLayout = new QHBoxLayout();
    bdayInput = new QLineEdit();
    bdayInput->setPlaceholderText("Ваш ДР (ДД.ММ.ГГГГ)");
    newDateInput = new QLineEdit();
    newDateInput->setPlaceholderText("Новая дата (ДД.ММ.ГГГГ)");
    inputLayout->addWidget(bdayInput);
    inputLayout->addWidget(newDateInput);

    QHBoxLayout *buttonsLayout1 = new QHBoxLayout();
    QPushButton *btnOpen = new QPushButton("Открыть .txt");
    QPushButton *btnAdd = new QPushButton("Добавить");
    QPushButton *btnDelete = new QPushButton("Удалить");
    QPushButton *btnNext = new QPushButton("След. дни");
    buttonsLayout1->addWidget(btnOpen);
    buttonsLayout1->addWidget(btnAdd);
    buttonsLayout1->addWidget(btnDelete);
    buttonsLayout1->addWidget(btnNext);

    QHBoxLayout *buttonsLayout2 = new QHBoxLayout();
    QPushButton *btnWeek = new QPushButton("№ недель");
    QPushButton *btnDiff = new QPushButton("Разница");
    QPushButton *btnBday = new QPushButton("Дней до ДР");
    buttonsLayout2->addWidget(btnWeek);
    buttonsLayout2->addWidget(btnDiff);
    buttonsLayout2->addWidget(btnBday);

    bottomLayout->addLayout(inputLayout);
    bottomLayout->addLayout(buttonsLayout1);
    bottomLayout->addLayout(buttonsLayout2);

    mainLayout->addLayout(bottomLayout);

    setCentralWidget(central);
    resize(850, 600);

    connect(btnOpen, &QPushButton::clicked, this, &MainWindow::onOpen);
    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::onAdd);
    connect(btnDelete, &QPushButton::clicked, this, &MainWindow::onDelete);
    connect(btnNext, &QPushButton::clicked, this, &MainWindow::onCalcNext);
    connect(btnWeek, &QPushButton::clicked, this, &MainWindow::onCalcWeek);
    connect(btnDiff, &QPushButton::clicked, this, &MainWindow::onCalcDiff);
    connect(btnBday, &QPushButton::clicked, this, &MainWindow::onCalcBday);
}

MainWindow::~MainWindow() {
    for(auto d : dates) delete d;
}

void MainWindow::onOpen() {
    filePath = QFileDialog::getOpenFileName(this, "Выбрать файл", "", "Text (*.txt)");
    if (filePath.isEmpty()) return;

    for(auto d : dates) delete d;
    dates.clear();

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString content = in.readAll();
        QString simplifiedContent = content.simplified();
        QStringList list = simplifiedContent.split(' ', Qt::SkipEmptyParts);

        for (const QString &s : list) {
            QStringList parts = s.split(".");
            if (parts.size() == 3) {
                try {
                    dates.append(new Date(parts[0].toInt(), parts[1].toInt(), parts[2].toInt()));
                } catch(...) { }
            }
        }
        file.close();
    }
    updateTableBase();
}

void MainWindow::updateTableBase() {
    table->setRowCount(dates.size());
    for (int i = 0; i < dates.size(); ++i) {
        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(dates[i]->toString())));
        for(int j = 1; j < 5; ++j) {
            table->setItem(i, j, new QTableWidgetItem(""));
        }
    }
}

void MainWindow::onAdd() {
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Файл не выбран");
        return;
    }
    QString raw = newDateInput->text();
    QStringList parts = raw.split(".");
    if (parts.size() != 3) return;

    QFile file(filePath);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << " " << raw;
        file.close();

        try {
            dates.append(new Date(parts[0].toInt(), parts[1].toInt(), parts[2].toInt()));
            updateTableBase();
            newDateInput->clear();
        } catch(...) {
            QMessageBox::warning(this, "Ошибка", "Некорректная дата");
        }
    }
}

void MainWindow::onDelete() {
    int currentRow = table->currentRow();
    if (currentRow < 0 || currentRow >= dates.size() || filePath.isEmpty()) {
        return;
    }

    delete dates.takeAt(currentRow);

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        QStringList strDates;
        for (Date *d : dates) {
            strDates << QString::fromStdString(d->toString());
        }
        out << strDates.join(" ");
        file.close();
    }
    updateTableBase();
}

void MainWindow::onCalcNext() {
    for (int i = 0; i < dates.size(); ++i) {
        Date next = dates[i]->nextDay();
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(next.toString())));
    }
}

void MainWindow::onCalcWeek() {
    for (int i = 0; i < dates.size(); ++i) {
        table->setItem(i, 2, new QTableWidgetItem(QString::number(dates[i]->weekNumber())));
    }
}

void MainWindow::onCalcDiff() {
    if (dates.size() < 2) return;
    for (int i = 0; i < (int)dates.size() - 1; ++i) {
        int diff = dates[i]->duration(*dates[i+1]);
        table->setItem(i, 4, new QTableWidgetItem(QString::number(diff)));
    }
}

void MainWindow::onCalcBday() {
    QStringList parts = bdayInput->text().split(".");
    if (parts.size() != 3) {
        QMessageBox::warning(this, "Ошибка", "Формат: ДД.ММ.ГГГГ");
        return;
    }

    try {
        Date userBday(parts[0].toInt(), parts[1].toInt(), parts[2].toInt());
        for (int i = 0; i < dates.size(); ++i) {
            int days = dates[i]->duration(userBday);
            table->setItem(i, 3, new QTableWidgetItem(QString::number(days)));
        }
    } catch(...) {
        QMessageBox::warning(this, "Ошибка", "Некорректная дата");
    }
}
