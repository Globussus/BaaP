#ifndef SHAPE_H
#define SHAPE_H

#include <QObject>
#include <QPointF>
#include <QPainter>
#include <QTimer>

class Shape : public QObject
{
    Q_OBJECT
public:
    explicit Shape(QObject *parent = nullptr);
    virtual ~Shape() = default;

    QPointF center() const { return m_center; }
    double rotation() const { return m_angle; }
    double scale() const { return m_scale; }

    void setCenter(const QPointF &c);
    void setRotation(double a);
    void setScale(double s);

    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void draw(QPainter &p) const = 0;
    virtual bool contains(const QPointF &pt) const = 0;
    virtual QRectF boundingRect() const = 0;

    virtual void moveBy(const QPointF &delta);
    virtual void rotateBy(double da);
    virtual void scaleBy(double k);

    void animateMove(const QPointF &target, int durationMs);
    void animateRotate(double angleDeg, int durationMs);
    void animateScale(double factor, int durationMs);

signals:
    void changed();

protected slots:
    void onAnimationStep();

protected:
    QPointF m_center;
    double  m_angle;
    double  m_scale;

    QTimer m_timer;
    enum class Mode { None, Move, Rotate, Scale } m_mode;

    QPointF m_startPos, m_endPos;
    double m_startAngle, m_endAngle;
    double m_startScale, m_endScale;

    int m_elapsed;
    int m_duration;
};

#endif
