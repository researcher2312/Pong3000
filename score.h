#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsSimpleTextItem>

class Score: public QGraphicsSimpleTextItem
{
private:
    int score = 0;
    void update();
public:
    Score(int, int, QGraphicsItem* parent = nullptr);
    void increase();
    int getScore()const;
    void resetScore();
};

#endif // SCORE_H
