#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "polygon.h"

class Rhombus : public Polygon
{
    Q_OBJECT
public:
    explicit Rhombus(double d1, double d2, QObject *parent = nullptr);

    double diag1() const { return m_d1; }
    double diag2() const { return m_d2; }

    void setDiagonals(double d1, double d2);

private:
    double m_d1;
    double m_d2;

    void updatePoints();
};

#endif
