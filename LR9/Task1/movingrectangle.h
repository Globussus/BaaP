#ifndef MOVINGRECTANGLE_H
#define MOVINGRECTANGLE_H

#include <QPainter>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>

class MovingRectangle: public QObject, public QGraphicsRectItem{
protected:
    float speed;
public:
    MovingRectangle(int x, int y, int width, int height, int speed, QGraphicsItem *parent = nullptr);

    virtual void move(int sceneWidth);
    virtual void jump(int sceneHeight);
};
#endif
