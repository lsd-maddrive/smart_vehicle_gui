#ifndef SVCLIENT_H
#define SVCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QDataStream>
#include <QTime>
#include "datapackage.h"
#include "adapter.h"

union BI // byte / int conversion
{
    unsigned char bytes[4];
    unsigned  int I;
};

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
    void sendData(QByteArray data);
    void sendAuthPackage();
    bool isConnected() const;

private slots:
    void slotConnected();
    void slotDisconnected();
    void slotError(QAbstractSocket::SocketError socketError);
    void slotReadyRead();
public slots:
    void slotUIConnect(QString const& address, quint16 const& port);
    void slotUIDisconnect();
    void slotUICommand(TaskPackage const& task);
signals:
    void signalUIConnected(qint8 const& state);
    void signalUIDisconnected();
    void signalUIError(QString message);
    void signalUIData(DataPackage const& data);
};

#endif // SVCLIENT_H
