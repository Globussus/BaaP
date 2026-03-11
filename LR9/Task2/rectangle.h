#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "polygon.h"

class Rectangle : public Polygon
{
    Q_OBJECT
public:
    explicit Rectangle(double width, double height, QObject *parent = nullptr);

    double width() const { return m_width; }
    double height() const { return m_height; }

    void setSize(double w, double h);

private:
    double m_width;
    double m_height;

    void updatePoints();
};

#endif
