#include "rhombus.h"

Rhombus::Rhombus(double d1, double d2, QObject *parent)
    : Polygon(parent),
    m_d1(d1),
    m_d2(d2)
{
    updatePoints();
}

void Rhombus::setDiagonals(double d1, double d2)
{
    m_d1 = d1;
    m_d2 = d2;
    updatePoints();
    emit changed();
}

void Rhombus::updatePoints()
{
    double a = m_d1 / 2.0;
    double b = m_d2 / 2.0;

    m_points = {
        QPointF( 0, -b),
        QPointF( a,  0),
        QPointF( 0,  b),
        QPointF(-a,  0)
    };
}
