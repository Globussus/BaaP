#include "mainwindow.h"
#include "file_functions.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <stdexcept>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    display = new QTextEdit(this);
    display->setReadOnly(true);

    inputFio = new QLineEdit(this);
    inputFio->setPlaceholderText("ФИО для поиска/удаления");

    QPushButton *btnLoad = new QPushButton("Открыть", this);
    QPushButton *btnSave = new QPushButton("Сохранить", this);
    QPushButton *btnAdd = new QPushButton("Добавить", this);
    QPushButton *btnDel = new QPushButton("Удалить", this);
    QPushButton *btnSortAll = new QPushButton("Сорт. всех", this);
    QPushButton *btnSortGrp = new QPushButton("Сорт. в группе", this);
    QPushButton *btnSearch = new QPushButton("Найти", this);
    QPushButton *btnGood   = new QPushButton("Успевающие", this);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchLayout->addWidget(inputFio);
    searchLayout->addWidget(btnSearch);

    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(display);

    QHBoxLayout *buttonRow1 = new QHBoxLayout();
    buttonRow1->addWidget(btnLoad);
    buttonRow1->addWidget(btnSave);
    buttonRow1->addWidget(btnAdd);

    QHBoxLayout *buttonRow2 = new QHBoxLayout();
    buttonRow2->addWidget(btnSortAll);
    buttonRow2->addWidget(btnSortGrp);
    buttonRow2->addWidget(btnGood);
    buttonRow2->addWidget(btnDel);

    mainLayout->addLayout(buttonRow1);
    mainLayout->addLayout(buttonRow2);

    setCentralWidget(centralWidget);
    resize(700, 500);

    connect(btnLoad, &QPushButton::clicked, this, &MainWindow::handleLoad);
    connect(btnSave, &QPushButton::clicked, this, &MainWindow::handleSave);
    connect(btnSortAll, &QPushButton::clicked, this, &MainWindow::handleSortAll);
    connect(btnSortGrp, &QPushButton::clicked, this, &MainWindow::handleSortGroup);
    connect(btnSearch, &QPushButton::clicked, this, &MainWindow::handleSearch);
    connect(btnGood, &QPushButton::clicked, this, &MainWindow::showGoodStudents);
    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::handleAdd);
    connect(btnDel, &QPushButton::clicked, this, &MainWindow::handleDelete);
}

MainWindow::~MainWindow() {
    qDeleteAll(data);
}

void MainWindow::refreshDisplay(const QVector<Student *> &list) {
    display->clear();
    for (Student* student : list) {
        if (!student) continue;
        QStringList gradesList;
        for (int g : student->grades) gradesList << QString::number(g);

        QString info = QString("%1 | %2 | Оценки: %3 | Средний: %4")
                           .arg(student->groupNumber, -8)
                           .arg(student->fio, -20)
                           .arg(gradesList.join(" "), -10)
                           .arg(student->average, 0, 'f', 2);
        display->append(info);
    }
}

void MainWindow::handleAdd() {
    bool ok;
    QString name = QInputDialog::getText(this, "Ввод", "ФИО:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;

    QString grp = QInputDialog::getText(this, "Ввод", "Группа:", QLineEdit::Normal, "", &ok);
    if (!ok) return;

    QString gStr = QInputDialog::getText(this, "Ввод", "5 оценок (через пробел):", QLineEdit::Normal, "", &ok);
    if (!ok) return;

    QStringList parts = gStr.split(" ", Qt::SkipEmptyParts);
    QVector<int> grades;
    for (const QString &p : parts) grades.append(p.toInt());

    data.append(new Student("Специальность", grp, name, grades));
    refreshDisplay(data);
}

void MainWindow::handleDelete() {
    QString name = inputFio->text();
    for (int i = 0; i < data.size(); i++) {
        if (data[i]->fio == name) {
            delete data.takeAt(i);
            refreshDisplay(data);
            return;
        }
    }
}

void MainWindow::handleLoad() {
    QString path = QFileDialog::getOpenFileName(this, "Открыть", "./../../..", "Data (*.dat)");
    if (path.isEmpty()) return;

    try {
        QVector<Student*> loadedData = loadStudents(path);
        qDeleteAll(data);
        data = loadedData;
        refreshDisplay(data);
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Ошибка загрузки", e.what());
    } catch (...) {
        QMessageBox::critical(this, "Ошибка", "Произошла неизвестная ошибка при чтении файла.");
    }
}

void MainWindow::handleSave() {
    if (data.isEmpty()) {
        QMessageBox::warning(this, "Внимание", "Список пуст.");
        return;
    }

    QString path = QFileDialog::getSaveFileName(this, "Сохранить", "./../../..", "Data (*.dat)");
    if (path.isEmpty()) return;

    try {
        saveStudents(path, data);
        QMessageBox::information(this, "Успех", "Данные сохранены.");
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Ошибка сохранения", e.what());
    } catch (...) {
        QMessageBox::critical(this, "Ошибка", "Непредвиденный сбой при записи.");
    }
}

void MainWindow::handleSortAll() {
    sortByAverage(data);
    refreshDisplay(data);
}

void MainWindow::handleSortGroup() {
    sortByAverageInGroup(data);
    refreshDisplay(data);
}

void MainWindow::handleSearch() {
    QVector<Student*> found = findByFio(data, inputFio->text());
    refreshDisplay(found);
}

void MainWindow::showGoodStudents() {
    refreshDisplay(getSuccessfulStudents(data));
}
