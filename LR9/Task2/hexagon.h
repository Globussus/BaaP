#ifndef HEXAGON_H
#define HEXAGON_H

#include "polygon.h"

class Hexagon : public Polygon
{
    Q_OBJECT
public:
    explicit Hexagon(double radius, QObject *parent = nullptr);

    double radius() const { return m_radius; }
    void setRadius(double r);

private:
    double m_radius;

    void updatePoints();
};

#endif
