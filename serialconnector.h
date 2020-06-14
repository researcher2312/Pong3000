#ifndef SERIALCONNECTOR_H
#define SERIALCONNECTOR_H

#include <QSerialPort>


/**
 * \class SerialConnector
 *
 *
 * \brief Klasa zajmująca się nawiązaniem połączenia i nadzorem nad połączeniem z szeregowym portem komunikacyjnym
 *
 * Klasa wysyła sygnał \link newData newData \endlink zawierający odzytane i sformatowane dane
 *
 */

class SerialConnector: public QSerialPort
{
    Q_OBJECT
public:
    /*!
     * \brief Konstruktor klasy SerialConnector od razu tworzący łączenie do portu szeregowego
     * \param[in] name nazwa portu szeregwego
     * \param[in] parent rodzic obiektu
     */
    SerialConnector(QString name, QObject* parent);
    /*!
     * \brief Konstruktor klasy SerialConnector nie tworzący połączenia z portem
     * \param[in] parent rodzic obiektu
     */
    SerialConnector(QObject* parent);
    /*!
     * \brief Ustanawia połączenie z portem szeregowym
     * \param[in] port_name nazwa portu szeregowego
     * \return jeżeli udało się nawiązać połączenie zwraca true, jeżeli nie to false
     *
     * Połączenie zostaje nawiązane ze standardowymi parametrami baudrate 9600, parzystość włączona, controlflow włączony
     */
    bool connect(QString port_name);
signals:
    /*!
     * \brief Przesyła dane odebrane z portu szeregowego
     * \param[out] data Dwuwartościowy wektor zawierający dane z pierwszego i drugiego czujnika w kontrolerze
     *
     *  Po odczytaniu nowych danych z portu szeregowego wysyłany jest sygnał zawierający odczytane dane
     */
    void newData(QVector<int> data);
private:
    bool setupSerialPort();
    QVector<int> convertInput(QString);
private slots:
    void readFromPort();
};

#endif // SERIALCONNECTOR_H

