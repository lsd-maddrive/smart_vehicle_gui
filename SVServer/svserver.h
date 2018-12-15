#ifndef SVSERVER_H
#define SVSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QVector>
#include <QDataStream>
#include <QNetworkInterface>
#include <QDebug>
#include <QThread>
#include <QTime>

class SVServer : public QObject
{
    Q_OBJECT
private:
    QTcpServer *server;
    QHostAddress adress;
    quint16 port;
    QMap<qintptr, QTcpSocket*> connections;
    /*
     * все активные подключения хранятся в Map контейнере
     * в качестве ключа используется socket->socketDescriptor()
     */

    void sendTo(QTcpSocket* socket, QString const& data);
    void log(QString const& message);
public:
    SVServer();
    ~SVServer();


    bool start(QHostAddress const& adress = QHostAddress::AnyIPv4 , quint16 port = 80);
    void stop();

    void sendAll(QString const& data);

    QHostAddress getHostAdress() const;
    quint16 getPort() const;
    bool isListening() const;
public slots:
    void slotNewConnection();
    void slotAcceptError(QAbstractSocket::SocketError error);
    void slotClientDisconnected();
    void slotReadyRead();

    void slotUIStart(QString adress, quint16 port);
    void slotUIStop();
    void slotUISend(QString message);
signals:
    void signalUILog(QString message);
    void signalUIChangeState(bool listening);
};

#endif // SVSERVER_H
