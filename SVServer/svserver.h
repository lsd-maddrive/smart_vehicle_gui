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
    AuthPackage validAuthPackage;
    QQueue<quint8> coiQueue;

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

    bool start(QHostAddress const& adress = QHostAddress::AnyIPv4 , quint16 port = 80);
    void stop();

    void sendAll(QString const& data);
    void sendAll(QByteArray const& data);
    void sendAll(AnswerPackage const& answer);
    void sendAll(DataPackage const& data);

    QHostAddress getHostAdress() const;
    quint16 getPort() const;
    bool isListening() const;
private slots:
    void slotNewConnection();
    void slotAcceptError(QAbstractSocket::SocketError error);
    void slotClientDisconnected();
    void slotReadyRead();
public slots:
    void slotUIStart(QString adress, quint16 port);
    void slotUIStop();
    void slotUISendAll(QString message);
    void slotUITestSend(QString command);

    void slotTaskDone(quint8 answerType);
    void slotSendData(DataPackage data);
signals:
    void signalUILog(QString message);
    void signalUIChangeState(bool listening);

    void signalTask(TaskPackage task);
    void signalSet(SetPackage set);
};

#endif // SVSERVER_H
