#ifndef CHART_H
#define CHART_H

#include <QtCharts>
#include <QTimer>

#include "serialconnector.h"

using namespace QtCharts;

class Chart: public QChart
{
    Q_OBJECT
public:
    Chart(SerialConnector*, int side, QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = {});
    virtual ~Chart();

public slots:
    void handleNewData(QVector<int> data);
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
