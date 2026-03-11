#include "mainwindow.h"
#include "canvas.h"
#include "triangle.h"
#include "rectangle.h"
#include "square.h"
#include "rhombus.h"
#include "circle.h"
#include "star.h"
#include "hexagon.h"
#include "octagon.h"

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QSizePolicy>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QMenu>


Canvas::Canvas(QWidget *parent)
    : QWidget(parent),
    m_selected(nullptr),
    m_dragging(false)
{
    setMouseTracking(true);
    m_bounds = QRectF(0, 0, width(), height());
}

void Canvas::resizeEvent(QResizeEvent *ev)
{
    QWidget::resizeEvent(ev);
    m_bounds = QRectF(0, 0, width(), height());
}

void Canvas::addShape(Shape *s)
{
    m_shapes.append(s);

    connect(s, &Shape::changed, this, &Canvas::onShapeChanged);

    update();
}

void Canvas::removeShape(Shape *s)
{
    m_shapes.removeOne(s);
    if (m_selected == s)
        m_selected = nullptr;

    delete s;
    update();
}

void Canvas::onShapeChanged()
{
    Shape *s = qobject_cast<Shape*>(sender());
    if (s)
        clampToBounds(s);

    update();
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.fillRect(rect(), Qt::white);

    p.setPen(QPen(Qt::gray, 2));
    p.drawRect(m_bounds);

    for (Shape *s : m_shapes)
        s->draw(p);

    if (m_selected)
    {
        p.setPen(QPen(Qt::red, 2, Qt::DashLine));
        p.drawRect(m_selected->boundingRect());
    }
}

Shape* Canvas::shapeAt(const QPointF &pt)
{
    for (int i = m_shapes.size() - 1; i >= 0; i--)
        if (m_shapes[i]->contains(pt))
            return m_shapes[i];
    return nullptr;
}

void Canvas::mousePressEvent(QMouseEvent *ev)
{
    QPointF pos = ev->pos();
    m_selected = shapeAt(pos);

    if (m_selected && ev->button() == Qt::LeftButton)
    {
        m_dragging = true;
        m_dragStartPos = pos;
        m_shapeStartCenter = m_selected->center();
    }

    update();
}

void Canvas::mouseMoveEvent(QMouseEvent *ev)
{
    if (m_dragging && m_selected)
    {
        QPointF delta = ev->pos() - m_dragStartPos;
        m_selected->setCenter(m_shapeStartCenter + delta);
        clampToBounds(m_selected);
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *)
{
    m_dragging = false;
}

void Canvas::contextMenuEvent(QContextMenuEvent *ev)
{
    Shape *s = shapeAt(ev->pos());
    if (!s) return;

    m_selected = s;

    QMenu menu(this);

    QAction *actMove      = menu.addAction("Сдвинуть (-10, -10)");
    QAction *actRotate    = menu.addAction("Повернуть на 15°");
    QAction *actScaleUp   = menu.addAction("Увеличить (x1.2)");
    QAction *actScaleDown = menu.addAction("Уменьшить (x0.8)");

    menu.addSeparator();

    Circle   *c  = dynamic_cast<Circle*>(s);
    Star     *st = dynamic_cast<Star*>(s);
    Rectangle*r  = dynamic_cast<Rectangle*>(s);
    Square   *sq = dynamic_cast<Square*>(s);
    Rhombus  *rh = dynamic_cast<Rhombus*>(s);
    Hexagon  *hx = dynamic_cast<Hexagon*>(s);
    Octagon  *oc = dynamic_cast<Octagon*>(s);

    QAction *actCircleRPlus = nullptr;
    QAction *actCircleRMinus = nullptr;

    QAction *actStarOuterPlus = nullptr;
    QAction *actStarOuterMinus = nullptr;
    QAction *actStarInnerPlus = nullptr;
    QAction *actStarInnerMinus = nullptr;

    QAction *actRectWPlus = nullptr;
    QAction *actRectWMinus = nullptr;
    QAction *actRectHPlus = nullptr;
    QAction *actRectHMinus = nullptr;

    QAction *actSquarePlus = nullptr;
    QAction *actSquareMinus = nullptr;

    QAction *actRhD1Plus = nullptr;
    QAction *actRhD1Minus = nullptr;
    QAction *actRhD2Plus = nullptr;
    QAction *actRhD2Minus = nullptr;

    QAction *actPolyRPlus = nullptr;
    QAction *actPolyRMinus = nullptr;

    if (c)
    {
        menu.addSection("Круг");
        actCircleRPlus  = menu.addAction("Радиус +10");
        actCircleRMinus = menu.addAction("Радиус -10");
    }

    if (st)
    {
        menu.addSection("Звезда");
        actStarOuterPlus  = menu.addAction("Внешний радиус +10");
        actStarOuterMinus = menu.addAction("Внешний радиус -10");
        actStarInnerPlus  = menu.addAction("Внутренний радиус +5");
        actStarInnerMinus = menu.addAction("Внутренний радиус -5");
    }

    if (r)
    {
        menu.addSection("Прямоугольник");
        actRectWPlus  = menu.addAction("Ширина +10");
        actRectWMinus = menu.addAction("Ширина -10");
        actRectHPlus  = menu.addAction("Высота +10");
        actRectHMinus = menu.addAction("Высота -10");
    }

    if (sq)
    {
        menu.addSection("Квадрат");
        actSquarePlus  = menu.addAction("Сторона +10");
        actSquareMinus = menu.addAction("Сторона -10");
    }

    if (rh)
    {
        menu.addSection("Ромб");
        actRhD1Plus  = menu.addAction("Диагональ 1 +10");
        actRhD1Minus = menu.addAction("Диагональ 1 -10");
        actRhD2Plus  = menu.addAction("Диагональ 2 +10");
        actRhD2Minus = menu.addAction("Диагональ 2 -10");
    }

    if (hx || oc)
    {
        menu.addSection("Правильный многоугольник");
        actPolyRPlus  = menu.addAction("Радиус +10");
        actPolyRMinus = menu.addAction("Радиус -10");
    }

    menu.addSeparator();

    QAction *actInfo = menu.addAction("Информация");
    QAction *actDelete = menu.addAction("Удалить");

    QAction *chosen = menu.exec(ev->globalPos());
    if (!chosen) return;

    if (chosen == actMove)
        s->moveBy(QPointF(-10, -10));

    else if (chosen == actRotate)
        s->rotateBy(15);

    else if (chosen == actScaleUp)
        s->scaleBy(1.2);

    else if (chosen == actScaleDown)
        s->scaleBy(0.8);

    else if (chosen == actInfo)
    {
        QString text;
        text += "Площадь: " + QString::number(s->area()) + "\n";
        text += "Периметр: " + QString::number(s->perimeter()) + "\n";
        text += "Центр масс: (" + QString::number(s->center().x()) + ", " + QString::number(s->center().y()) + ")";

        QMessageBox::information(this, "Информация", text);
        return;
    }

    else if (chosen == actDelete)
    {
        removeShape(s);
        return;
    }

    else if (c && chosen == actCircleRPlus)
        c->setRadius(c->radius() + 10);

    else if (c && chosen == actCircleRMinus)
        c->setRadius(qMax(5.0, c->radius() - 10));


    else if (st && chosen == actStarOuterPlus)
        st->setOuterRadius(st->outerRadius() + 10);

    else if (st && chosen == actStarOuterMinus)
        st->setOuterRadius(qMax(5.0, st->outerRadius() - 10));

    else if (st && chosen == actStarInnerPlus)
        st->setInnerRadius(st->innerRadius() + 5);

    else if (st && chosen == actStarInnerMinus)
        st->setInnerRadius(qMax(2.0, st->innerRadius() - 5));


    else if (r && chosen == actRectWPlus)
        r->setSize(r->width() + 10, r->height());

    else if (r && chosen == actRectWMinus)
        r->setSize(qMax(10.0, r->width() - 10), r->height());

    else if (r && chosen == actRectHPlus)
        r->setSize(r->width(), r->height() + 10);

    else if (r && chosen == actRectHMinus)
        r->setSize(r->width(), qMax(10.0, r->height() - 10));


    else if (sq && chosen == actSquarePlus)
        sq->setSide(sq->side() + 10);

    else if (sq && chosen == actSquareMinus)
        sq->setSide(qMax(10.0, sq->side() - 10));


    else if (rh && chosen == actRhD1Plus)
        rh->setDiagonals(rh->diag1() + 10, rh->diag2());

    else if (rh && chosen == actRhD1Minus)
        rh->setDiagonals(qMax(10.0, rh->diag1() - 10), rh->diag2());

    else if (rh && chosen == actRhD2Plus)
        rh->setDiagonals(rh->diag1(), rh->diag2() + 10);

    else if (rh && chosen == actRhD2Minus)
        rh->setDiagonals(rh->diag1(), qMax(10.0, rh->diag2() - 10));


    else if (hx && chosen == actPolyRPlus)
        hx->setRadius(hx->radius() + 10);

    else if (hx && chosen == actPolyRMinus)
        hx->setRadius(qMax(10.0, hx->radius() - 10));


    else if (oc && chosen == actPolyRPlus)
        oc->setRadius(oc->radius() + 10);

    else if (oc && chosen == actPolyRMinus)
        oc->setRadius(qMax(10.0, oc->radius() - 10));

    clampToBounds(s);
    update();
}


void Canvas::clampToBounds(Shape *s)
{
    QRectF br = s->boundingRect();

    double dx = 0, dy = 0;

    if (br.left() < m_bounds.left())
        dx = m_bounds.left() - br.left();
    if (br.right() > m_bounds.right())
        dx = m_bounds.right() - br.right();

    if (br.top() < m_bounds.top())
        dy = m_bounds.top() - br.top();
    if (br.bottom() > m_bounds.bottom())
        dy = m_bounds.bottom() - br.bottom();

    if (dx != 0 || dy != 0)
        s->moveBy(QPointF(dx, dy));
}
