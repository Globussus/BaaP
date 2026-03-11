#include "shape.h"
#include <QtMath>

Shape::Shape(QObject *parent)
    : QObject(parent),
    m_center(0,0),
    m_angle(0),
    m_scale(1),
    m_mode(Mode::None),
    m_elapsed(0),
    m_duration(0)
{
    connect(&m_timer, &QTimer::timeout, this, &Shape::onAnimationStep);
}

void Shape::setCenter(const QPointF &c)
{
    m_center = c;
    emit changed();
}

void Shape::setRotation(double a)
{
    m_angle = a;
    emit changed();
}

void Shape::setScale(double s)
{
    m_scale = s;
    emit changed();
}

void Shape::moveBy(const QPointF &delta)
{
    m_center += delta;
    emit changed();
}

void Shape::rotateBy(double da)
{
    m_angle += da;
    emit changed();
}

void Shape::scaleBy(double k)
{
    m_scale *= k;
    emit changed();
}

void Shape::animateMove(const QPointF &target, int durationMs)
{
    m_mode = Mode::Move;
    m_startPos = m_center;
    m_endPos = target;
    m_elapsed = 0;
    m_duration = durationMs;
    m_timer.start(16);
}

void Shape::animateRotate(double angleDeg, int durationMs)
{
    m_mode = Mode::Rotate;
    m_startAngle = m_angle;
    m_endAngle = angleDeg;
    m_elapsed = 0;
    m_duration = durationMs;
    m_timer.start(16);
}

void Shape::animateScale(double factor, int durationMs)
{
    m_mode = Mode::Scale;
    m_startScale = m_scale;
    m_endScale = factor;
    m_elapsed = 0;
    m_duration = durationMs;
    m_timer.start(16);
}

void Shape::onAnimationStep()
{
    m_elapsed += 16;
    double t = qMin(1.0, double(m_elapsed) / m_duration);

    switch (m_mode)
    {
    case Mode::Move:
        m_center = m_startPos + (m_endPos - m_startPos) * t;
        break;

    case Mode::Rotate:
        m_angle = m_startAngle + (m_endAngle - m_startAngle) * t;
        break;

    case Mode::Scale:
        m_scale = m_startScale + (m_endScale - m_startScale) * t;
        break;

    default:
        break;
    }

    emit changed();

    if (t >= 1.0)
    {
        m_timer.stop();
        m_mode = Mode::None;
        emit changed();
    }
}
