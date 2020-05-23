#include <QKeyEvent>
#include "Paddle.h"

void Paddle::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up)
        setPos(x(), y()-10);
    else if (event->key() == Qt::Key_Down)
        setPos(x(), y()+10);
}
