#ifndef KEY_H
#define KEY_H

#include <QChar>
#include <QLabel>

class Key : public QLabel {
private:
    QString key;
    static const QString kBaseStyle;

public:
    explicit Key(QString key = "", QWidget *parent = nullptr);

    void setLetter(QString letter);
    void setActive(bool active);
    void refresh();

    bool operator==(const Key &other) const;
    bool operator==(const QString &string) const;
    bool operator!=(const Key &other) const;
    bool operator!=(const QString &string) const;
};

#endif