#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "polygon.h"

class Triangle : public Polygon
{
    Q_OBJECT
public:
    explicit Triangle(const QPointF &a, const QPointF &b, const QPointF &c, QObject *parent = nullptr);

    void setVertices(const QPointF &a, const QPointF &b, const QPointF &c);

    QPointF A() const { return m_points[0]; }
    QPointF B() const { return m_points[1]; }
    QPointF C() const { return m_points[2]; }
};

#endif // TRIANGLE_H
