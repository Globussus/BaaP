#include "hexagon.h"
#include <QtMath>

Hexagon::Hexagon(double radius, QObject *parent)
    : Polygon(parent),
    m_radius(radius)
{
    updatePoints();
}

void Hexagon::setRadius(double r)
{
    m_radius = r;
    updatePoints();
    emit changed();
}

void Hexagon::updatePoints()
{
    m_points.clear();
    m_points.reserve(6);

    double angle = -M_PI_2;
    double step = M_PI / 3;

    for (int i = 0; i < 6; i++)
    {
        double x = m_radius * qCos(angle);
        double y = m_radius * qSin(angle);
        m_points.append(QPointF(x, y));
        angle += step;
    }
}
