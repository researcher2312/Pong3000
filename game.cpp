#include "game.h"


Game::Game(QWidget* parent):
    QGraphicsScene((parent))
{
    setSceneRect(0,0, 800, 600);
    score1 = new Score(50, 10);
    score2 = new Score(420, 10);
    player1 = new Paddle(50, height()/2-150, score1);
    player2 = new Paddle(730, height()/2-150, score2);
    player1->setFlag(QGraphicsItem::ItemIsFocusable);
    player1->setFocus();
    ball = new Ball();
    addItem(ball);
    addItem(player1);
    addItem(player2);
    addItem(score1);
    addItem(score2);
    ball->initRandomStart();
    connect(ball, SIGNAL(ballOut()), this, SLOT(resetBall()));
}

void Game::resetBall()
{
    if (ball->x() > width()/2){
        score1->increase();
    }
    else{
        score2->increase();
    }
    ball->initRandomStart();
}
