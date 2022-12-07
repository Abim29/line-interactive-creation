#include "my_canvas.h"

my_canvas::my_canvas(QWidget *parent) : QLabel(parent)
{

}

void my_canvas::mousePressEvent(QMouseEvent *ev)
{
    this->x_coords.append(ev->position().x());
    this->y_coords.append(ev->position().y());
    emit Mouse_Pressed();
}

