#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <QSerialPort>
#include <QObject>
#include <QWidget>

#include "ball.h"
#include "paddle.h"
#include "score.h"

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget* parent=nullptr);
protected:
    Paddle* player1;
    Paddle* player2;
private:
    QGraphicsLineItem* central_line;
    QGraphicsScene* scene;
    Ball* ball;
    Score* score1;
    Score* score2;
public slots:
    void resetBall();
};

class KeyboardPlayedGame: public Game
{
    Q_OBJECT
public:
    KeyboardPlayedGame(QWidget* parent=nullptr);
private:
    void keyPressEvent(QKeyEvent *event);
signals:
    void moveUp1();
    void moveUp2();
    void moveDown1();
    void moveDown2();
};

class USBPlayedGame: public Game
{
public:
    USBPlayedGame(QString, QWidget* parent=nullptr);
private:
    void setupSerialPort();
    QSerialPort* device;
};

#endif // GAME_H
