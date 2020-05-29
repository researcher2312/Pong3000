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

void Paddle::moveAbsolute(int move){
    setPos(x(), move);
}

void Paddle::moveRelative(int move){
    if (move < 0)
    {
        if (y()>0)
            setPos(x(), y() + move);
    }
    else
    {
        if (y()+rect().height() < scene()->height())
            setPos(x(), y() + move);
    }
}
