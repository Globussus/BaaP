#include "octagon.h"
#include <QtMath>

Octagon::Octagon(double radius, QObject *parent)
    : Polygon(parent),
    m_radius(radius)
{
    updatePoints();
}

void Octagon::setRadius(double r)
{
    m_radius = r;
    updatePoints();
    emit changed();
}

void Octagon::updatePoints()
{
    m_points.clear();
    m_points.reserve(8);

    double angle = -M_PI_2;
    double step = M_PI / 4.0;

    for (int i = 0; i < 8; i++)
    {
        double x = m_radius * qCos(angle);
        double y = m_radius * qSin(angle);
        m_points.append(QPointF(x, y));
        angle += step;
    }
}
