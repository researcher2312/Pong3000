#include <QKeyEvent>
#include "game.h"


Game::Game(QWidget* parent)
    :QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    setScene(scene);
    scene->setSceneRect(0,0, 800, 600);
    score1 = new Score(340, 10);
    score2 = new Score(450, 10);
    player1 = new Paddle(50, scene->height()/2-150, score1);
    player2 = new Paddle(730, scene->height()/2-150, score2);
    ball = new Ball();
    central_line = new QGraphicsLineItem(400, 0, 400, 600);
    scene->addItem(ball);
    scene->addItem(player1);
    scene->addItem(player2);
    scene->addItem(score1);
    scene->addItem(score2);
    scene->addItem(central_line);
    ball->initRandomStart();
    connect(ball, SIGNAL(ballOut()), this, SLOT(resetBall()));
}
USBPlayedGame::USBPlayedGame(QString port_name, QWidget* parent)
    :Game(parent)
{
    device = new QSerialPort(port_name, this);
    setupSerialPort();
}

KeyboardPlayedGame::KeyboardPlayedGame(QWidget* parent)
    :Game(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
    connect(this, SIGNAL(moveUp1()), player1, SLOT(moveUp()));
    connect(this, SIGNAL(moveUp2()), player2, SLOT(moveUp()));
    connect(this, SIGNAL(moveDown1()), player1, SLOT(moveDown()));
    connect(this, SIGNAL(moveDown2()), player2, SLOT(moveDown()));
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

void KeyboardPlayedGame::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case (Qt::Key_Up):
        emit moveUp2();
        break;
    case (Qt::Key_Down):
        emit moveDown2();
        break;
    case (Qt::Key_W):
        emit moveUp1();
        break;
    case (Qt::Key_S):
        emit moveDown1();
        break;
    }
}

void USBPlayedGame::setupSerialPort()
{
    if(device->open(QSerialPort::ReadWrite))
    {
      this->device->setBaudRate(QSerialPort::Baud9600);
      this->device->setDataBits(QSerialPort::Data8);
      this->device->setParity(QSerialPort::NoParity);
      this->device->setStopBits(QSerialPort::OneStop);
      this->device->setFlowControl(QSerialPort::NoFlowControl);
    }
}
