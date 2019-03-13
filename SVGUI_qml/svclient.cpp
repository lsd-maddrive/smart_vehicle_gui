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

        char *bytes = new char[static_cast<size_t>(data.length()) + 2];
        bytes[0] = static_cast<char>(data.length());
        for (int i = 0; i < data.length(); i++)    {
            bytes[i + 1] = static_cast<char>(data.data()[i].toLatin1());
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
        qDebug() << "send done";
    }   else {
        qDebug() << "there is no active connections";
    }
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
    QTimer::singleShot(3000, [this] {
        if (!gotAuthPackage)
            this->disconnectFromHost();
    });
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

        QByteArray bytes = socket->read(blockSize);

        qDebug() << "Data(" << (int)blockSize << "): " << QString(bytes);

        if (bytes.at(0) == AuthAnswerPackage::packageType)    {
            qDebug() << "Valid answer code.";
            qDebug() << "Device type: " << QString::number(bytes[1]);
            qDebug() << "Device id: " << QString::number(bytes[2]);
            qDebug() << "State: " << QString::number(bytes[3]);

            gotAuthPackage = true;
            emit signalUIConnected(bytes[3]);
        }   else if (bytes.at(0) == AnswerPackage::packageType)   {
            qDebug() << "Task #" << QString::number(bytes[1]) << " has been done.";
            qDebug() << "Answer code: " << QString::number(bytes[2]);
            emit signalUIDone(bytes[1], bytes[2]);
        }   else if (bytes.at(0) == DataPackage::packageType) {
            DataPackage data(bytes);
            emit signalUIData(data);
        }   else if (bytes.at(0) == SetPackage::packageType) {
            qDebug() << "Uploading settings...";
            SetPackage set(bytes);
            emit signalUISettings(set);
        }   else if (bytes.at(0) == MapPackage::packageType) {
            MapPackage map(bytes);
            emit signalUIMap(map);
        }   else {
            brokenPackages++;
            emit signalUIBrokenPackage();
        }
        qDebug() << "----------------------------------------------------------------------";
    }   else {
        qDebug() << "Nothing to read. Maybe this device is not supporting.";
    }

}

void SVClient::slotUISearch()   {
    qDebug() << "Searching...";
        QList<QString> addressList;
        /*
        foreach (const QHostAddress &a, QNetworkInterface::allAddresses()) {
            if (a.isGlobal() || a.isLoopback())
                addressList.push_back(a.toString());
        }*/
        foreach(const QNetworkInterface &interface, QNetworkInterface::allInterfaces()) {
            if (interface.type() == QNetworkInterface::Loopback || interface.type() == QNetworkInterface::Ethernet) {
                foreach (const QNetworkAddressEntry &addressEntry, interface.addressEntries())   {
                    QHostAddress address = addressEntry.ip();
                    if (address.isGlobal()) {
                        addressList.push_back(interface.addressEntries().first().ip().toString());
                        break;
                    }
                }
            }
        }
        addressList.push_back("127.0.0.1");

        emit signalUIAddresses(addressList);
}

void SVClient::slotUIConnect(QString const& address, quint16 const& port) {
    if (connected)
        disconnectFromHost();
    connectToHost(address, port);
}

void SVClient::slotUIDisconnect()   {
    disconnectFromHost();
}

void SVClient::slotUICommand(TaskPackage const& task)   {
    sendData(task.toBytes());
}

void SVClient::slotUISettingsLoad(SetPackage const& set)    {
    sendData(set.toBytes());
}

void SVClient::slotUISettingsUpload()   {
    SetRequestPackage request;
    sendData(request.toBytes());
}
