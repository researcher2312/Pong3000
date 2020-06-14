#include "serialconnector.h"

#include <QDebug>
#include <QObject>

SerialConnector::SerialConnector(QString port_name, QObject* parent)
    :QSerialPort(port_name, parent)
{
    setupSerialPort();
}

SerialConnector::SerialConnector(QObject* parent)
    :QSerialPort(parent){}

bool SerialConnector::setupSerialPort()
{
    if(!isOpen()){
        if(open(QSerialPort::ReadWrite)){
            setBaudRate(QSerialPort::Baud9600);
            setDataBits(QSerialPort::Data8);
            setParity(QSerialPort::NoParity);
            setStopBits(QSerialPort::OneStop);
            setFlowControl(QSerialPort::NoFlowControl);
            QObject::connect(this, SIGNAL(readyRead()), this, SLOT(readFromPort()));
            return true;
        }
    }
    return false;
}

void SerialConnector::readFromPort()
{
    while(canReadLine()){
      QString line = readLine();
      QVector<int> message = convertInput(line);
      if (message.size() == 2)
        emit (newData(message));
    }
}

bool SerialConnector::connect(QString port_name)
{
    setPortName(port_name);
    return setupSerialPort();
}


QVector<int> SerialConnector::convertInput(QString line)
{
    QVector<int> data;
    line.remove("\r\n");
    QStringList moveList = line.split(' ');
    if (moveList.size() == 2){
         data = {moveList.at(0).toInt(), moveList.at(1).toInt()};
    }
    return data;
}
