#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>
#include "game.h"


constexpr int POINTS_ENDING_ROUND= 2;

Game::Game(bool isPlayedWithComputer, int difficulty_level, QWidget* parent)
    :QGraphicsView(parent), isPlayedWithComputer(isPlayedWithComputer), difficulty_level(difficulty_level)
{
    scene = new QGraphicsScene();
    setScene(scene);
    scene->setSceneRect(0,0, 800, 600);
    score1 = new Score(340, 10);
    score2 = new Score(450, 10);
    player1 = new Paddle(50, scene->height()/2-150, score1);
    player2 = new Paddle(730, scene->height()/2-150, score2);
    label[0] = new QGraphicsSimpleTextItem;
    label[1] = new QGraphicsSimpleTextItem;
    ball = new Ball();
    central_line = new QGraphicsLineItem(400, 0, 400, 600);
    scene->addItem(ball);
    scene->addItem(player1);
    scene->addItem(player2);
    scene->addItem(score1);
    scene->addItem(score2);
    scene->addItem(central_line);
    scene->addItem(label[0]);
    scene->addItem(label[1]);
    ball->initRandomStart();
    connect(ball, SIGNAL(ballOut()), this, SLOT(resetBall()));
    if (isPlayedWithComputer){
        botTimer = new QTimer(this);
        botTimer->start(20);
        connect(botTimer, SIGNAL(timeout()), this, SLOT(moveBotPlayer()));
    }
}

void Game::setPlayersNames(QString name1, QString name2)
{
        label[0]->setFont(QFont("bitwise", 25));
        label[0]->setText(name1);
        label[0]->setPos(0, 20);

        label[1]->setFont(QFont("bitwise", 25));
        label[1]->setText(name2);
        label[1]->setPos(750, 10);
}

USBPlayedGame::USBPlayedGame(SerialConnector* serial, QWidget* parent, bool isPlayedWithComputer, int difficulty_level)
    :Game(isPlayedWithComputer, difficulty_level, parent), device(serial)
{
    connect(device, SIGNAL(newData(QVector<int>)), this, SLOT(movePlayers(QVector<int>)));
}

KeyboardPlayedGame::KeyboardPlayedGame(QWidget* parent, bool isPlayedWithComputer, int difficulty_level)
    :Game(isPlayedWithComputer, difficulty_level, parent)
{
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}

void Game::resetBall()
{
    if (ball->x() > width()/2){
        score1->increase();
    }
    else{
        score2->increase();
    }
    if (score1->getScore() == POINTS_ENDING_ROUND || score2->getScore() == POINTS_ENDING_ROUND){
        if (score1->getScore() == POINTS_ENDING_ROUND){
            points[0]++;
        }
        if (score2->getScore() == POINTS_ENDING_ROUND){
            points[1]++;
        }
        if (points[0] == 2 || points[1] == 2){
            QMessageBox msgBox;
            msgBox.setText("Koniec gry");
            msgBox.exec();
            delete this;
        }
        QMessageBox msgBox;
        score1->resetScore();
        score2->resetScore();
        msgBox.setText("Zmiana połów");
        msgBox.exec();
    }
    ball->initRandomStart();
}

void KeyboardPlayedGame::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case (Qt::Key_W):
        player1->moveRelative(-10);
        break;
    case (Qt::Key_S):
        player1->moveRelative(10);
        break;
    case (Qt::Key_Up):
        player2->moveRelative(-10);
        break;
    case (Qt::Key_Down):
        player2->moveRelative(10);
        break;
    }
}

int USBPlayedGame::normalizeInBounds(int var)
{
    int i = (var-10)*(scene->height()-player1->rect().height())/40;
    return i;
}

void USBPlayedGame::movePlayers(QVector<int> move)
{
    player1->moveAbsolute(normalizeInBounds(move.at(1)));
    if (!isPlayedWithComputer){
        player2->moveAbsolute(normalizeInBounds(move.at(0)));
    }
}

void Game::moveBotPlayer()
{
    int difference = player2->y() - ball->y();
    player2->moveRelative(-getSign(difference) * difficulty_level);

}

int getSign(int tested){return tested>0?1:-1;}
