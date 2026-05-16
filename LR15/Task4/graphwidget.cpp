#include "graphwidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <cmath>
#include <algorithm>

GraphWidget::GraphWidget(QWidget* parent)
    : QWidget(parent)
    , minX(0), maxX(1), minY(0), maxY(1)
    , lineColor(70, 130, 180) {
    setMinimumSize(300, 200);
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::white);
    setPalette(pal);
}

void GraphWidget::setData(const QVector<double>& xData, const QVector<double>& yData,
                          const QString& title, const QString& xLabel, const QString& yLabel,
                          const QColor& lineColor) {
    dataPoints.clear();
    for (int i = 0; i < xData.size() && i < yData.size(); ++i) {
        dataPoints.append(QPointF(xData[i], yData[i]));
    }
    this->title = title;
    this->xLabel = xLabel;
    this->yLabel = yLabel;
    this->lineColor = lineColor;
    calculateBounds();
    update();
}

void GraphWidget::clear() {
    dataPoints.clear();
    title.clear();
    xLabel.clear();
    yLabel.clear();
    update();
}

void GraphWidget::calculateBounds() {
    if (dataPoints.isEmpty()) {
        minX = 0; maxX = 1; minY = 0; maxY = 1;
        return;
    }

    minX = maxX = dataPoints[0].x();
    minY = maxY = dataPoints[0].y();

    for (const auto& point : dataPoints) {
        minX = std::min(minX, point.x());
        maxX = std::max(maxX, point.x());
        minY = std::min(minY, point.y());
        maxY = std::max(maxY, point.y());
    }

    double xPadding = (maxX - minX) * 0.1;
    double yPadding = (maxY - minY) * 0.1;

    if (xPadding < 1.0) xPadding = 1.0;
    if (yPadding < 0.1) yPadding = 0.1;

    minX -= xPadding;
    maxX += xPadding;
    minY -= yPadding;
    maxY += yPadding;

    if (minX < 0) minX = 0;
    if (minY < 0) minY = 0;
}

QPointF GraphWidget::mapToWidget(double x, double y, const QRect& rect) const {
    double px = rect.left() + (x - minX) / (maxX - minX) * rect.width();
    double py = rect.bottom() - (y - minY) / (maxY - minY) * rect.height();
    return QPointF(px, py);
}

void GraphWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect rect = this->rect().adjusted(60, 40, -20, -50);

    if (dataPoints.isEmpty()) {
        painter.setPen(Qt::gray);
        painter.drawText(rect, Qt::AlignCenter, "No data");
        return;
    }

    // Фон графика
    painter.fillRect(rect, QColor(245, 245, 250));
    painter.setPen(QPen(Qt::lightGray, 1));
    painter.drawRect(rect);

    // Сетка (5 горизонтальных линий)
    painter.setPen(QPen(QColor(220, 220, 230), 1, Qt::DashLine));
    for (int i = 0; i <= 4; ++i) {
        double y = minY + (maxY - minY) * i / 4.0;
        QPointF left = mapToWidget(minX, y, rect);
        QPointF right = mapToWidget(maxX, y, rect);
        painter.drawLine(QPointF(rect.left(), left.y()), QPointF(rect.right(), right.y()));

        // Подписи оси Y
        painter.setPen(Qt::black);
        QString label;
        if (maxY < 1.0) {
            label = QString::number(y, 'f', 3);
        } else if (maxY < 100) {
            label = QString::number(y, 'f', 1);
        } else {
            label = QString::number(static_cast<int>(y));
        }
        painter.drawText(QRectF(0, left.y() - 10, 55, 20), Qt::AlignRight | Qt::AlignVCenter, label);
        painter.setPen(QPen(QColor(220, 220, 230), 1, Qt::DashLine));
    }

    // Сетка (вертикальные линии)
    for (int i = 0; i < dataPoints.size(); ++i) {
        QPointF p = mapToWidget(dataPoints[i].x(), minY, rect);
        painter.drawLine(QPointF(p.x(), rect.top()), QPointF(p.x(), rect.bottom()));

        // Подписи оси X
        painter.setPen(Qt::black);
        QString label = QString::number(static_cast<int>(dataPoints[i].x()));
        painter.drawText(QRectF(p.x() - 20, rect.bottom() + 5, 40, 20), Qt::AlignCenter, label);
        painter.setPen(QPen(QColor(220, 220, 230), 1, Qt::DashLine));
    }

    // Линия графика
    painter.setPen(QPen(lineColor, 2));
    QVector<QPointF> widgetPoints;
    for (const auto& point : dataPoints) {
        widgetPoints.append(mapToWidget(point.x(), point.y(), rect));
    }

    for (int i = 0; i < widgetPoints.size() - 1; ++i) {
        painter.drawLine(widgetPoints[i], widgetPoints[i + 1]);
    }

    // Точки на графике
    painter.setPen(QPen(lineColor.darker(150), 1));
    painter.setBrush(lineColor);
    for (const auto& wp : widgetPoints) {
        painter.drawEllipse(wp, 4, 4);
    }

    // Подписи значений над точками
    painter.setPen(Qt::black);
    QFont font = painter.font();
    font.setPointSize(8);
    painter.setFont(font);
    for (int i = 0; i < widgetPoints.size(); ++i) {
        QString valueStr;
        if (dataPoints[i].y() < 1.0) {
            valueStr = QString::number(dataPoints[i].y(), 'f', 3);
        } else if (dataPoints[i].y() < 100) {
            valueStr = QString::number(dataPoints[i].y(), 'f', 1);
        } else {
            valueStr = QString::number(static_cast<int>(dataPoints[i].y()));
        }
        painter.drawText(QRectF(widgetPoints[i].x() - 25, widgetPoints[i].y() - 25, 50, 20),
                        Qt::AlignCenter, valueStr);
    }

    // Заголовок
    font.setPointSize(11);
    font.setBold(true);
    painter.setFont(font);
    painter.setPen(Qt::black);
    painter.drawText(QRect(0, 5, this->width(), 30), Qt::AlignCenter, title);

    // Подписи осей
    font.setPointSize(9);
    font.setBold(false);
    painter.setFont(font);
    painter.setPen(Qt::darkGray);
    painter.drawText(QRect(0, this->height() - 25, this->width(), 20), Qt::AlignCenter, xLabel);
    painter.save();
    painter.translate(15, this->height() / 2);
    painter.rotate(-90);
    painter.drawText(QRect(-50, -10, 100, 20), Qt::AlignCenter, yLabel);
    painter.restore();
}