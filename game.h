#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QWidget>

#include "ball.h"
#include "paddle.h"
#include "score.h"

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    void keyPressEvent(QKeyEvent *event);
    Game(QWidget* parent=nullptr);
    QGraphicsScene* scene;
    Paddle* player1;
    Paddle* player2;
    Ball* ball;
    Score* score1;
    Score* score2;
public slots:
    void resetBall();
signals:
    void moveUp1();
    void moveUp2();
    void moveDown1();
    void moveDown2();
};

#endif // GAME_H