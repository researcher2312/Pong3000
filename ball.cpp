#include <QGraphicsScene>
#include <QDebug>
#include <QList>
#include <QRandomGenerator>
#include <QSound>
#include "ball.h"

int getRandomSign()
{
    return (2*QRandomGenerator::securelySeeded().bounded(0, 2))-1;
}
Ball::Ball()
{
    setRect(0,0,25,25);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(25);
}

void Ball::move()
{
    detectWallCollision();
    if (detectPaddleColision()){
        QSound::play(":/sounds/tennis.wav");
    }
    setPos(x()+speed_x, y()+speed_y);

}

bool Ball::detectWallCollision()
{
    if(y() <= 0 || y() >= scene()->height()-rect().height()){
        speed_y = -speed_y;
        return true;
    }
    if(x() <= 0 || x() >= scene()->width()-rect().width()){
        emit ballOut();
        return true;
    }
    return false;
}

bool Ball::detectPaddleColision()
{
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (auto& tested: colliding_items){
        if (typeid (*tested) == typeid (Paddle)){
            if ((speed_x > 0 && x() < tested->x()) or (speed_x < 0 && x() > tested->x())){
                speed_x = -speed_x;
                return true;
            }
        }
    }
    return false;
}

void Ball::initRandomSpeed()
{
    speed_x = getRandomSign()*QRandomGenerator::securelySeeded().bounded(5, 7);
    speed_y = getRandomSign()*QRandomGenerator::securelySeeded().bounded(5, 7);
}

void Ball::initRandomCoords()
{
    int rand = QRandomGenerator::system()->bounded(55, scene()->height()-55);
    setPos(scene()->width()/2, rand);
}

void Ball::initRandomStart()
{
    initRandomSpeed();
    initRandomCoords();
}
