#ifndef PADDLE_H
#define PADDLE_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>

#include "score.h"


class Paddle:  public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    Score* score;
public:
    Paddle(int x, int y, Score* new_score, QGraphicsItem* parent = nullptr);
    void moveAbsolute(int);
    void moveRelative(int);
};

#endif // PADDLE_H
