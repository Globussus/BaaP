#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape
{
    Q_OBJECT
public:
    explicit Circle(double radius, QObject *parent = nullptr);

    double radius() const { return m_radius; }
    void setRadius(double r);

    double area() const override;
    double perimeter() const override;

    void draw(QPainter &p) const override;
    bool contains(const QPointF &pt) const override;
    QRectF boundingRect() const override;

private:
    double m_radius;
};

#endif
