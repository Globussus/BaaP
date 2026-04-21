#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <QByteArray>
#include <QMessageBox>

static constexpr int BUFFER_SIZE = 1024;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setupUi();
}

void MainWindow::setupUi() {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    functionSelector = new QComboBox();
    functionSelector->addItems({
        "memcpy", "memmove", "strcpy", "strncpy", "strcat", "strncat",
        "memcmp", "strcmp", "strcoll", "strncmp", "strxfrm", "strtok",
        "memset", "strerror", "strlen"
    });
    mainLayout->addWidget(new QLabel("Выберите функцию (Select function):"));
    mainLayout->addWidget(functionSelector);

    input1 = new QLineEdit();
    input1->setPlaceholderText("Строка 1 (s1 / dest / str) - основной буфер");
    mainLayout->addWidget(input1);

    input2 = new QLineEdit();
    input2->setPlaceholderText("Строка 2 (s2 / src / delimiters) - источник или разделитель");
    mainLayout->addWidget(input2);

    inputNumber = new QLineEdit();
    inputNumber->setPlaceholderText("Числовой параметр (n / errnum)");
    mainLayout->addWidget(inputNumber);

    executeButton = new QPushButton("Выполнить");
    connect(executeButton, &QPushButton::clicked, this, &MainWindow::executeFunction);
    mainLayout->addWidget(executeButton);

    outputLog = new QTextEdit();
    outputLog->setReadOnly(true);
    mainLayout->addWidget(outputLog);

    setCentralWidget(centralWidget);
    setWindowTitle("String Library Tester");
    resize(650, 450);
}

void MainWindow::logMessage(const QString& msg) {
    outputLog->append(msg);
}

static void safeCopyToBuffer(char* buffer, int bufferSize, const char* src) {
    int len = 0;
    while (src[len] != '\0' && len < bufferSize - 1) {
        buffer[len] = src[len];
        len++;
    }
    buffer[len] = '\0';
}

static int safeStringLength(const char* s, int maxLen) {
    int len = 0;
    while (len < maxLen && s[len] != '\0') {
        len++;
    }
    return len;
}

// Проверка: нужен ли числовой параметр для данной функции
static bool needsNumberParam(const QString& funcName) {
    return funcName == "memcpy" || funcName == "memmove" || funcName == "strncpy" ||
           funcName == "strncat" || funcName == "memcmp" || funcName == "strncmp" ||
           funcName == "strxfrm" || funcName == "memset" || funcName == "strerror";
}

// Проверка: является ли строка корректным целым числом
static bool isValidNumber(const QString& str, int& outValue) {
    if (str.isEmpty()) {
        return false;
    }
    bool ok;
    int value = str.toInt(&ok);
    if (!ok) {
        return false;
    }
    outValue = value;
    return true;
}

void MainWindow::executeFunction() {
    QString funcName = functionSelector->currentText();
    QByteArray arr1 = input1->text().toUtf8();
    QByteArray arr2 = input2->text().toUtf8();

    // Проверка числового параметра для функций, где он требуется
    int n = 0;
    if (needsNumberParam(funcName)) {
        QString numStr = inputNumber->text().trimmed();
        if (!isValidNumber(numStr, n)) {
            QMessageBox::warning(this, "Ошибка ввода",
                QString("Функция '%1' требует числовой параметр (n / errnum).\n"
                       "Пожалуйста, введите целое число в поле 'Числовой параметр'.").arg(funcName));
            return;
        }
    } else {
        // Для функций без числового параметра просто парсим, если пользователь что-то ввёл
        // (игнорируем, если пусто)
        QString numStr = inputNumber->text().trimmed();
        if (!numStr.isEmpty()) {
            isValidNumber(numStr, n); // n будет использовано или проигнорировано
        }
    }

    const char* s1 = arr1.constData();
    const char* s2 = arr2.constData();

    char buffer[BUFFER_SIZE];
    safeCopyToBuffer(buffer, BUFFER_SIZE, s1);

    logMessage(QString("\n--- Вызов: %1 ---").arg(funcName));

    if (funcName == "memcpy") {
        int safeN = (n < 0) ? 0 : (n > BUFFER_SIZE ? BUFFER_SIZE : n);
        String::memoryCopy(buffer, s2, safeN);
        if (safeN < BUFFER_SIZE) {
            buffer[safeN] = '\0';
        } else {
            buffer[BUFFER_SIZE - 1] = '\0';
        }
        logMessage(QString("Результат memcpy: '%1'").arg(buffer));
    } 
    else if (funcName == "memmove") {
        int safeN = (n < 0) ? 0 : (n > BUFFER_SIZE ? BUFFER_SIZE : n);
        String::memoryMove(buffer, s2, safeN);
        if (safeN < BUFFER_SIZE) {
            buffer[safeN] = '\0';
        } else {
            buffer[BUFFER_SIZE - 1] = '\0';
        }
        logMessage(QString("Результат memmove: '%1'").arg(buffer));
    } 
    else if (funcName == "strcpy") {
        safeCopyToBuffer(buffer, BUFFER_SIZE, s2);
        logMessage(QString("Результат strcpy: '%1'").arg(buffer));
    } 
    else if (funcName == "strncpy") {
        int safeN = (n < 0) ? 0 : (n > BUFFER_SIZE - 1 ? BUFFER_SIZE - 1 : n);
        String::stringCopyN(buffer, s2, safeN);
        buffer[BUFFER_SIZE - 1] = '\0';
        logMessage(QString("Результат strncpy: '%1'").arg(buffer));
    } 
    else if (funcName == "strcat") {
        int len1 = safeStringLength(buffer, BUFFER_SIZE);
        int len2 = safeStringLength(s2, BUFFER_SIZE);
        if (len1 + len2 >= BUFFER_SIZE) {
            logMessage("ОШИБКА: Результат слишком длинный для буфера!");
        } else {
            String::stringConcat(buffer, s2);
            logMessage(QString("Результат strcat: '%1'").arg(buffer));
        }
    } 
    else if (funcName == "strncat") {
        int len1 = safeStringLength(buffer, BUFFER_SIZE);
        int maxCopy = (n < 0) ? 0 : n;
        if (len1 + maxCopy >= BUFFER_SIZE) {
            logMessage("ОШИБКА: Результат слишком длинный для буфера!");
        } else {
            String::stringConcatN(buffer, s2, maxCopy);
            logMessage(QString("Результат strncat: '%1'").arg(buffer));
        }
    } 
    else if (funcName == "memcmp") {
        int safeN = (n < 0) ? 0 : n;
        int res = String::memoryCompare(s1, s2, safeN);
        logMessage(QString("Результат memcmp('%1', '%2', %3) = %4").arg(s1).arg(s2).arg(safeN).arg(res));
    } 
    else if (funcName == "strcmp") {
        int res = String::stringCompare(s1, s2);
        logMessage(QString("Результат strcmp('%1', '%2') = %3").arg(s1).arg(s2).arg(res));
    } 
    else if (funcName == "strcoll") {
        int res = String::stringCollate(s1, s2);
        logMessage(QString("Результат strcoll('%1', '%2') = %3").arg(s1).arg(s2).arg(res));
    } 
    else if (funcName == "strncmp") {
        int safeN = (n < 0) ? 0 : n;
        int res = String::stringCompareN(s1, s2, safeN);
        logMessage(QString("Результат strncmp('%1', '%2', %3) = %4").arg(s1).arg(s2).arg(safeN).arg(res));
    } 
    else if (funcName == "strxfrm") {
        int safeN = (n < 0) ? 0 : (n > BUFFER_SIZE - 1 ? BUFFER_SIZE - 1 : n);
        size_t len = String::transformString(buffer, s2, safeN);
        buffer[BUFFER_SIZE - 1] = '\0';
        logMessage(QString("Результат strxfrm: длина = %1, буфер = '%2'").arg(len).arg(buffer));
    } 
    else if (funcName == "strtok") {
    // Проверяем, что строка 1 не пуста
    if (arr1.isEmpty()) {
        logMessage("ОШИБКА: Строка 1 (buffer) не может быть пустой для strtok.");
        return;
    }
    
    // Проверяем, что разделители указаны
    if (arr2.isEmpty()) {
        logMessage("ОШИБКА: Строка 2 (delimiters) не может быть пустой.");
        return;
    }
    
    // Создаём копию буфера для токенизации (так как strtok модифицирует строку)
    char* tokenBuffer = new char[BUFFER_SIZE];
    safeCopyToBuffer(tokenBuffer, BUFFER_SIZE, s1);
    
    char* saveptr = nullptr;
    char* token = String::stringTokenize_r(tokenBuffer, s2, &saveptr);
    int count = 1;
    
    if (token == nullptr) {
        logMessage("Токены не найдены (строка состоит только из разделителей или пуста).");
    }
    
    while (token != nullptr) {
        // Проверяем, что токен не пустой (двойные разделители)
        if (token[0] != '\0') {
            logMessage(QString("Токен %1: '%2'").arg(count++).arg(token));
        } else {
            logMessage(QString("Пропущен пустой токен (двойной разделитель)"));
        }
        token = String::stringTokenize_r(nullptr, s2, &saveptr);
    }
    
    delete[] tokenBuffer;
    } else if (funcName == "memset") {
        int c = !arr2.isEmpty() ? arr2.at(0) : '*';
        int safeN = (n < 0) ? 0 : (n > BUFFER_SIZE - 1 ? BUFFER_SIZE - 1 : n);
        String::memorySet(buffer, c, safeN);
        buffer[safeN] = '\0';
        logMessage(QString("Результат memset('%1', %2): '%3'").arg(QChar(c)).arg(safeN).arg(buffer));
    } 
    else if (funcName == "strerror") {
        const char* err = String::errorString(n);
        logMessage(QString("Результат strerror(%1) = '%2'").arg(n).arg(err));
    } 
    else if (funcName == "strlen") {
        size_t len = String::stringLength(s1);
        logMessage(QString("Результат strlen('%1') = %2").arg(s1).arg(len));
    }
}