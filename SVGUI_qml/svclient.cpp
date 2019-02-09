#include "svclient.h"

SVClient::SVClient()
{
    qDebug() << "Network client initializing...";
    socket = new QTcpSocket();
    connect(socket, SIGNAL(connected()), this, SLOT(slotConnected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));

    qDebug() << "Done. Network client is ready.";
}

SVClient::~SVClient() {
    socket->close();
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
    if (connected)  {
        qDebug() << "sending " + data + "...";

        char *bytes = new char[(size_t) data.length() + 2];
        bytes[0] = (char)data.length();
        for (int i = 0; i < data.length(); i++)    {
            bytes[i + 1] = (char) data.data()[i].toLatin1();
        }
        bytes[data.length() + 1] = '\0';
        socket->write(bytes);
        delete[] bytes;

    }   else {
        qDebug() << "there is no active connections";
    }
}

void SVClient::sendData(QByteArray data)    {
    if (connected)  {
        qDebug() << "sending " + data + " / sz " + QString::number(data.size()) + "...";
        data.push_front(static_cast<uint8_t>(data.size()));
        socket->write(data);

    }   else {
        qDebug() << "there is no active connections";
    }
    qDebug() << "send done";
}

void SVClient::sendAuthPackage()    {
    AuthPackage authPackage;
    sendData(authPackage.toBytes());
}

bool SVClient::isConnected() const    {
    return connected;
}

void SVClient::slotConnected()  {
    qDebug() << "Connected";
    connected = true;
    sendAuthPackage();
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
    qDebug() << "----------------------------------------------------------------------";
    qDebug() << "Incomming data...";
    if (socket->bytesAvailable())   {

        char blockSize = 0;
        socket->read(&blockSize, 1);

        QByteArray bytes = socket->readAll();
        QDataStream in(bytes);

        qDebug() << "Data(" << (int)blockSize << "): " << QString(bytes);

        if (bytes.at(0) == AuthAnswerPackage::packageType && blockSize == 4)    {
            qDebug() << "Valid answer code.";
            qDebug() << "Device type: " << QString::number(bytes[1]);
            qDebug() << "Device id: " << QString::number(bytes[2]);
            qDebug() << "State: " << QString::number(bytes[3]);

            emit signalUIConnected(bytes[3]);
        }
        if (bytes.at(0) == AnswerPackage::packageType && blockSize == 3)   {
            qDebug() << "Task #" << QString::number(bytes[1]) << " has been done.";
            qDebug() << "Answer code: " << QString::number(bytes[2]);
            emit signalUIDone(bytes[1], bytes[2]);
        }
        if (bytes.at(0) == DataPackage::packageType && blockSize >= 12) {
            qDebug() << "Data package: ";
            qint8 state = bytes[1];
            qDebug() << "State: " << QString::number(state);
            BI bi = {(unsigned char) bytes[2], (unsigned char) bytes[3],
                     (unsigned char) bytes[4], (unsigned char) bytes[5]};
            qint32 msec = bi.I;
            qDebug() << "Sending time: " << QTime::fromMSecsSinceStartOfDay(msec).toString();
            int dataBlockSize = bytes[6];
            DataPackage data;
            data.stateType = state;
            data.dataBlockSize = dataBlockSize;
            for (int i = 0; i < dataBlockSize; i++) {
                qint8 dataType = bytes[7 + i * 5];
                qDebug() << "Data type: " << QString::number(dataType);
                bi = {(unsigned char) bytes[8 + i * 5], (unsigned char) bytes[9 + i * 5],
                      (unsigned char) bytes[10 + i * 5], (unsigned char) bytes[11 + i * 5]};
                qint32 dataValue = bi.I;
                qDebug() << "Value: " << dataValue;
                data.data.append({dataType, dataValue});
            }
            emit signalUIData(data);
        }
        qDebug() << "----------------------------------------------------------------------";
    }   else {
        qDebug() << "Nothing to read.";
    }

}

void SVClient::slotUIConnect(QString const& address, quint16 const& port) {
    connectToHost(address, port);
}

void SVClient::slotUIDisconnect()   {
    disconnectFromHost();
}

void SVClient::slotUICommand(TaskPackage const& task)   {
    sendData(task.toBytes());
}
