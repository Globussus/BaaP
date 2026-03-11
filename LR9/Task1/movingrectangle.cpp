#include <QPainter>
#include <movingrectangle.h>

MovingRectangle::MovingRectangle(int x, int y, int width, int height, int speed, QGraphicsItem *parent)
    : QGraphicsRectItem(0, 0, width, height, parent), speed(speed) {
    setPos(x, y);
    setBrush(Qt::lightGray);
    setPen(QPen(Qt::black));

    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemSendsGeometryChanges);

}

void MovingRectangle::move(int sceneWidth) {
    if (pos().x() + rect().width() >= sceneWidth || pos().x() <= 0) {
        speed = -speed;
    }
    moveBy(speed, 0);
}

void MovingRectangle::jump(int sceneHeight) {
    if (pos().y() + rect().height() >= sceneHeight || pos().y() <= 0) {
        speed = -speed;
    }
    moveBy(0, speed);
}
