#ifndef SVCLIENT_H
#define SVCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QDataStream>
#include <QTime>
#include <QNetworkInterface>
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
    void slotUISearch();
    void slotUIConnect(QString const& address, quint16 const& port);
    void slotUIDisconnect();
    void slotUICommand(TaskPackage const& task);
signals:
    void signalUIAddresses(QList<QString> const& addresses);
    void signalUIConnected(qint8 const& state);
    void signalUIDisconnected();
    void signalUIError(QString message);
    void signalUIData(DataPackage const& data);
    void signalUIDone(qint8 const& COI, qint8 const& answerCode);
};

#endif // SVCLIENT_H
