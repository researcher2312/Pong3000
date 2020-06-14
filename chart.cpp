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
    QObject::connect(&m_timer, &QTimer::timeout, this, &Chart::handleTimeout);

    m_series = new QLineSeries(this);
    QPen blue(Qt::blue);
    blue.setWidth(3);
    m_series->setPen(blue);

    addSeries(m_series);

    addAxis(m_axisX,Qt::AlignBottom);
    addAxis(m_axisY,Qt::AlignLeft);

    m_series->attachAxis(m_axisX);
    m_series->attachAxis(m_axisY);

    m_axisX->setTickCount(20);
    m_axisX->setRange(0, 10);
    m_axisY->setRange(0, 50);

    legend()->hide();
    setAnimationOptions(QChart::AllAnimations);

    m_timer.setInterval(500);
    m_timer.start();
}

void Chart::handleTimeout()
{
    qreal x = plotArea().width() / m_axisX->tickCount();
    qreal y = (m_axisX->max() - m_axisX->min()) / m_axisX->tickCount();
    m_x += y;
    m_series->append(m_x, m_y);

    scroll(x, 0);
}

void Chart::handleNewData(QVector<int> data)
{  
    m_y = data.at(m_chosen_side);
}

Chart::~Chart()
{

}
