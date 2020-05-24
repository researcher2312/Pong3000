#include <QString>
#include <QFont>
#include "score.h"



Score::Score(int x, int y, QGraphicsItem* parent):
    QGraphicsSimpleTextItem(parent)
{
    setFont(QFont("times", 16));
    setPos(x, y);
    update();
}

void Score::update()
{
    setText(QString::number(score));
}

void Score::increase()
{
    ++score;
}

int Score::getScore()const
{
    return score;
}
