#include "mainwindow.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QVBoxLayout>

#include "bitset.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setupUi();
    bitset_ = std::make_unique<BitSet>(8);
    secondBitset_ = std::make_unique<BitSet>(8);
    updateBitsetDisplay();
}

void MainWindow::setupUi() {
    auto* centralWidget = new QWidget(this);
    auto* mainLayout = new QVBoxLayout(centralWidget);

    auto* inputGroup = new QGroupBox("Ввод битсета (строка из 0 и 1)", this);
    auto* inputLayout = new QVBoxLayout(inputGroup);

    auto* inputRow1 = new QHBoxLayout();
    inputRow1->addWidget(new QLabel("BitSet 1:", this));
    bitsetInput_ = new QLineEdit(this);
    bitsetInput_->setPlaceholderText("Введите биты, например: 10110100");
    inputRow1->addWidget(bitsetInput_);
    inputLayout->addLayout(inputRow1);

    auto* inputRow2 = new QHBoxLayout();
    inputRow2->addWidget(new QLabel("BitSet 2:", this));
    secondBitsetInput_ = new QLineEdit(this);
    secondBitsetInput_->setPlaceholderText("Второй битсет для операций &, |");
    inputRow2->addWidget(secondBitsetInput_);
    inputLayout->addLayout(inputRow2);

    auto* sizeRow = new QHBoxLayout();
    sizeRow->addWidget(new QLabel("Размер:", this));
    sizeSpinBox_ = new QSpinBox(this);
    sizeSpinBox_->setRange(1, 128);
    sizeSpinBox_->setValue(8);
    sizeRow->addWidget(sizeSpinBox_);

    auto* setSizeBtn = new QPushButton("Установить размер", this);
    connect(setSizeBtn, &QPushButton::clicked, this, &MainWindow::onSetBitsetSizeClicked);
    sizeRow->addWidget(setSizeBtn);
    sizeRow->addStretch();
    inputLayout->addLayout(sizeRow);

    mainLayout->addWidget(inputGroup);

    auto* controlGroup = new QGroupBox("Управление", this);
    auto* controlLayout = new QGridLayout(controlGroup);

    auto* btnAll = new QPushButton("all()", this);
    auto* btnAny = new QPushButton("any()", this);
    auto* btnNone = new QPushButton("none()", this);
    auto* btnCount = new QPushButton("count()", this);
    auto* btnSize = new QPushButton("size()", this);
    auto* btnTest = new QPushButton("test(pos)", this);

    connect(btnAll, &QPushButton::clicked, this, &MainWindow::onAllClicked);
    connect(btnAny, &QPushButton::clicked, this, &MainWindow::onAnyClicked);
    connect(btnNone, &QPushButton::clicked, this, &MainWindow::onNoneClicked);
    connect(btnCount, &QPushButton::clicked, this, &MainWindow::onCountClicked);
    connect(btnSize, &QPushButton::clicked, this, &MainWindow::onSizeClicked);
    connect(btnTest, &QPushButton::clicked, this, &MainWindow::onTestClicked);

    controlLayout->addWidget(btnAll, 0, 0);
    controlLayout->addWidget(btnAny, 0, 1);
    controlLayout->addWidget(btnNone, 0, 2);
    controlLayout->addWidget(btnCount, 0, 3);
    controlLayout->addWidget(btnSize, 0, 4);
    controlLayout->addWidget(btnTest, 0, 5);

    auto* btnSet = new QPushButton("set()", this);
    auto* btnReset = new QPushButton("reset()", this);
    auto* btnFlip = new QPushButton("flip()", this);
    auto* btnToggle = new QPushButton("toggle[pos]", this);

    connect(btnSet, &QPushButton::clicked, this, &MainWindow::onSetClicked);
    connect(btnReset, &QPushButton::clicked, this, &MainWindow::onResetClicked);
    connect(btnFlip, &QPushButton::clicked, this, &MainWindow::onFlipClicked);
    connect(btnToggle, &QPushButton::clicked, this, &MainWindow::onToggleBitClicked);

    controlLayout->addWidget(btnSet, 1, 0);
    controlLayout->addWidget(btnReset, 1, 1);
    controlLayout->addWidget(btnFlip, 1, 2);
    controlLayout->addWidget(btnToggle, 1, 3);

    auto* btnNot = new QPushButton("~ (NOT)", this);
    auto* btnAnd = new QPushButton("& (AND)", this);
    auto* btnOr = new QPushButton("| (OR)", this);
    auto* btnShiftL = new QPushButton("<< (left)", this);
    auto* btnShiftR = new QPushButton(">> (right)", this);

    connect(btnNot, &QPushButton::clicked, this, &MainWindow::onOperatorNotClicked);
    connect(btnAnd, &QPushButton::clicked, this, &MainWindow::onOperatorAndClicked);
    connect(btnOr, &QPushButton::clicked, this, &MainWindow::onOperatorOrClicked);
    connect(btnShiftL, &QPushButton::clicked, this, &MainWindow::onShiftLeftClicked);
    connect(btnShiftR, &QPushButton::clicked, this, &MainWindow::onShiftRightClicked);

    controlLayout->addWidget(btnNot, 2, 0);
    controlLayout->addWidget(btnAnd, 2, 1);
    controlLayout->addWidget(btnOr, 2, 2);
    controlLayout->addWidget(btnShiftL, 2, 3);
    controlLayout->addWidget(btnShiftR, 2, 4);

    auto* indexRow = new QHBoxLayout();
    indexRow->addWidget(new QLabel("Индекс/сдвиг:", this));
    indexSpinBox_ = new QSpinBox(this);
    indexSpinBox_->setRange(0, 128);
    indexSpinBox_->setValue(0);
    indexRow->addWidget(indexSpinBox_);
    indexRow->addStretch();
    controlLayout->addLayout(indexRow, 3, 0, 1, 6);

    mainLayout->addWidget(controlGroup);

    auto* resultGroup = new QGroupBox("Результат", this);
    auto* resultLayout = new QVBoxLayout(resultGroup);
    resultOutput_ = new QTextEdit(this);
    resultOutput_->setReadOnly(true);
    resultOutput_->setMaximumHeight(60);
    resultLayout->addWidget(resultOutput_);
    mainLayout->addWidget(resultGroup);

    auto* logGroup = new QGroupBox("История операций", this);
    auto* logLayout = new QVBoxLayout(logGroup);
    logOutput_ = new QTextEdit(this);
    logOutput_->setReadOnly(true);
    logLayout->addWidget(logOutput_);
    mainLayout->addWidget(logGroup);

    setCentralWidget(centralWidget);
    setWindowTitle("BitSet Tester");
    resize(800, 600);
}

void MainWindow::updateBitsetDisplay() {
    if (!bitset_) {
        return;
    }
    String str = bitset_->toString();
    bitsetInput_->setText(QString::fromUtf8(str.cStr()));
}

void MainWindow::logResult(const String& msg) {
    resultOutput_->setText(QString::fromUtf8(msg.cStr()));
    logOutput_->append(QString::fromUtf8(msg.cStr()));
}

void MainWindow::logResult(const QString& msg) {
    resultOutput_->setText(msg);
    logOutput_->append(msg);
}

bool MainWindow::parseBitsetFromString(BitSet& bs, const QString& str) {
    for (QChar ch : str) {
        if (ch != '0' && ch != '1') {
            return false;
        }
    }
    int len = str.length();
    int bitsetSize = static_cast<int>(bs.size());
    bs.reset();
    for (int i = 0; i < len && i < bitsetSize; ++i) {
        QChar ch = str[len - 1 - i];
        if (ch == '1') {
            bs.set(static_cast<BitSet::SizeType>(i));
        }
    }
    return true;
}

void MainWindow::onSetBitsetSizeClicked() {
    int newSize = sizeSpinBox_->value();
    bitset_ = std::make_unique<BitSet>(static_cast<BitSet::SizeType>(newSize));
    secondBitset_ = std::make_unique<BitSet>(static_cast<BitSet::SizeType>(newSize));
    indexSpinBox_->setMaximum(newSize - 1);
    updateBitsetDisplay();
    logResult(QString("Создан новый BitSet размером %1").arg(newSize));
}

void MainWindow::onAllClicked() {
    if (!parseBitsetFromString(*bitset_, bitsetInput_->text())) {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Строка должна содержать только символы '0' и '1'");
        return;
    }
    bool result = bitset_->all();
    logResult(QString("all() = %1").arg(result ? "true" : "false"));
}

void MainWindow::onAnyClicked() {
    if (!parseBitsetFromString(*bitset_, bitsetInput_->text())) {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Строка должна содержать только символы '0' и '1'");
        return;
    }
    bool result = bitset_->any();
    logResult(QString("any() = %1").arg(result ? "true" : "false"));
}

void MainWindow::onNoneClicked() {
    if (!parseBitsetFromString(*bitset_, bitsetInput_->text())) {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Строка должна содержать только символы '0' и '1'");
        return;
    }
    bool result = bitset_->none();
    logResult(QString("none() = %1").arg(result ? "true" : "false"));
}

void MainWindow::onCountClicked() {
    if (!parseBitsetFromString(*bitset_, bitsetInput_->text())) {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Строка должна содержать только символы '0' и '1'");
        return;
    }
    BitSet::SizeType result = bitset_->count();
    logResult(QString("count() = %1").arg(result));
}

void MainWindow::onSizeClicked() {
    BitSet::SizeType result = bitset_->size();
    logResult(QString("size() = %1").arg(result));
}

void MainWindow::onTestClicked() {
    if (!parseBitsetFromString(*bitset_, bitsetInput_->text())) {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Строка должна содержать только символы '0' и '1'");
        return;
    }
    BitSet::SizeType pos = static_cast<BitSet::SizeType>(indexSpinBox_->value());
    bool result = bitset_->test(pos);
    logResult(QString("test(%1) = %2").arg(pos).arg(result ? "true" : "false"));
}

void MainWindow::onSetClicked() {
    if (!parseBitsetFromString(*bitset_, bitsetInput_->text())) {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Строка должна содержать только символы '0' и '1'");
        return;
    }
    bitset_->set();
    logResult(QString("set() — все биты установлены в 1"));
    updateBitsetDisplay();
}

void MainWindow::onResetClicked() {
    if (!parseBitsetFromString(*bitset_, bitsetInput_->text())) {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Строка должна содержать только символы '0' и '1'");
        return;
    }
    bitset_->reset();
    logResult(QString("reset() — все биты сброшены в 0"));
    updateBitsetDisplay();
}

void MainWindow::onFlipClicked() {
    if (!parseBitsetFromString(*bitset_, bitsetInput_->text())) {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Строка должна содержать только символы '0' и '1'");
        return;
    }
    bitset_->flip();
    logResult(QString("flip() — все биты инвертированы"));
    updateBitsetDisplay();
}

void MainWindow::onToggleBitClicked() {
    if (!parseBitsetFromString(*bitset_, bitsetInput_->text())) {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Строка должна содержать только символы '0' и '1'");
        return;
    }
    BitSet::SizeType pos = static_cast<BitSet::SizeType>(indexSpinBox_->value());
    (*bitset_)[pos] = !(*bitset_)[pos];
    logResult(QString("operator[](%1) = %2 (переключено)")
                  .arg(pos)
                  .arg((*bitset_)[pos] ? "true" : "false"));
    updateBitsetDisplay();
}

void MainWindow::onToULongClicked() {
    if (!parseBitsetFromString(*bitset_, bitsetInput_->text())) {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Строка должна содержать только символы '0' и '1'");
        return;
    }
    unsigned long result = bitset_->toULong();
    logResult(QString("toULong() = %1").arg(result));
}

void MainWindow::onToULongLongClicked() {
    if (!parseBitsetFromString(*bitset_, bitsetInput_->text())) {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Строка должна содержать только символы '0' и '1'");
        return;
    }
    unsigned long long result = bitset_->toULongLong();
    logResult(QString("toULongLong() = %1").arg(result));
}

void MainWindow::onOperatorNotClicked() {
    if (!parseBitsetFromString(*bitset_, bitsetInput_->text())) {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Строка должна содержать только символы '0' и '1'");
        return;
    }
    BitSet result = ~(*bitset_);
    logResult(QString("~bitset = %1")
                  .arg(QString::fromUtf8(result.toString().cStr())));
}

void MainWindow::onOperatorAndClicked() {
    if (!parseBitsetFromString(*bitset_, bitsetInput_->text())) {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Строка должна содержать только символы '0' и '1'");
        return;
    }
    if (!parseBitsetFromString(*secondBitset_, secondBitsetInput_->text())) {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Второй битсет: строка должна содержать только символы '0' и '1'");
        return;
    }
    BitSet result = (*bitset_) & (*secondBitset_);
    logResult(QString("bitset & bitset2 = %1")
                  .arg(QString::fromUtf8(result.toString().cStr())));
}

void MainWindow::onOperatorOrClicked() {
    if (!parseBitsetFromString(*bitset_, bitsetInput_->text())) {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Строка должна содержать только символы '0' и '1'");
        return;
    }
    if (!parseBitsetFromString(*secondBitset_, secondBitsetInput_->text())) {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Второй битсет: строка должна содержать только символы '0' и '1'");
        return;
    }
    BitSet result = (*bitset_) | (*secondBitset_);
    logResult(QString("bitset | bitset2 = %1")
                  .arg(QString::fromUtf8(result.toString().cStr())));
}

void MainWindow::onShiftLeftClicked() {
    if (!parseBitsetFromString(*bitset_, bitsetInput_->text())) {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Строка должна содержать только символы '0' и '1'");
        return;
    }
    BitSet::SizeType shift = static_cast<BitSet::SizeType>(indexSpinBox_->value());
    BitSet result = (*bitset_) << shift;
    logResult(QString("bitset << %1 = %2")
                  .arg(shift)
                  .arg(QString::fromUtf8(result.toString().cStr())));
}

void MainWindow::onShiftRightClicked() {
    if (!parseBitsetFromString(*bitset_, bitsetInput_->text())) {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Строка должна содержать только символы '0' и '1'");
        return;
    }
    BitSet::SizeType shift = static_cast<BitSet::SizeType>(indexSpinBox_->value());
    BitSet result = (*bitset_) >> shift;
    logResult(QString("bitset >> %1 = %2")
                  .arg(shift)
                  .arg(QString::fromUtf8(result.toString().cStr())));
}