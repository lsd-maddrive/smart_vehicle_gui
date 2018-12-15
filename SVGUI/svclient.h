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

private slots:
    void slotConnected();
    void slotDisconnected();
    void slotError(QAbstractSocket::SocketError socketError);
    void slotReadyRead();
public slots:
    void slotUIConnect(QString address, quint16 port);
    void slotUIDisconnect();
signals:
    void signalUIConnected();
    void signalUIDisconnected();
    void signalUIError(QString message);
};

#endif // SVCLIENT_H
