#ifndef MY_CANVAS_H
#define MY_CANVAS_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>

class my_canvas : public QLabel
{
       Q_OBJECT
public:
    explicit my_canvas(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *ev);

    int x, y;
    QVector<int> x_coords, y_coords;

signals:
    void Mouse_Pressed();
public slots:
};

#endif // MY_CANVAS_H
