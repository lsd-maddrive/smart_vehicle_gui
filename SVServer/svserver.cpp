#include "svserver.h"


SVServer::SVServer()   {
    log("Server initializing...");
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
    connect(server, SIGNAL(acceptError(QAbstractSocket::SocketError)), this, SLOT(slotAcceptError(QAbstractSocket::SocketError)));
}

SVServer::~SVServer()   {
    server->close();
    delete server;
    foreach (QTcpSocket *socket, connections)   {
        socket->close();
        delete socket;
    }
}

void SVServer::log(QString const& message) {
    QString timedMessage = QTime::currentTime().toString() + ": " + message;
    emit signalUILog(timedMessage);
    qDebug() << timedMessage;
}

bool SVServer::start(QHostAddress const& adress, quint16 port)   {
    log("Starting server...");
    if (!server->isListening())   {
        bool ready = server->listen(adress, port);
        if (ready)  {

            this->port = port;
            foreach (QHostAddress adress, QNetworkInterface::allAddresses())    {
                if (adress != QHostAddress::LocalHost && adress.toIPv4Address())    {
                    this->adress = adress;
                    break;
                }
            }
            log("Server is listening.");
        }   else    {
            log("Error! Cannot start server.");
        }
        emit signalUIChangeState(ready);
        return ready;
    }   else    {
        log("Warning! Server is already working...");
        return true;
    }
}

void SVServer::stop()   {
    if (server->isListening())  {
        log("Server stopping...");
        foreach (QTcpSocket* socket, connections)   {
            socket->close();
            delete socket;
        }
        connections.clear();

        server->close();
        log("Server stopped");
        emit signalUIChangeState(false);
    }   else    {
        log("Warning! Server is already disabled,");
    }
}

void SVServer::sendAll(QString const& data)    {
    if (server->isListening())   {
        log("Sending data [" + data + "] to all...");

        foreach (QTcpSocket* socket, connections)  {
            sendTo(socket, data);
        }
        log("Done.");
    }   else    {
        log("Warning! Server is disabled");
    }
}

void SVServer::sendTo(QTcpSocket* socket, QString const& data)   {
    char *bytes = new char[(size_t) data.length() + 2];
    bytes[0] = (char)data.length();
    for (int i = 0; i < data.length(); i++)    {
        bytes[i + 1] = (char) data.data()[i].toLatin1();
    }
    bytes[data.length() + 1] = '\0';
    socket->write(bytes);
}

QHostAddress SVServer::getHostAdress() const    {
    return adress;
}

quint16 SVServer::getPort() const   {
    return port;
}

bool SVServer::isListening() const  {
    return server->isListening();
}

void SVServer::slotNewConnection()  {
    log("New connection.");
    QTcpSocket* newConnection = dynamic_cast<QTcpSocket*>(server->nextPendingConnection());
    connections.insert(newConnection->socketDescriptor(), newConnection);
    connect(newConnection, SIGNAL(disconnected()), this, SLOT(slotClientDisconnected()));
    connect(newConnection, SIGNAL(readyRead()),this, SLOT(slotReadyRead()));
    connect(newConnection, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotAcceptError(QAbstractSocket::SocketError)));
    log("Socket descriptor: " + QString::number(newConnection->socketDescriptor()));
}

void SVServer::slotAcceptError(QAbstractSocket::SocketError error)    {
    qDebug() << error;
}

void SVServer::slotClientDisconnected() {
    log("Client disconnected");
    QTcpSocket* disconnectedClient = dynamic_cast<QTcpSocket*>(sender());
    connections.remove(connections.key(disconnectedClient));
    disconnectedClient->deleteLater();
}

void SVServer::slotReadyRead()  {
    log("Incoming data");
    QTcpSocket* client = dynamic_cast<QTcpSocket*>(sender());

    if (client->bytesAvailable())   {
        QByteArray bytes = client->readAll();
        QString message(bytes);
        if (message.endsWith("\r\n"))
            message.chop(2);

        log("Data: " + message);
    }
}

void SVServer::slotUIStart(QString adress, quint16 port) {
    start(QHostAddress(adress), port);
}

void SVServer::slotUIStop()    {
    stop();
}

void SVServer::slotUISend(QString message) {
    sendAll(message);
}
