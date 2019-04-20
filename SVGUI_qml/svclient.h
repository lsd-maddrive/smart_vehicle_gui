#ifndef SVCLIENT_H
#define SVCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QDataStream>
#include <QTime>
#include <QTimer>
#include <QNetworkInterface>
#include "datapackage.h"

class SVClient : public QObject
{
    Q_OBJECT
private:
    QTcpSocket* socket;
    bool connected = false;
    bool gotAuthPackage = false;
    unsigned brokenPackages = 0;
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
    void slotUISettingsLoad(SetPackage const& set);
    void slotUISettingsUpload();
    void slotUIControl(ControlPackage const& data);
signals:
    void signalUIAddresses(QList<QString> const& addresses);
    void signalUIConnected(qint8 const& state);
    void signalUIDisconnected();
    void signalUIError(QString message);
    void signalUIData(LowFreqDataPackage const& data);
    void signalUIData(HighFreqDataPackage const& data);
    void signalUIDone(qint8 const& answerCode);
    void signalUISettings(SetPackage const& set);
    void signalUIMap(MapPackage const& map);
    void signalUIBrokenPackage();
};

#endif // SVCLIENT_H
