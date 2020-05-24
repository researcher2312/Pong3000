#include <QKeyEvent>
#include <QGraphicsScene>
#include "Paddle.h"


Paddle::Paddle(int x, int y)
{
    setRect(x, y, 20, 300);
}
void Paddle::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up){
        if (y()>0)
            setPos(x(), y()-10);
    }
    else if (event->key() == Qt::Key_Down){
        if (y()+rect().height() < scene()->height())
            setPos(x(), y()+10);
    }
}
