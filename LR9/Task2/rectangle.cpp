#include "rectangle.h"

Rectangle::Rectangle(double width, double height, QObject *parent)
    : Polygon(parent),
    m_width(width),
    m_height(height)
{
    updatePoints();
}

void Rectangle::setSize(double w, double h)
{
    m_width = w;
    m_height = h;
    updatePoints();
    emit changed();
}

void Rectangle::updatePoints()
{
    double w = m_width / 2.0;
    double h = m_height / 2.0;

    m_points = {
        QPointF(-w, -h),
        QPointF(+w, -h),
        QPointF(+w, +h),
        QPointF(-w, +h)
    };
}
