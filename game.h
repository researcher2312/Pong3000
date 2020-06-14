#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <QGraphicsSimpleTextItem>

#include <QObject>
#include <QWidget>

#include "ball.h"
#include "paddle.h"
#include "score.h"
#include "serialconnector.h"

/**
 * \class Game
 *
 * \brief Podstawowy interfejs do uruchomienia gry
 *
 * Gra odbywa się pomiędzy dwoma graczami przedstawianymi przez paletki
 * W zależności od preferowanej metody wejścia, powinno się używać
 * którejś z klas potomnych: \link KeyboardPlayedGame KeyboardPlayedGame\endlink
 * lub \link USBPlayedGame USBPlayedGame\endlink
 *
 * Gra rozgrywana jest do momentu gdy któryś z graczy zdobędzie dwa razy sumę 11 punktów
 *
 */

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    /*!
     * \brief Konstruktor klasy Game
     * \param[in] isPlayedWithComputer określa czy w grze bierze dwóch graczy czy jeden gracz z komputerem
     * \param[in] difficulty_level określa poziom trudności
     * \pre Wartość parametru difficulty_level musi być większa od zera
     * \param[in] parent rodzic obiektu
     */
    Game(bool isPlayedWithComputer, int difficulty_level, QWidget* parent=nullptr);
    /*! \brief Ustawia imoiona graczy
    *\param[in] name1 imię pierwszego gracza
    *\param[in] name2 imię drugiego gracza
    *
    * Imiona graczy są wyświetlane w rogach ekranu
    */
    void setPlayersNames(QString name1, QString name2);
protected:
    /*! \brief Paletka pierwszego gracza
    *
    * Wskaźnik do klasy przechowującej paletkę pierwszego gracza
    */
    Paddle* player1;
    /*! \brief Paletka drugiego gracza
     *
    * Wskaźnik do klasy przechowującej paletkę pdrugiego gracza
    */
    Paddle* player2;
    /*! \brief Scena
     *
    * Przechowuje scenę za pomocą której wyświetlana jest zawartość gry
    */
    QGraphicsScene* scene;
    /*! \brief Czy gram z komputerem
     *
     * Zmienna służy do określenia czy gra dwóch graczy czy jeden gra z komputerem
    */
    bool isPlayedWithComputer;
    /*! \brief Poziom trudności
    *
    * Służy do określenia trudności w wypadku gry z graczem komputerowym
    */
    int difficulty_level;
public slots:
    /*! \brief Resetuje położenie piłki i nalicza punkty
     *
     * W zależności od połowy boiska na którym znajduje się piłka nalicza
     * odpowiedniemu graczowi punkty. Położenie, prędkość i kierunek piłki
     * są losowane na nowo. Jeżeli któryś z graczy zdobył wymaganą liczbę punktów wyświetlany jest komunikat
     * o zmianie połów
    */
    void resetBall();
    /*! \brief Porusza paletką bota
     *
     * W zależności od wartości pola \link Game::difficulty_level difficulty_level\endlink
     * przesuwa paletkę sterowaną przez komputer o pewną odległość w kierunku piłki
    *
    */
    void moveBotPlayer();
private:
    QGraphicsLineItem* central_line;
    Ball* ball;
    Score* score1;
    Score* score2;
    QTimer *botTimer;
    QGraphicsSimpleTextItem *label[2];
    int points[2] = {0};
};

/**
 * \class KeyboardPlayedGame
 *
 *
 * \brief Gra sterowana z klawiatury
 *
 *Gra ustawia na siebie KeyboardFocus i po przechwyceniu wydarzenia z klawiatury
 * przekazuje sygnał nakazujący ruch do slotów \link Paddle::moveRelative() moveRelative\endlink
 * paletek graczy
 *
 */

class KeyboardPlayedGame: public Game
{
    Q_OBJECT
public:
    /*!
     * \brief Konstruktor klasy KeyboardPlayedGame
     * \param[in] isPlayedWithComputer określa czy w grze bierze dwóch graczy czy jeden gracz z komputerem
     * \param[in] difficulty_level określa poziom trudności
     * \pre Wartość parametru difficulty_level musi być większa od zera
     * \param[in] parent rodzic obiektu
     */
    KeyboardPlayedGame( QWidget* parent=nullptr, bool isPlayedWithComputer = false, int difficulty_level = 0);
private:
    void keyPressEvent(QKeyEvent *event);
};

/**
 * \class USBPlayedGame
 *
 *
 * \brief Gra sterowana z zewnętrznego kontrolera
 *
 * Gra pobiera informacje z obiektu \link SerialConnector SerialConnector \endlink
 * wysyłane sygnałem \link SerialConnector::newData newData \endlink
 * następnie dane odczytane z czujnika są normalizowane dla wielkości planszy
 * i przeazywane do paletek graczy do slotu \link Paddle::moveAbsolute moveAbsolute\endlink
 *
 */
class USBPlayedGame: public Game
{
    Q_OBJECT
public:
    /*!
     * \brief Konstruktor klasy USBPlayedGame
     * \param[in] isPlayedWithComputer określa czy w grze bierze dwóch graczy czy jeden gracz z komputerem
     * \param[in] difficulty_level określa poziom trudności
     * \pre Wartość parametru difficulty_level musi być większa od zera
     * \param[in] parent rodzic obiektu
     */
    USBPlayedGame(SerialConnector*,  QWidget* parent=nullptr, bool isPlayedWithComputer = false, int difficulty_level = 0);
private:
    int normalizeInBounds(int);
    SerialConnector* device;
private slots:
    void movePlayers(QVector<int>);
};

int getSign(int);

#endif // GAME_H
