#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QVector>
#include <QString>
#include <QPointF>

class GraphWidget : public QWidget {
    Q_OBJECT

public:
    explicit GraphWidget(QWidget* parent = nullptr);

    void setData(const QVector<double>& xData, const QVector<double>& yData,
                 const QString& title, const QString& xLabel, const QString& yLabel,
                 const QColor& lineColor = QColor(70, 130, 180));

    void clear();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QVector<QPointF> dataPoints;
    QString title;
    QString xLabel;
    QString yLabel;
    QColor lineColor;
    double minX, maxX, minY, maxY;

    void calculateBounds();
    QPointF mapToWidget(double x, double y, const QRect& rect) const;
};

#endif // GRAPHWIDGET_H