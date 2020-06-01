#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsView>

#include <QObject>
#include <QWidget>

#include "ball.h"
#include "paddle.h"
#include "score.h"
#include "serialconnector.h"

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
    USBPlayedGame(SerialConnector*, QWidget* parent=nullptr);
private:
    int normalizeInBounds(int);
    SerialConnector* device;
private slots:
    void movePlayers(QVector<int>);
};

#endif // GAME_H
