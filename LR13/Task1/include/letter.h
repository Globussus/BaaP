#ifndef LETTER_H
#define LETTER_H

#include <QLabel>

class Letter : public QLabel {
private:
    QString letter;
    QString color;
    QString underlineColor;
    bool underlined;
    int underlineWidth;
    int fontSize;

public:
    explicit Letter(QString letter = " ", QWidget *parent = nullptr);

    void setLetter(QString letter);
    void setColor(QString color);
    void setUnderlineColor(QString color);
    void setUnderlined(bool underlined);
    void setFontSize(int size);
    void correct();
    void incorrect();
    void extra();
    void next();
    void reset();
    void refresh();

    QString text();
};

#endif