#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <QGraphicsSimpleTextItem>

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
    Game(bool isPlayedWithComputer, int difficulty_level, QWidget* parent=nullptr);
    void setPlayersNames(QString, QString);
protected:
    Paddle* player1;
    Paddle* player2;
    QGraphicsScene* scene;
    bool isPlayedWithComputer;
    int difficulty_level;
private:
    QGraphicsLineItem* central_line;
    Ball* ball;
    Score* score1;
    Score* score2;
    QTimer *botTimer;
    QGraphicsSimpleTextItem *label[2];
    int points[2] = {0};
public slots:
    void resetBall();
    void moveBotPlayer();
};

class KeyboardPlayedGame: public Game
{
    Q_OBJECT
public:
    KeyboardPlayedGame( QWidget* parent=nullptr, bool isPlayedWithComputer = false, int difficulty_level = 0);
private:
    void keyPressEvent(QKeyEvent *event);
};

class USBPlayedGame: public Game
{
    Q_OBJECT
public:
    USBPlayedGame(SerialConnector*,  QWidget* parent=nullptr, bool isPlayedWithComputer = false, int difficulty_level = 0);
private:
    int normalizeInBounds(int);
    SerialConnector* device;
private slots:
    void movePlayers(QVector<int>);
};

int getSign(int);

#endif // GAME_H
