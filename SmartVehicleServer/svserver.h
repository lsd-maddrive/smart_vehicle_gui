#ifndef SVSERVER_H
#define SVSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QDataStream>
#include "consoleinterface.h"
#include <QDebug>

class SVServer : public QObject
{
    Q_OBJECT
private:
    QTcpServer *server;
    QMap<qintptr, QTcpSocket*> connections;
    /*
     * все активные подключения хранятся в Map контейнере
     * в качестве ключа используется socket->socketDescriptor()
     */
    ConsoleInterface* console;

    void print(QString const& message);
    void sendTo(QTcpSocket* socket, QString const& data);
public:
    SVServer(ConsoleInterface *console = nullptr);
    ~SVServer();
    void setConsole(ConsoleInterface *console);

    bool start(QHostAddress const& adress = QHostAddress::Any, quint16 port = 80);
    void stop();

    void sendAll(QString const& data);
public slots:
    void slotNewConnection();
    void slotAcceptError(QAbstractSocket::SocketError error);
    void slotClientDisconnected();
    void slotReadyRead();

    void slotConsoleStart();
    void slotConsoleStop();
    void slotConsoleSend(QString message);
signals:
    void signalConsoleMessage(QString message);
};

#endif // SVSERVER_H
