#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <QObject>
#include <QWidget>

#include "ball.h"
#include "paddle.h"
#include "score.h"

class Game: public QGraphicsScene
{
    Q_OBJECT
public:
    Game(QWidget* parent=nullptr);
    Paddle* player1;
    Paddle* player2;
    Ball* ball;
    Score* score1;
    Score* score2;
public slots:
    void resetBall();
};

#endif // GAME_H
