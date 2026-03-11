#ifndef SQUARE_H
#define SQUARE_H

#include "polygon.h"

class Square : public Polygon
{
    Q_OBJECT
public:
    explicit Square(double side, QObject *parent = nullptr);

    double side() const { return m_side; }
    void setSide(double s);

private:
    double m_side;

    void updatePoints();
};

#endif
