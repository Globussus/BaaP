#include <cart.h>
#include <canvas.h>
#include <QGraphicsItem>

Canvas::Canvas(QWidget *parent) : QGraphicsView(parent) {
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 600);

    setScene(scene);
    setFixedSize(800, 600);

    setRenderHint(QPainter::Antialiasing);
    setBackgroundBrush(Qt::white);
}


void Canvas::addCart() {
    Cart *cart = new Cart(50, 50, 200, 80, 5);
    scene->addItem(cart);
}

void Canvas::moveSelected() {
    for (QGraphicsItem *item : scene->selectedItems()) {
        Cart *cart = dynamic_cast<Cart*>(item);
        if (cart) {
            cart->move(scene->width());
        }
    }
}

void Canvas::jumpSelected() {
    for (QGraphicsItem *item : scene->selectedItems()) {
        Cart *cart = dynamic_cast<Cart*>(item);
        if (cart) {
            cart->jump(scene->height());
        }
    }
}

void Canvas::removeSelected() {
    QList<QGraphicsItem *> items = scene->selectedItems();
    scene->clearSelection();
    for (QGraphicsItem *item : items) {
        scene->removeItem(item);
        delete item;
    }
}
