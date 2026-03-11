#include "polygon.h"
#include <QtMath>

Polygon::Polygon(QObject *parent)
    : Shape(parent)
{
}

void Polygon::setPoints(const QVector<QPointF> &pts)
{
    m_points = pts;
    emit changed();
}

QPointF Polygon::transformPoint(const QPointF &p) const
{
    double rad = qDegreesToRadians(m_angle);
    double cos = qCos(rad);
    double sin = qSin(rad);

    QPointF s = p * m_scale;
    QPointF r(s.x() * cos - s.y() * sin,
              s.x() * sin + s.y() * cos);

    return m_center + r;
}

QVector<QPointF> Polygon::transformedPoints() const
{
    QVector<QPointF> out;
    out.reserve(m_points.size());
    for (const QPointF &p : m_points)
        out.append(transformPoint(p));
    return out;
}

double Polygon::area() const
{
    auto pts = transformedPoints();
    double A = 0;

    for (int i = 0; i < pts.size(); i++)
    {
        const QPointF &p1 = pts[i];
        const QPointF &p2 = pts[(i + 1) % pts.size()];
        A += p1.x() * p2.y() - p2.x() * p1.y();
    }
    return qAbs(A) * 0.5;
}

double Polygon::perimeter() const
{
    auto pts = transformedPoints();
    double P = 0;

    for (int i = 0; i < pts.size(); i++)
        P += QLineF(pts[i], pts[(i + 1) % pts.size()]).length();

    return P;
}

void Polygon::draw(QPainter &p) const
{
    auto pts = transformedPoints();
    if (pts.size() < 2) return;

    p.save();
    p.setRenderHint(QPainter::Antialiasing, true);

    QPolygonF poly(pts);

    p.setBrush(Qt::gray);
    p.setPen(Qt::black);
    p.drawPolygon(poly);

    p.restore();
}


bool Polygon::contains(const QPointF &pt) const
{
    QPolygonF poly(transformedPoints());
    return poly.containsPoint(pt, Qt::OddEvenFill);
}

QRectF Polygon::boundingRect() const
{
    auto pts = transformedPoints();
    if (pts.isEmpty()) return QRectF();

    qreal minX = pts[0].x(), maxX = pts[0].x();
    qreal minY = pts[0].y(), maxY = pts[0].y();

    for (const QPointF &p : pts)
    {
        minX = qMin(minX, p.x());
        maxX = qMax(maxX, p.x());
        minY = qMin(minY, p.y());
        maxY = qMax(maxY, p.y());
    }

    return QRectF(QPointF(minX, minY), QPointF(maxX, maxY));
}
