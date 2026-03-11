#include "square.h"

Square::Square(double side,
               QObject *parent)
    : Polygon(parent),
    m_side(side)
{
    updatePoints();
}

void Square::setSide(double s)
{
    m_side = s;
    updatePoints();
    emit changed();
}

void Square::updatePoints()
{
    double h = m_side / 2.0;

    m_points = {
        QPointF(-h, -h),
        QPointF(+h, -h),
        QPointF(+h, +h),
        QPointF(-h, +h)
    };
}
