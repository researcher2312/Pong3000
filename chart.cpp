#include "chart.h"

Chart::Chart(SerialConnector* serial, int side, QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    device(serial),
    m_series(0),
    m_chosen_side(side),
    m_axisX(new QValueAxis()),
    m_axisY(new QValueAxis()),
    m_step(0),
    m_x(5),
    m_y(1)
{
    QObject::connect(device, SIGNAL(newData(QVector<int>)), this, SLOT(handleNewData(QVector<int>)));

    m_series = new QLineSeries(this);
    QPen blue(Qt::blue);
    blue.setWidth(3);
    m_series->setPen(blue);

    addSeries(m_series);

    addAxis(m_axisX,Qt::AlignBottom);
    addAxis(m_axisY,Qt::AlignLeft);

    m_series->attachAxis(m_axisX);
    m_series->attachAxis(m_axisY);

    m_axisX->setTickCount(5);
    m_axisX->setRange(0, 10);
    m_axisY->setRange(0, 50);

    setTitle("Zależność odległości zmierzonej od czasu");
    legend()->hide();
    setAnimationOptions(QChart::AllAnimations);

    m_timer.start();
}

void Chart::handleNewData(QVector<int> data)
{
    m_series->append(qreal(m_timer.elapsed())/1000, data.at(m_chosen_side));
//    scroll(m_timer.elapsed()/1000, 0);
}

Chart::~Chart()
{

}
