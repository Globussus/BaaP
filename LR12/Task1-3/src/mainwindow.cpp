#include "mainwindow.h"
#include "tools.h"
#include <chrono>
#include <stdexcept>
#include <QString>
#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    QVBoxLayout *firstTaskLayout = new QVBoxLayout();
    QVBoxLayout *secondTaskLayout = new QVBoxLayout();
    QVBoxLayout *thirdTaskLayout = new QVBoxLayout();

    firstTaskLabel = new QLabel("Задание 1", this);
    firstTaskLabel->setMinimumSize(500, 300);
    firstTaskLabel->setStyleSheet("border: 1px solid black;");
    secondTaskLabel = new QLabel("Задание 2", this);
    secondTaskLabel->setMinimumSize(500, 300);
    secondTaskLabel->setStyleSheet("border: 1px solid black;");
    thirdTaskLabel = new QLabel("Задание 3", this);
    thirdTaskLabel->setMinimumSize(500, 300);
    thirdTaskLabel->setStyleSheet("border: 1px solid black;");

    QPushButton *startFirstTask = new QPushButton("Запустить 1-е задание", this);
    QPushButton *startSecondTask = new QPushButton("Запустить 2-е задание", this);
    QPushButton *startThirdTask = new QPushButton("Запустить 3-е задание", this);

    mainLayout->addLayout(firstTaskLayout);
    mainLayout->addLayout(secondTaskLayout);
    mainLayout->addLayout(thirdTaskLayout);

    connect(startFirstTask, &QPushButton::clicked, this, &MainWindow::handleFirstTask);
    connect(startSecondTask, &QPushButton::clicked, this, &MainWindow::handleSecondTask);
    connect(startThirdTask, &QPushButton::clicked, this, &MainWindow::handleThirdTask);

    firstTaskLayout->addWidget(firstTaskLabel);
    firstTaskLayout->addWidget(startFirstTask);
    secondTaskLayout->addWidget(secondTaskLabel);
    secondTaskLayout->addWidget(startSecondTask);
    thirdTaskLayout->addWidget(thirdTaskLabel);
    thirdTaskLayout->addWidget(startThirdTask);
}

void MainWindow::handleFirstTask() {
    bool ok;
    try {
        bool okInt, okNumbers;
        int n = QInputDialog::getInt(this, "Ввод", "Введите целое число n", 5, 1, 15, 1, &okInt);
        if (!okInt) {
            throw std::runtime_error("Некорректно введенное число!");
        }
        QString input = QInputDialog::getText(this, "Ввод", "Введите n чисел", QLineEdit::Normal, "0", &okNumbers);
        if (!okNumbers) {
            throw std::runtime_error("Некорректный ввод!");
        }
        QStringList list = input.split(" ", Qt::SkipEmptyParts);
        QVector<int> numbers;
        for (const QString &str: list) {
            bool conversionOk;
            int number = str.trimmed().toInt(&conversionOk);
            if (!conversionOk) {
                throw std::runtime_error("Некорректно введенное число!");
            }
            numbers.append(number);
        }
        if (numbers.size() != n) {
            throw std::runtime_error("Количество чисел не равно n!");
        }
        std::string message;
        std::vector<int> numbersVector(numbers.begin(), numbers.end());
        std::vector<int> numbersCopy(n); 
        message.append("Исходный массив: " + printArray(numbersVector, n) + "\n");

        std::copy(numbersVector.begin(), numbersVector.end(), numbersCopy.begin());
        auto start = std::chrono::high_resolution_clock::now();
        heapSort(numbersCopy, n);
        auto end = std::chrono::high_resolution_clock::now();
        float heap_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        message.append("Исходный массив после сортировки кучей: " + printArray(numbersCopy, n) + "\n");
        message.append("Время исполнения сортировки кучей: " + std::to_string(heap_duration) + " мкс\n");

        std::copy(numbersVector.begin(), numbersVector.end(), numbersCopy.begin());
        start = std::chrono::high_resolution_clock::now();
        quickSort(numbersCopy, 0, n - 1);
        end = std::chrono::high_resolution_clock::now();
        float quickSort_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        message.append("Исходный массив после быстрой сортировки:: " + printArray(numbersCopy, n) + "\n");
        message.append("Время исполнения быстрой сортировки: " + std::to_string(quickSort_duration) + " мкс\n");

        std::copy(numbersVector.begin(), numbersVector.end(), numbersCopy.begin());
        start = std::chrono::high_resolution_clock::now();
        mergeSort(numbersCopy, 0, n - 1);
        end = std::chrono::high_resolution_clock::now();
        heap_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        message.append("Исходный массив после сортировки слиянием: " + printArray(numbersCopy, n) + "\n");
        message.append("Время исполнения сортировки слиянием: " + std::to_string(heap_duration) + " мкс\n");

        int search = QInputDialog::getInt(this, "Ввод", "Введите целое число n", 0, 0, numbersCopy.back(), 1, &okInt);
        if (!okInt) {
            throw std::runtime_error("Некорректно введенное число!");
        }
        int result = binarySearch(numbersCopy, search, n);
        if (result == -1) {
            message.append("Искомого элемента нет в массиве!\n");
        } else {
            message.append("Индекс искомого элемента = " + std::to_string(result) + "\n");
        }
        firstTaskLabel->setText(QString::fromStdString(message));
    } catch (std::runtime_error &error) {
        QMessageBox::critical(this, "Ошибка", error.what());
    }
}

void MainWindow::handleSecondTask() {
    try {
        bool okInt, okNumbers;
        int n = QInputDialog::getInt(this, "Ввод", "Введите целое число n", 5, 1, 15, 1, &okInt);
        if (!okInt) {
            throw std::runtime_error("Некорректно введенное число!");
        }
        QString input = QInputDialog::getText(this, "Ввод", "Введите n чисел", QLineEdit::Normal, "0", &okNumbers);
        if (!okNumbers) {
            throw std::runtime_error("Некорректный ввод!");
        }
        QStringList list = input.split(" ", Qt::SkipEmptyParts);
        QVector<int> numbers;
        for (const QString &str: list) {
            bool conversionOk;
            int number = str.trimmed().toInt(&conversionOk);
            if (!conversionOk) {
                throw std::runtime_error("Некорректно введенное число!");
            }
            numbers.append(number);
        }
        if (numbers.size() != n) {
            throw std::runtime_error("Количество чисел не равно n!");
        }
        std::string message;
        std::vector<int> numbersVector(numbers.begin(), numbers.end());
        interpolationSort(numbersVector, n, message);
        message.append(printArray(numbersVector, n));

        int search = QInputDialog::getInt(this, "Ввод", "Введите целое число n", 0, 0, numbersVector.back(), 1, &okInt);
        if (!okInt) {
            throw std::runtime_error("Некорректно введенное число!");
        }
        int result = interpolationSearch(numbersVector, n, search);
        if (result == -1) {
            message.append("Искомого элемента нет в массиве!\n");
        } else {
            message.append("Индекс искомого элемента = " + std::to_string(result) + "\n");
            message.append(std::to_string(result) + " ^ " + std::to_string(n) + " = " + std::to_string(binaryPow(result, n, 100000000LL)));
        }
        secondTaskLabel->setText(QString::fromStdString(message));
    } catch (std::runtime_error &error) {
        QMessageBox::critical(this, "Ошибка", error.what());
    }
}

void MainWindow::handleThirdTask() {
    try {
        bool okInt, okNumbers;
        int n = QInputDialog::getInt(this, "Ввод", "Введите целое число n", 5, 1, 15, 1, &okInt);
        if (!okInt) {
            throw std::runtime_error("Некорректно введенное число!");
        }
        QString input = QInputDialog::getText(this, "Ввод", "Введите n чисел", QLineEdit::Normal, "0", &okNumbers);
        if (!okNumbers) {
            throw std::runtime_error("Некорректный ввод!");
        }
        QStringList list = input.split(" ", Qt::SkipEmptyParts);
        QVector<int> numbers;
        for (const QString &str: list) {
            bool conversionOk;
            int number = str.trimmed().toInt(&conversionOk);
            if (!conversionOk) {
                throw std::runtime_error("Некорректно введенное число!");
            }
            numbers.append(number);
        }
        if (numbers.size() != n) {
            throw std::runtime_error("Количество чисел не равно n!");
        }
        std::string message;
        std::vector<int> numbersVector(numbers.begin(), numbers.end());
        message.append("Исходный массив: " + printArray(numbersVector, n));
        std::vector<int> medians = findMedians(numbersVector, n);
        message.append("Медианы массива: " + printArray(medians, medians.size()));
        thirdTaskLabel->setText(QString::fromStdString(message));
    } catch (std::runtime_error &error) {
        QMessageBox::critical(this, "Ошибка", error.what());
    }
}

MainWindow::~MainWindow() {}