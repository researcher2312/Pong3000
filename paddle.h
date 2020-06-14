#ifndef PADDLE_H
#define PADDLE_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>

#include "score.h"

/*!
 * \class Paddle
 * \brief Klasa odpowiedzialna za przedstawienie graficzne i wygląd paletki gracza
 *
 * Paletka może być sterowana za pomocą sygnałów: \link #moveAbsolute moveAbsolute\endlink
 * i \link #moveRelative moveRelative\endlink
 */
class Paddle:  public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    /*!
     * \brief Konstruktor klasy Paddle
     * \param[in] x początkowa pozycja w osi x
     * \param[in] y początkowa pozycja w osi y
     * \param[in] new_score wskaźnik na obiekt klasy \link Score Score\endlink w którym przedstawiane są punkty gracza
     * \param[in] parent rodzic obiektu graficznego
     */
    Paddle(int x, int y, Score* new_score, QGraphicsItem* parent = nullptr);
    /*!
     * \brief przenosi paletkę we wskazane miejsce na planszy
     * \param[in] y współrzędna y na którą ma zostać przeniesiona paletka
     * \pre współrzędna y powinna znajdować się wewnątrz planszy
     */
    void moveAbsolute(int y);
    /*!
     * \brief przenosi paletkę o wskazaną odległość od obecnego miejsca
     * \param[in] y odległość na jaką ma się przenieść paletka
     */
    void moveRelative(int y);
private:
    Score* score;
};

#endif // PADDLE_H
