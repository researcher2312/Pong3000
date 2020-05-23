#include <QTimer>
#include "Ball.h"

Ball::Ball()
{
    setRect(0,0,100,100);
    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Ball::move()
{
    setPos(x()+2, y()+2);
}
