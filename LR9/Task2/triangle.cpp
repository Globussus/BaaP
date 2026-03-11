#include "triangle.h"

Triangle::Triangle(const QPointF &a, const QPointF &b, const QPointF &c, QObject *parent)
    : Polygon(parent)
{
    m_points = { a, b, c };

    m_center = QPointF(
        (a.x() + b.x() + c.x()) / 3.0,
        (a.y() + b.y() + c.y()) / 3.0
        );
}

void Triangle::setVertices(const QPointF &a, const QPointF &b, const QPointF &c)
{
    m_points = { a, b, c };

    m_center = QPointF(
        (a.x() + b.x() + c.x()) / 3.0,
        (a.y() + b.y() + c.y()) / 3.0
        );

    emit changed();
}
