#ifndef PADDLE_H
#define PADDLE_H

#include <QGraphicsRectItem>

class Paddle: public QGraphicsRectItem
{
public:
    Paddle(int x, int y);
    void keyPressEvent(QKeyEvent* event);
};

#endif // PADDLE_H
