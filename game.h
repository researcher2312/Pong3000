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
    QGraphicsScene* scene;
private:
    QGraphicsLineItem* central_line;
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
};

class USBPlayedGame: public Game
{
    Q_OBJECT
public:
    USBPlayedGame(QString, QWidget* parent=nullptr);
private:
    int normalizeInBounds(int);
    void setupSerialPort();
    QSerialPort* device;
private slots:
    void readFromPort();
};

#endif // GAME_H
