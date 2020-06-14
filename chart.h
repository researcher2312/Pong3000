#ifndef CHART_H
#define CHART_H

#include <QtCharts>
#include <QTimer>

#include "serialconnector.h"

using namespace QtCharts;


/*!
 * \class Chart
 * \brief Klasa umożliwiająca wyświetlanie danych z czujnika na żywo
 *
 * Poprzez wskaźnik na obiekt \link SerialConnector SerialConnector\endlink
 * jest w stanie pobierać aktualnie nadchodzące dane z czujników. Wyświetlane dane są
 * automatycznie przesuwane na wykresie
 */
class Chart: public QChart
{
    Q_OBJECT
public:
    /*!
     * \brief konstruktor klasy Chart
     * \param[in] connector wskaźnik na obiekt \link SerialConnector SerialConnector\endlink z którego będą pobierane dane
     * \param[in] side strona czujnik z której będą pobierane dane
     * \pre Wartość side musi być równa 0 lub 1
     * \param[in] parent rodzic obiektu
     * \param[in] wFlags flagi do stworzenia obiektu
     */
    Chart(SerialConnector* connector, int side, QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = {});
    virtual ~Chart();

public slots:
    /*!
     * \brief zapisuje nowe dane z komórki określonej przez parametr \link side side\endlink
     * \param[in] data dane z dwóch czujników przesłane przez urządzeie zewnętrzne
     */
    void handleNewData(QVector<int> data);
private slots:
    void handleTimeout();
private:
    SerialConnector* device;
    QTimer m_timer;
    QLineSeries* m_series;
    int m_chosen_side;
    QValueAxis *m_axisX;
    QValueAxis *m_axisY;
    qreal m_step;
    qreal m_x;
    qreal m_y;

};

#endif // CHART_H
