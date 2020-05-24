#ifndef BALL_H
#define BALL_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QTimer>

class Ball: public QObject, public QGraphicsRectItem{
    Q_OBJECT
private:
    QTimer* timer;
    int speed_x;
    int speed_y;
    bool detectWallCollision();
    bool detectPaddleColision();
public:
    Ball(int x=0, int y=0, int speed_x=5, int speed_y=5);
public slots:
    void move();
};

#endif // BALL_H
