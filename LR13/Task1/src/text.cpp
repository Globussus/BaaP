#include "text.h"

#include <QKeyEvent>
#include <QRegularExpression>

#include "keyboard.h"

Text::Text(QWidget *parent)
    : QWidget(parent),
      layout(new QGridLayout()),
      keyboardLayout(English),
      offset(0) {
    setMaximumHeight(35 * kRowCount);
    setFocusPolicy(Qt::StrongFocus);
    grabKeyboard();
    setLayout(layout);
    layout->setSpacing(0);
    for (int i = 0; i < kRowCount; i++) {
        letters.push_back(QVector<Letter *>());
        for (int j = 0; j < kColumnCount; j++) {
            auto *letter = new Letter();
            letter->setFont(QFont("Noto Sans Mono"));
            layout->addWidget(letter, i, j);
            letters[i].push_back(letter);
        }
    }
    generateConverter();
    restart();
}

Text::~Text() {
    for (auto &row : letters) {
        for (Letter *letter : row) {
            delete letter;
        }
    }
}

QString Text::generate() {
    QMap<Layout, QString> alphabets{
        {English, "abcdefghijklmnopqrstuvwxyz"},
        {Russian, "абвгдежзийклмнопстуфхцчшщъыьэюя"},
        {German, "abcdefghijklmnopqrstuvwxyzäöü"},
        {French, "abcdefghijklmnpqrstuvwxyzù"},
        {Arabic, "ءؤئاابةتثجحخدرزسشصضطظعغفقكللمنهوىي"},
        {Chinese, "一中人十卜口土大女尸山廿弓心戈手日月木水火田竹重金難"},
        {Belarusian, "абвгдежзйклмнопрстуфхцчшыьэюяіў"},
        {Hebrew, "אבגדהוזחטיךכלםמןנסעףפץצקרשת"}};
    QString resultText;
    for (int i = 2; i <= 6; i++) {
        for (int j = 0; j < (kColumnCount - i) / 2; j += i + 1) {
            QString word;
            for (int k = 0; k < i * i; k++) {
                word += alphabets[keyboardLayout]
                                 [rand() % alphabets[keyboardLayout].size()];
            }
            resultText += word + " ";
        }
    }
    return resultText;
}

void Text::generateConverter() {
    converter.clear();
    for (int i = 0; i < Keyboard::kLayouts[English].size(); i++) {
        for (int j = 0; j < Keyboard::kLayouts[English][i].size(); j++) {
            converter[Keyboard::kLayouts[English][i][j].toLower()] =
                Keyboard::kLayouts[keyboardLayout][i][j].toLower();
        }
    }
}

void Text::keyPressEvent(QKeyEvent *event) {
    if (event->modifiers() == Qt::ControlModifier) {
        if (event->key() == Qt::Key_R) {
            restart();
        } else if (event->key() == Qt::Key_O) {
            emit openFile();
        }
    } else if (!event->text().isEmpty()) {
        if (text.isEmpty()) {
            emit startTyping();
        }
        if (event->text()[0].isPrint() && text.size() < hint.size()) {
            if (converter.contains(event->text().toLower())) {
                text += event->text()[0].isUpper() && event->text()[0].isLetter()
                            ? converter[event->text().toLower()].toUpper()
                            : converter[event->text().toLower()];
            } else {
                text += event->text();
            }
        } else if (event->text() == "\b") {
            text = text.left(text.size() - 1);
        }
        refresh();
    }
}

void Text::setHint(QString hint) {
    this->hint = hint;
    text = "";
    offset = 0;
    refresh();
    emit reset();
}

void Text::setText(QString text) {
    this->text = text;
}

void Text::setKeyboardLayout(Layout layout) {
    keyboardLayout = layout;
    generateConverter();
    restart();
}

int Text::getTypedWordsCount() {
    return hint.left(text.size()).count(QRegularExpression("[^\\s]+"));
}

void Text::refresh() {
    if (text.size() - offset > kColumnCount * (kRowCount / 2 + 1) &&
        text.size() < hint.size() - kColumnCount) {
        offset += kColumnCount;
    }
    int index = offset;
    for (auto &row : letters) {
        for (Letter *letter : row) {
            letter->reset();
            if (keyboardLayout == Chinese) {
                letter->setFontSize(15);
            }
            if (index < text.size() && index < hint.size()) {
                letter->setLetter(QString(hint[index]));
                if (text[index] == hint[index]) {
                    letter->correct();
                } else {
                    letter->incorrect();
                }
            } else if (index < hint.size()) {
                letter->setLetter(QString(hint[index]));
            }
            index++;
        }
    }
    emit setActive("");
    if (text.size() < hint.size()) {
        letters[(text.size() - offset) / kColumnCount]
               [(text.size() - offset) % kColumnCount]
                   ->next();
        emit setActive(letters[(text.size() - offset) / kColumnCount]
                              [(text.size() - offset) % kColumnCount]
                                  ->text());
    }
    if (text.size() == hint.size()) {
        emit stopTyping();
    }
}

void Text::restart() {
    hint = generate();
    text = "";
    offset = 0;
    refresh();
    emit reset();
}