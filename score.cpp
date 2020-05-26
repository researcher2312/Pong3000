#include <QString>
#include <QFont>
#include "score.h"



Score::Score(int x, int y, QGraphicsItem* parent):
    QGraphicsSimpleTextItem(parent)
{
    setFont(QFont("bitwise", 25));
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
    update();
}

int Score::getScore()const
{
    return score;
}
