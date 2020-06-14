#ifndef BALL_H
#define BALL_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

#include "paddle.h"


/*!
 * \class Ball
 * \brief Klasa przedstawiająca piłkę
 *
 * Piłka odbija się między graczami
 * piłka sama porusza się w zadanym kierunku.
 * Piłka przy dotknięciu paletki gracza odbija się i wydaje dźwięk,
 * przy dotknięciu ściany górnej lub dolnej odbija sie ale nie wydaje dźwięku, przy
 * dotknięciu ściany prawej lub lewej emituje sygnał \link ballOut ballOut\endlink
 */
class Ball: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /*!
     * \brief Konstruktor klasy Ball
     */
    Ball();
    /*!
     * \brief funkcja resetująca położenie piłki
     *
     * ustawia piłkę na linii środkowej w losowym miejscu pomiędzy punktami [55, wysokość-55]
     * , nadaje jej losową prędkość w obu osiach z zakresu [5, 7] w obu osiach niezależnie
     */
    void initRandomStart();
signals:
    /*!
     * \brief sygnał wysyłany kiedy piłka dotknie którejś ze ścian bocznych
     */
    void ballOut();
private:
    QTimer* timer;
    int speed_x;
    int speed_y;
    bool detectWallCollision();
    bool detectPaddleColision();
    void initRandomSpeed();
    void initRandomCoords();
private slots:
    void move();
};

#endif // BALL_H
