#include <QPainter>
#include <QPen>
#include <cart.h>

Cart::Cart(int x, int y, int width, int height, int speed)
    : MovingRectangle(x, y, width, height, speed) {
    int wheelRadius = 30;
    QPen spokePen(Qt::gray, 2);

    firstWheel = new QGraphicsEllipseItem(10, height - 5, wheelRadius, wheelRadius, this);
    QRectF firstRect = firstWheel->rect();

    firstWheel->setTransformOriginPoint(firstRect.center());
    firstWheel->setBrush(Qt::black);

    QGraphicsLineItem* firstHorizontalSpoke = new QGraphicsLineItem(firstRect.left(), firstRect.center().y(), firstRect.right(), firstRect.center().y(), firstWheel);
    QGraphicsLineItem* firstVerticalSpoke = new QGraphicsLineItem(firstRect.center().x(), firstRect.top(), firstRect.center().x(), firstRect.bottom(), firstWheel);

    firstHorizontalSpoke->setPen(spokePen);
    firstVerticalSpoke->setPen(spokePen);

    secondWheel = new QGraphicsEllipseItem(width - 40, height - 5, wheelRadius, wheelRadius, this);
    QRectF secondRect = secondWheel->rect();
    secondWheel->setTransformOriginPoint(secondRect.center());
    secondWheel->setBrush(Qt::black);

    QGraphicsLineItem* secondHorizontalSpoke = new QGraphicsLineItem(secondRect.left(), secondRect.center().y(), secondRect.right(), secondRect.center().y(), secondWheel);
    QGraphicsLineItem* secondVerticalSpoke = new QGraphicsLineItem(secondRect.center().x(), secondRect.top(), secondRect.center().x(), secondRect.bottom(), secondWheel);

    secondHorizontalSpoke->setPen(spokePen);
    secondVerticalSpoke->setPen(spokePen);

}

void Cart::move(int sceneWidth) {
    MovingRectangle::move(sceneWidth);
    wheelAngle += speed * 2;
    firstWheel->setRotation(wheelAngle);
    secondWheel->setRotation(wheelAngle);
}

void Cart::jump(int sceneHeight) {
    MovingRectangle::jump(sceneHeight);
    wheelAngle += speed * 2;
    firstWheel->setRotation(wheelAngle);
    secondWheel->setRotation(wheelAngle);
}
