#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"
#include <QVector>

class Polygon : public Shape
{
    Q_OBJECT
public:
    explicit Polygon(QObject *parent = nullptr);

    const QVector<QPointF>& points() const { return m_points; }
    void setPoints(const QVector<QPointF> &pts);

    double area() const override;
    double perimeter() const override;

    void draw(QPainter &p) const override;
    bool contains(const QPointF &pt) const override;
    QRectF boundingRect() const override;

protected:
    QVector<QPointF> m_points;

    QPointF transformPoint(const QPointF &p) const;
    QVector<QPointF> transformedPoints() const;
};

#endif
