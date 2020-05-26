#include <QGraphicsScene>
#include <QFont>
#include "paddle.h"

Paddle::Paddle(int x, int y, Score* new_score, QGraphicsItem* parent):
    QGraphicsRectItem(parent)
{
    setRect(0, 0, 10, 150);
    setPos(x, y);
    score = new_score;
}

void Paddle::moveUp(){
    if (y()>0)
        setPos(x(), y()-20);
}

void Paddle::moveDown(){
    if (y()+rect().height() < scene()->height())
        setPos(x(), y()+20);
}
