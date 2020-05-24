#include <QGraphicsScene>
#include <QList>
#include "Ball.h"
#include "Paddle.h"

Ball::Ball(int x, int y, int speed_x, int speed_y):
    speed_x(speed_x), speed_y(speed_y)
{
    setRect(x,y,50,50);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Ball::move()
{
    detectWallCollision();
    detectPaddleColision();
    setPos(x()+speed_x, y()+speed_y);

}

bool Ball::detectWallCollision()
{
    if(y() <= 0 || y() >= scene()->height()-rect().height()){
        speed_y = -speed_y;
        return true;
    }
    if(x() <= 0 || x() >= scene()->width()-rect().width()){
        speed_x = -speed_x;
        return true;
    }
    return false;
}

bool Ball::detectPaddleColision()
{
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (auto& tested: colliding_items){
        if (typeid (*tested) == typeid (Paddle)){
            speed_x = -speed_x;
            return true;
        }
    }
    return false;
}
