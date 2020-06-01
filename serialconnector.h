#ifndef SERIALCONNECTOR_H
#define SERIALCONNECTOR_H

#include <QSerialPort>


class SerialConnector: public QSerialPort
{
    Q_OBJECT
public:
    SerialConnector(QString, QObject*);
    SerialConnector(QObject*);
    bool connect(QString port_name);
private:
    bool setupSerialPort();
    QVector<int> convertInput(QString);
private slots:
    void readFromPort();
signals:
    void newData(QVector<int>);
};

#endif // SERIALCONNECTOR_H

