#ifndef OCTAGON_H
#define OCTAGON_H

#include "polygon.h"

class Octagon : public Polygon
{
    Q_OBJECT
public:
    explicit Octagon(double radius, QObject *parent = nullptr);

    double radius() const { return m_radius; }
    void setRadius(double r);

private:
    double m_radius;

    void updatePoints();
};

#endif
