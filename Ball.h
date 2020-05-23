#ifndef BALL_H
#define BALL_H

#include <QGraphicsRectItem>
#include <QObject>

class Ball: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Ball();
public slots:
    void move();
};

#endif // BALL_H
