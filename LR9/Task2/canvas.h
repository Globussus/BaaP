#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QVector>
#include "shape.h"

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);

    void addShape(Shape *s);
    void removeShape(Shape *s);

    Shape* selected() const { return m_selected; }

    QPointF canvasCenter() const {
        return QPointF(width() / 2.0, height() / 2.0);
    }

protected:
    void paintEvent(QPaintEvent *ev) override;

    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void contextMenuEvent(QContextMenuEvent *ev) override;
    void resizeEvent(QResizeEvent *ev) override;

private slots:
    void onShapeChanged();

private:
    QVector<Shape*> m_shapes;
    Shape *m_selected;

    QRectF m_bounds;

    bool m_dragging;
    QPointF m_dragStartPos;
    QPointF m_shapeStartCenter;

    Shape* shapeAt(const QPointF &pt);
    void clampToBounds(Shape *s);
};

#endif
