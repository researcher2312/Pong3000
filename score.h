#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsSimpleTextItem>

/*!
 * \class Score
 * \brief Klasa przechowująca i wyświetlająca wynik w punktach
 */
class Score: public QGraphicsSimpleTextItem
{
public:
    /*!
     * \brief konstruktor klasy Score
     * \param[in] parent rodzic obiektu
     */
    Score(int, int, QGraphicsItem* parent = nullptr);
    /*!
     * \brief zwiększa wartość przechowywanego licznika o 1
     */
    void increase();
    /*!
     * \brief zwraca obecny wynik punktowy
     * \return obecna ilość punktów
     */
    int getScore()const;
    /*!
     * \brief ustawia ilość punktów na 0
     */
    void resetScore();
private:
    int score = 0;
    void update();
};

#endif // SCORE_H
