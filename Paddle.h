#ifndef PADDLE_H
#define PADDLE_H

#include <QGraphicsRectItem>

class Paddle: public QGraphicsRectItem
{
public:
    void keyPressEvent(QKeyEvent* event);
};

#endif // PADDLE_H
