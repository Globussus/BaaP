#ifndef CART_H
#define CART_H

#include <QPainter>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <movingrectangle.h>

class Cart : public MovingRectangle {
private:
    QGraphicsEllipseItem *firstWheel;
    QGraphicsEllipseItem *secondWheel;
    double wheelAngle = 0;
public:
    Cart(int x, int y, int width, int height, int speed);
    void move(int sceneWidth) override;
    void jump(int sceneHeight) override;
};

#endif // CART_H
