#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsSimpleTextItem>

class Score: public QGraphicsSimpleTextItem
{
public:
    Score(int, int, QGraphicsItem* parent = nullptr);
    void increase();
    int getScore()const;
    void resetScore();
private:
    int score = 0;
    void update();
};

#endif // SCORE_H
