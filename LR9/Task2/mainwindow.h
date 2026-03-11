#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include "canvas.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onAddTriangle();
    void onAddRectangle();
    void onAddSquare();
    void onAddRhombus();
    void onAddCircle();
    void onAddStar5();
    void onAddStar6();
    void onAddStar8();
    void onAddHexagon();
    void onAddOctagon();

    void onDeleteSelected();
    void onAnimateMove();
    void onAnimateRotate();
    void onAnimateScale();

private:
    Canvas *m_canvas;

    QWidget* createSidePanel();
};

#endif
