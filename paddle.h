#ifndef PADDLE_H
#define PADDLE_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>

#include "score.h"


class Paddle: public QGraphicsRectItem
{
private:
    Score* score;
public:
    Paddle(int x, int y, Score* new_score, QGraphicsItem* parent = nullptr);
    void keyPressEvent(QKeyEvent* event);
};

#endif // PADDLE_H
