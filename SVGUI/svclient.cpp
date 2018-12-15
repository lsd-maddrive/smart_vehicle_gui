#include "svclient.h"

SVClient::SVClient()
{
    qDebug() << "client init...";
    socket = new QTcpSocket();
    connect(socket, SIGNAL(connected()), this, SLOT(slotConnected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(socket, SIGNAL(QAbstractSocket::SocketError), this, SLOT(slotError(QAbstractSocket::SocketError)));
}

SVClient::~SVClient() {
    delete socket;
}

void SVClient::connectToHost(QString const& adress, quint16 port) {
    qDebug() << "connecting to " + adress + "...";
    socket->connectToHost(adress, port);
    if (!socket->waitForConnected(3000))    {
        emit signalUIError("Connection timeout");
    }
}

void SVClient::disconnectFromHost() {
    qDebug() << "disconnecting...";
    if (connected)  {
        socket->disconnectFromHost();
    }   else
        qDebug() << "there is no active connections";
}

void SVClient::sendData(QString data)   {
    qDebug() << "sending " + data + "...";

    if (connected)  {

    }   else {

    }
}

bool SVClient::isConnected() const    {
    return connected;
}

void SVClient::slotConnected()  {
    qDebug() << "Connected";
    connected = true;
    emit signalUIConnected();
}

void SVClient::slotDisconnected()   {
    qDebug() << "Disconnected";
    connected = false;
    emit signalUIDisconnected();
}

void SVClient::slotError(QAbstractSocket::SocketError socketError)  {
    qDebug() << socketError;
}

void SVClient::slotReadyRead()  {
    qDebug() << "Incomming data...";
    if (socket->bytesAvailable())   {
        socket->flush();
        QByteArray bytes;
        char size = 0;
        socket->read(&size, 1);
        bytes = socket->readAll();
        QString message(bytes);

        if (message.endsWith("\r\n"))
            message.chop(2);

        qDebug() << "Data(" << (int)size << "): " << message;
    }

}

void SVClient::slotUIConnect(QString address, quint16 port) {
    connectToHost(address, port);
}

void SVClient::slotUIDisconnect()   {
    disconnectFromHost();
}
