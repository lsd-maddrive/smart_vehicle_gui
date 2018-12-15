#ifndef SVCLIENT_H
#define SVCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QDataStream>

class SVClient : public QObject
{
    Q_OBJECT
private:
    QTcpSocket* socket;
    bool connected;
public:
    SVClient();
    ~SVClient();

    void connectToHost(QString const& adress, quint16 port);
    void disconnectFromHost();

    void sendData(QString data);
    bool isConnected() const;

public slots:
    void slotConnected();
    void slotDisconnected();
    void slotError(QAbstractSocket::SocketError socketError);
    void slotReadyRead();
signals:

};

#endif // SVCLIENT_H
