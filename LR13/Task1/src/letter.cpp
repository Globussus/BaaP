#include "letter.h"

#include <utility>

Letter::Letter(QString letter, QWidget *parent)
    : letter(std::move(letter)),
      color("slategrey"),
      underlineColor("slategrey"),
      underlineWidth(1),
      fontSize(0),
      underlined(false),
      QLabel(parent) {
    setMaximumSize(30, 30);
    setAlignment(Qt::AlignCenter);
    refresh();
}

void Letter::setLetter(QString letter) {
    this->letter = letter;
    refresh();
}

void Letter::setColor(QString color) {
    this->color = color;
    refresh();
}

void Letter::setUnderlineColor(QString color) {
    underlineColor = color;
    refresh();
}

void Letter::setUnderlined(bool underlined) {
    this->underlined = underlined;
    refresh();
}

void Letter::setFontSize(int size) {
    fontSize = size;
    refresh();
}

void Letter::correct() {
    color = "white";
    refresh();
}

void Letter::incorrect() {
    color = "lightcoral";
    refresh();
}

void Letter::extra() {
    color = "lightcoral";
    underlineColor = "lightcoral";
    underlineWidth = 1;
    underlined = true;
    refresh();
}

void Letter::next() {
    underlineColor = "cornflowerblue";
    underlineWidth = 3;
    underlined = true;
    refresh();
}

void Letter::reset() {
    letter = " ";
    color = "slategrey";
    underlineColor = "slategrey";
    underlineWidth = 1;
    fontSize = 20;
    underlined = false;
    refresh();
}

void Letter::refresh() {
    setStyleSheet("font-size: " + QString::number(fontSize) + "px;" +
                  "color: " + color + ";" +
                  (underlined
                       ? ("border-bottom: " + QString::number(underlineWidth) +
                          "px solid " + underlineColor + ";")
                       : ""));
    setText(letter);
}

QString Letter::text() {
    return letter;
}