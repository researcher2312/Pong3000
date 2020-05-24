#include "game.h"


Game::Game(QWidget* parent)
{
    setSceneRect(0,0, 800, 600);
    score1 = new Score(10, 50);
    score2 = new Score(10, 120);
    player1 = new Paddle(50, height()/2-150, score1);
    player2 = new Paddle(730, height()/2-150, score2);
    player1->setFlag(QGraphicsItem::ItemIsFocusable);
    player1->setFocus();
    ball = new Ball();
    ball->setPos(width()/2, height()/2);
    addItem(ball);
    addItem(player1);
    addItem(player2);
    addItem(score1);
    addItem(score2);
}
