#ifndef BALL_H
#define BALL_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QTimer>

#include "paddle.h"

class Ball: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    QTimer* timer;
    int speed_x;
    int speed_y;
    bool detectWallCollision();
    bool detectPaddleColision();
    void initRandomSpeed();
    void initRandomCoords();
public:
    Ball();
    void initRandomStart();
public slots:
    void move();
signals:
    void ballOut();
};

#endif // BALL_H
