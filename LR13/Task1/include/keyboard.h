#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QBoxLayout>
#include <QMap>
#include <QWidget>

#include "key.h"
#include "layout.h"

class Keyboard : public QVBoxLayout {
private:
    QVector<Key *> keys;
    Layout layout;

public:
    Keyboard(Layout layout = English, QWidget *parent = nullptr);
    ~Keyboard();

    static const QMap<Layout, QVector<QVector<QString>>> kLayouts;

    void setLayout(Layout layout);
    void setActive(QString keyString);
    void refresh();
};

#endif