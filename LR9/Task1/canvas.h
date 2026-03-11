#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <cart.h>

class Canvas: public QGraphicsView {
    Q_OBJECT
private:
    QGraphicsScene *scene;
public:
    Canvas(QWidget *parent = nullptr);

    void addCart();
    void moveSelected();
    void jumpSelected();
    void removeSelected();

};
#endif // CANVAS_H
