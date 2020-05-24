#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <QWidget>

#include "ball.h"
#include "paddle.h"
#include "score.h"

class Game: public QGraphicsScene
{
public:
    Game(QWidget* parent=nullptr);
    Paddle* player1;
    Paddle* player2;
    Ball* ball;
    Score* score1;
    Score* score2;
};

#endif // GAME_H
