#include "svserver.h"


SVServer::SVServer(ConsoleInterface *console)   {
    server = new QTcpServer(this);
    if (console)
        setConsole(console);
}

SVServer::~SVServer()   {
    server->close();
    delete server;
    foreach (QTcpSocket *socket, connections)   {
        socket->close();
        delete socket;
    }
}

void SVServer::setConsole(ConsoleInterface *console)    {
    this->console = console;
    connect(this, SIGNAL(signalConsoleMessage(QString)), console, SLOT(slotConsoleMessage(QString)));
    connect(console, SIGNAL(signalConsoleStart()), this, SLOT(slotConsoleStart()));
    connect(console, SIGNAL(signalConsoleStop()), this, SLOT(slotConsoleStop()));
    connect(console, SIGNAL(signalConsoleSend(QString)), this, SLOT(slotConsoleSend(QString)));
    console->listen();
}

void SVServer::print(QString const& message)    {
    if (console)    {
        emit(signalConsoleMessage(message));
    }
}

bool SVServer::start(QHostAddress const& adress, quint16 port)   {
    if (!server->isListening())   {
        bool ready = server->listen(adress, port);
        if (ready)  {
            print("Starting server...");
            connect(server, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
            connect(server, SIGNAL(acceptError(QAbstractSocket::SocketError)), this, SLOT(slotAcceptError(QAbstractSocket::SocketError)));
            print("Server is listening on adress " + adress.toString() + " and port " + QString::number(port));
        }   else
            print("Error. Cannor start server :(");
        return ready;
    }   else    {
        print("Warning! Server already working...");
        return true;
    }
}

void SVServer::stop()   {
    if (server->isListening())  {
        print("Server stopping...");
        server->close();
        foreach (QTcpSocket* socket, connections)   {
            delete socket;
        }
        connections.clear();
        print("Server stopped.");
    }   else    {
        print("Warning! Server is already disabled");
    }
}

void SVServer::slotNewConnection()  {
    print("New incoming connection...");
    QTcpSocket* newConnection = server->nextPendingConnection();
    connections.insert(newConnection->socketDescriptor(), newConnection);
    connect(newConnection, SIGNAL(disconnected()), this, SLOT(slotClientDisconnected()));
    connect(newConnection, SIGNAL(readyRead()),this, SLOT(slotReadyRead()));
    sendTo(newConnection, "greetings");
}

void SVServer::slotAcceptError(QAbstractSocket::SocketError error)    {
    print("Server error. Something went wrong :(");
}

void SVServer::sendAll(QString const& data)    {
    if (server->isListening())   {
        print("Sending data(" + data + ") to all...");
        if (!server->hasPendingConnections())   {
            return;
        }

        foreach (QTcpSocket* socket, connections)  {
            sendTo(socket, data);
        }
    }   else    {
        print("Warning! Server is disabled.");
    }
}

void SVServer::sendTo(QTcpSocket* socket, QString const& data)   {
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out << data;
    socket->write(arrBlock);
}

void SVServer::slotClientDisconnected() {
    print("Client disconnected.");
    QTcpSocket* disconnectedClient = dynamic_cast<QTcpSocket*>(sender());
    connections.remove(disconnectedClient->socketDescriptor());
    disconnectedClient->deleteLater();
}

void SVServer::slotReadyRead()  {
    print("Incomming data.");
    QTcpSocket* client = dynamic_cast<QTcpSocket*>(sender());
    QDataStream in(client);
    if (client->bytesAvailable())   {
        QString message;
        in >> message;
        print("Data: " + message);
    }
}

void SVServer::slotConsoleStart() {
    start();
}

void SVServer::slotConsoleStop()    {
    stop();
}

void SVServer::slotConsoleSend(QString message) {
    sendAll(message);
}
