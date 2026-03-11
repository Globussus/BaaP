#include "star.h"
#include <QtMath>

Star::Star(int points, double outerRadius, double innerRadius, QObject *parent)
    : Polygon(parent),
    m_pointsCount(points),
    m_rOuter(outerRadius),
    m_rInner(innerRadius)
{
    updatePoints();
}

void Star::setPoints(int n)
{
    m_pointsCount = n;
    updatePoints();
    emit changed();
}

void Star::setOuterRadius(double r)
{
    m_rOuter = r;
    updatePoints();
    emit changed();
}

void Star::setInnerRadius(double r)
{
    m_rInner = r;
    updatePoints();
    emit changed();
}

void Star::updatePoints()
{
    m_points.clear();

    if (m_pointsCount < 2)
        return;

    if (m_rOuter <= 0 || m_rInner <= 0 || m_rInner >= m_rOuter)
        return;

    m_points.reserve(m_pointsCount * 2);

    double step = M_PI / m_pointsCount;
    double angle = -M_PI_2;

    for (int i = 0; i < m_pointsCount * 2; ++i)
    {
        double r = (i % 2 == 0) ? m_rOuter : m_rInner;
        double x = r * qCos(angle);
        double y = r * qSin(angle);

        m_points.append(QPointF(x, y));
        angle += step;
    }
}

