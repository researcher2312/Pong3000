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
    connect(device, SIGNAL(readyRead()), this, SLOT(readFromPort()));
}

KeyboardPlayedGame::KeyboardPlayedGame(QWidget* parent)
    :Game(parent)
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
    ball->initRandomStart();
}

void KeyboardPlayedGame::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case (Qt::Key_Up):
        player2->moveRelative(-10);
        break;
    case (Qt::Key_Down):
        player2->moveRelative(10);
        break;
    case (Qt::Key_W):
        player1->moveRelative(-10);
        break;
    case (Qt::Key_S):
        player1->moveRelative(10);
        break;
    }
}

void USBPlayedGame::setupSerialPort()
{

    if(!device->isOpen()){
        if(device->open(QSerialPort::ReadWrite)){
            this->device->setBaudRate(QSerialPort::Baud9600);
            this->device->setDataBits(QSerialPort::Data8);
            this->device->setParity(QSerialPort::NoParity);
            this->device->setStopBits(QSerialPort::OneStop);
            this->device->setFlowControl(QSerialPort::NoFlowControl);
        }
    }
}

int USBPlayedGame::normalizeInBounds(int var)
{
    int i = (var-10)*(scene->height()-player1->rect().height())/40;
    return i;
}

void USBPlayedGame::readFromPort() {
  while(device->canReadLine()) {
    QString line = device->readLine();
    line.remove("\r\n");
    QStringList moveList = line.split(' ');
    if (moveList.size() == 2){
        player2->moveAbsolute(normalizeInBounds(moveList.at(0).toInt()));
        player1->moveAbsolute(normalizeInBounds(moveList.at(1).toInt()));
    }
        //qDebug() << moveList.at(0) << ' ' << moveList.at(1);
  }
}
