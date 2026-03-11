#include "circle.h"
#include <QtMath>

Circle::Circle(double radius,
               QObject *parent)
    : Shape(parent),
    m_radius(radius)
{
}

void Circle::setRadius(double r)
{
    m_radius = r;
    emit changed();
}

double Circle::area() const
{
    double R = m_radius * m_scale;
    return M_PI * R * R;
}

double Circle::perimeter() const
{
    double R = m_radius * m_scale;
    return 2 * M_PI * R;
}

void Circle::draw(QPainter &p) const
{
    p.save();
    p.setRenderHint(QPainter::Antialiasing, true);

    double R = m_radius * m_scale;

    p.translate(m_center);
    p.rotate(m_angle);

    p.setBrush(Qt::cyan);
    p.setPen(Qt::black);
    p.drawEllipse(QPointF(0,0), R, R);

    p.restore();
}


bool Circle::contains(const QPointF &pt) const
{
    double R = m_radius * m_scale;
    return QLineF(pt, m_center).length() <= R;
}

QRectF Circle::boundingRect() const
{
    double R = m_radius * m_scale;
    return QRectF(m_center.x() - R,
                  m_center.y() - R,
                  2*R, 2*R);
}
