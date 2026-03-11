#include "mainwindow.h"
#include "triangle.h"
#include "rectangle.h"
#include "square.h"
#include "rhombus.h"
#include "circle.h"
#include "star.h"
#include "hexagon.h"
#include "octagon.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(1200, 800);

    QWidget *central = new QWidget(this);
    auto *layout = new QHBoxLayout(central);

    QWidget *sidePanel = createSidePanel();

    m_canvas = new Canvas(this);
    m_canvas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(sidePanel);
    layout->addWidget(m_canvas, 1);

    central->setLayout(layout);
    setCentralWidget(central);
}

QWidget* MainWindow::createSidePanel()
{
    QWidget *panel = new QWidget(this);
    auto *v = new QVBoxLayout(panel);

    auto addBtn = [&](const QString &text, auto slot) {
        QPushButton *b = new QPushButton(text, panel);
        connect(b, &QPushButton::clicked, this, slot);
        v->addWidget(b);
    };

    addBtn("Треугольник", &MainWindow::onAddTriangle);
    addBtn("Прямоугольник", &MainWindow::onAddRectangle);
    addBtn("Квадрат", &MainWindow::onAddSquare);
    addBtn("Ромб", &MainWindow::onAddRhombus);
    addBtn("Круг", &MainWindow::onAddCircle);
    addBtn("Пятиконечная звезда", &MainWindow::onAddStar5);
    addBtn("Шестиконечная звезда", &MainWindow::onAddStar6);
    addBtn("Восьмиконечная звезда", &MainWindow::onAddStar8);
    addBtn("Шестиугольник", &MainWindow::onAddHexagon);
    addBtn("Восьмиугольник",&MainWindow::onAddOctagon);

    v->addSpacing(20);

    addBtn("Удалить выбранную фигуру", &MainWindow::onDeleteSelected);
    addBtn("Переместить выбранную фигуру", &MainWindow::onAnimateMove);
    addBtn("Поворот выбранной фигуры", &MainWindow::onAnimateRotate);
    addBtn("Приведение к основному масштабу", &MainWindow::onAnimateScale);

    v->addStretch();

    panel->setFixedWidth(300);
    return panel;
}

void MainWindow::onAddTriangle()
{
    auto *t = new Triangle(QPointF(-40,-30), QPointF(40,-30), QPointF(0,40));
    t->setCenter(m_canvas->canvasCenter());
    m_canvas->addShape(t);
}

void MainWindow::onAddRectangle()
{
    auto *r = new Rectangle(120, 80);
    r->setCenter(m_canvas->canvasCenter());
    m_canvas->addShape(r);
}

void MainWindow::onAddSquare()
{
    auto *s = new Square(100);
    s->setCenter(m_canvas->canvasCenter());
    m_canvas->addShape(s);
}

void MainWindow::onAddRhombus()
{
    auto *rh = new Rhombus(120, 80);
    rh->setCenter(m_canvas->canvasCenter());
    m_canvas->addShape(rh);
}

void MainWindow::onAddCircle()
{
    auto *c = new Circle(50);
    c->setCenter(m_canvas->canvasCenter());
    m_canvas->addShape(c);
}

void MainWindow::onAddStar5()
{
    auto *s = new Star(5, 60, 25);
    s->setCenter(m_canvas->canvasCenter());
    m_canvas->addShape(s);
}

void MainWindow::onAddStar6()
{
    auto *s = new Star(6, 60, 30);
    s->setCenter(m_canvas->canvasCenter());
    m_canvas->addShape(s);
}

void MainWindow::onAddStar8()
{
    auto *s = new Star(8, 60, 35);
    s->setCenter(m_canvas->canvasCenter());
    m_canvas->addShape(s);
}

void MainWindow::onAddHexagon()
{
    auto *h = new Hexagon(60);
    h->setCenter(m_canvas->canvasCenter());
    m_canvas->addShape(h);
}

void MainWindow::onAddOctagon()
{
    auto *o = new Octagon(60);
    o->setCenter(m_canvas->canvasCenter());
    m_canvas->addShape(o);
}

void MainWindow::onDeleteSelected()
{
    if (auto s = m_canvas->selected()) m_canvas->removeShape(s);
}

void MainWindow::onAnimateMove()
{
    if (auto s = m_canvas->selected())
        s->animateMove(s->center() + QPointF(-40, -40), 500);
}

void MainWindow::onAnimateRotate()
{
    if (auto s = m_canvas->selected())
        s->animateRotate(s->rotation() + 90, 800);
}

void MainWindow::onAnimateScale()
{
    if (auto s = m_canvas->selected())
        s->animateScale(1.5, 800);
}
