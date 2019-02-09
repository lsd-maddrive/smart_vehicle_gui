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

union BI // byte / int conversion
{
    unsigned char bytes[4];
    unsigned  int I;
};

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
    void sendTo(QTcpSocket* socket, DataPackage const& data);
    void sendTo(QTcpSocket* socket, AuthAnswerPackage const& answer);

    void log(QString message);
    void log(AnswerPackage answer);
    void log(DataPackage data);
public:


    SVServer();
    ~SVServer();

    void setUI(QObject const *UI);

    bool start(QHostAddress const& adress = QHostAddress::Null, quint16 port = 55555);
    void stop();

    void sendAll(QString const& data);
    void sendAll(QByteArray const& data);
    void sendAll(AnswerPackage const& answer);
    void sendAll(DataPackage const& data);



    QHostAddress getHostAddress() const;
    quint16 getPort() const;
    bool isListening() const;
private slots:
    void slotNewConnection();
    void slotAcceptError(QAbstractSocket::SocketError error);
    void slotClientDisconnected();
    void slotReadyRead();
public slots:
    void sendData(DataPackage const& data);

    void slotUIStart(QString adress, quint16 port);
    void slotUIStop();
    void slotUISendAll(QString message);
    void slotUITestAnswer();
    void slotUITestData(qint32, qint32);

    void slotTaskDone(quint8 answerType);
    void slotSendData(DataPackage data);
signals:
    void signalUILog(QString message);
    void signalUIChangeState(bool listening);

    void signalTaskForward(qint32 distantion);
    void signalTaskWheels(qint32 angle);
    void signalTaskFlick();
    void signalSetPID(qint32 p, qint32 i, qint32 d);
    void signalSetServoZero(qint32 zero);
};

#endif // SVSERVER_H
