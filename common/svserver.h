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
#include <QQueue>
#include "datapackage.h"

class Server : public QTcpServer    {
    Q_OBJECT
public:
    Server(QObject *parent = nullptr);
};

class SVServer : public QObject
{
    Q_OBJECT
private:
    Server *server;
    QHostAddress address;
    quint16 port;
    QMap<qintptr, QTcpSocket*> connections;
    /*
     * все активные подключения хранятся в Map контейнере
     * в качестве ключа используется socket->socketDescriptor()
     */
    AuthPackage validAuthPackage;
    qint8 currentTaskCOI = 0;

    void sendTo(QTcpSocket* socket, QString const& data);
    void sendTo(QTcpSocket* socket, QByteArray const& data);
    void sendTo(QTcpSocket* socket, AnswerPackage const& answer);
    void sendTo(QTcpSocket* socket, AuthAnswerPackage const& answer);

    void log(QString const& message);
    void log(AnswerPackage const& answer);
    void log(MapPackage const& map);
public:
    SVServer();
    ~SVServer();

    bool start(QHostAddress const& adress = QHostAddress::Null, quint16 port = 55555);
    void stop();

    void sendAll(QString const& data);
    void sendAll(QByteArray const& data);
    void sendAll(AnswerPackage const& answer);

    QHostAddress getHostAddress() const;
    quint16 getPort() const;
    bool isListening() const;
    int activeConnections() const;
private slots:
    void slotNewConnection();
    void slotAcceptError(QAbstractSocket::SocketError error);
    void slotClientDisconnected();
    void slotReadyRead();
public slots:

    void slotUIStart(QString adress, quint16 port);
    void slotUIStop();
    void slotUISendAll(QString message);
    void slotUITestAnswer();
    void slotUITestData(qint32, qint32);

    void slotTaskDone(quint8 answerType);
    void slotSendHighFreqData(HighFreqDataPackage const& data);
    void slotSendLowFreqData(LowFreqDataPackage const& data);
    void slotSendSettings(SetPackage const& set);
    void slotSendMap(MapPackage const& map);
signals:
    void signalUILog(QString message);
    void signalUIChangeState(bool listening);

    void signalTaskForward(float distantion);
    void signalTaskWheels(float angle);
    void signalTaskFlick();
    void signalSetSteering(float p, float i, float d, float zero);
    void signalSetForward(float p, float i, float d, float integrator);
    void signalSetBackward(float p, float i, float d, float integrator);

    void signalUploadSettings();
    void signalNewConnection(qintptr descriptor);
    void signalDisconnected(qintptr descriptor);
};

#endif // SVSERVER_H
