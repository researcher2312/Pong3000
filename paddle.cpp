#include <QKeyEvent>
#include <QGraphicsScene>
#include <QFont>
#include "paddle.h"

Paddle::Paddle(int x, int y, Score* new_score, QGraphicsItem* parent):
    QGraphicsRectItem(parent)
{
    setRect(0, 0, 20, 300);
    setPos(x, y);
    score = new_score;
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

