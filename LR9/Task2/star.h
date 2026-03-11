#ifndef STAR_H
#define STAR_H

#include "polygon.h"

class Star : public Polygon
{
    Q_OBJECT
public:
    explicit Star(int points, double outerRadius, double innerRadius, QObject *parent = nullptr);

    int points() const { return m_pointsCount; }
    double outerRadius() const { return m_rOuter; }
    double innerRadius() const { return m_rInner; }

    void setPoints(int n);
    void setOuterRadius(double r);
    void setInnerRadius(double r);

private:
    int m_pointsCount;
    double m_rOuter;
    double m_rInner;

    void updatePoints();
};

#endif
