#include "svserver.h"

Server::Server(QObject* parent)    {}

SVServer::SVServer()   {
    log("Server initializing...");
    server = new Server(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
    connect(server, SIGNAL(acceptError(QAbstractSocket::SocketError)), this, SLOT(slotAcceptError(QAbstractSocket::SocketError)));
    log("Server is ready.");
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

void SVServer::log(AnswerPackage const& answer)    {
    QString message = "Sending answer package: ";
    message.append("COI: ");
    message.append(QString::number(answer.COI));
    message.append("; Answer type: ");
    message.append(QString::number(answer.answerType));

    log(message);
}

void SVServer::log(MapPackage const& map)  {
    log("Map:");
    for (auto const& line : map.cells())    {
        QString str;
        for (auto const& cell : line)   {
            str.append(QString::number(cell));
            str.append(' ');
        }
        log(str);
    }
}

bool SVServer::start(QHostAddress const& address, quint16 port)   {
    log("Starting server...");
    if (!server->isListening())   {
        QHostAddress currentAddress = address;
        if (address == QHostAddress::Null)  {
            foreach (const QHostAddress &a, QNetworkInterface::allAddresses()) {
                if (a.protocol() == QAbstractSocket::IPv4Protocol && a != QHostAddress(QHostAddress::LocalHost))
                     currentAddress = a;
            }
        }

        bool ready = server->listen(currentAddress, port);
        if (ready)  {
            this->port = port;
            this->address = currentAddress;
            log("Server is listening. Address: " + currentAddress.toString() + ", port " + QString::number(port));
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
        log("Warning! Server is already disabled.");
    }
}

void SVServer::sendAll(QString const& data)    {
    if (server->isListening())   {
        foreach (QTcpSocket* socket, connections)  {
            sendTo(socket, data);
        }
        log("Done.");
    }   else    {
        log("Warning! Server is disabled.");
    }
}

void SVServer::sendAll(QByteArray const& data)    {
    if (server->isListening())   {
        foreach (QTcpSocket* socket, connections)  {
            sendTo(socket, data);
        }
    }   else    {
        log("Warning! Server is disabled.");
    }
}

void SVServer::sendAll(AnswerPackage const &answer) {
    log(answer);
    sendAll(answer.toBytes());
}

void SVServer::sendTo(QTcpSocket* socket, QString const& data)   {
    char *bytes = new char[(size_t) data.size() + 2];
    bytes[0] = (char)data.size();
    for (int i = 0; i < data.size(); i++)    {
        bytes[i + 1] = (char) data.data()[i].toLatin1();
    }
    bytes[data.size() + 1] = '\0';
    socket->write(bytes);
    //log(bytes);

    delete[] bytes;
}

void SVServer::sendTo(QTcpSocket *socket, QByteArray const &data)   {
    QByteArray bytes;
    bytes.append(static_cast<char>(data.size()));
    bytes.append(data);
    socket->write(bytes);
}

void SVServer::sendTo(QTcpSocket *socket, AnswerPackage const &answer)  {
    sendTo(socket, answer.toBytes());
}

void SVServer::sendTo(QTcpSocket *socket, AuthAnswerPackage const& answer) {
    sendTo(socket, answer.toBytes());
}

QHostAddress SVServer::getHostAddress() const    {
    return address;
}

quint16 SVServer::getPort() const   {
    return port;
}

bool SVServer::isListening() const  {
    return server->isListening();
}

int SVServer::activeConnections() const {
    return connections.size();
}

void SVServer::slotNewConnection()  {
    QTcpSocket* newConnection = dynamic_cast<QTcpSocket*>(server->nextPendingConnection());
    log("New connection: socket descriptor " + QString::number(newConnection->socketDescriptor()));
    if (newConnection != nullptr)
        connections.insert(newConnection->socketDescriptor(), newConnection);

    connect(newConnection, SIGNAL(disconnected()), this, SLOT(slotClientDisconnected()));
    connect(newConnection, SIGNAL(readyRead()),this, SLOT(slotReadyRead()));
    connect(newConnection, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotAcceptError(QAbstractSocket::SocketError)));

    emit signalNewConnection(newConnection->socketDescriptor());
}

void SVServer::slotAcceptError(QAbstractSocket::SocketError error)    {
    qDebug() << error;
}

void SVServer::slotClientDisconnected() {
    log("Client disconnected");
    QTcpSocket* disconnectedClient = dynamic_cast<QTcpSocket*>(sender());
    connections.remove(connections.key(disconnectedClient));
    emit signalDisconnected(disconnectedClient->socketDescriptor());
    disconnectedClient->deleteLater();
}

void SVServer::slotReadyRead()  {
    log("Incoming data");
    QTcpSocket* client = dynamic_cast<QTcpSocket*>(sender());

    if (client->bytesAvailable())   {
        char blockSize = 0;
        client->read(&blockSize, 1);
        QByteArray bytes = client->read(blockSize);
        QString message(bytes);
        if (message.endsWith("\r\n"))
            message.chop(2);

        log("Data[" + QString::number(blockSize) + "]: " + message);

        if (bytes.at(0) == AuthPackage::packageType)    {
            log("First byte: " + QString::number(bytes[0]));

            if (message.endsWith(validAuthPackage.authRequest)) {
                log("Valid GUI device connected.");
                sendTo(client, AuthAnswerPackage(1, 2, 3));
            }
        }   else
        if (bytes.at(0) == TaskPackage::packageType)    {
            TaskPackage task(bytes);

            log("Task package:");
            log("COI: " + QString::number(task.COI) + "; TaskType: " + QString::number(task.taskType) + "; Parameters:");
            for (float const& param : task.params)
                log(QString::number(param));
            if (!currentTaskCOI)    {
                currentTaskCOI = task.COI;
                switch (task.taskType)  {
                case 1: {
                    emit signalTaskForward(task.params.first());
                    log("Starting task FORWARD...");
                    break;
                }
                case 2: {
                    emit signalTaskWheels(task.params.first());
                    log("Starting task WHEELS");
                    break;
                }
                case 3: {
                    emit signalTaskFlick();
                    log("Starting task FLICK");
                    break;
                }
                }
            }   else {
                log("Vehicle is busy.");
            }
        }   else
        if (bytes.at(0) == SetPackage::packageType)  {
            SetPackage set(bytes);
            emit signalSetSteering(set.steering_p, set.steering_i, set.steering_d, set.steering_servoZero);
            emit signalSetForward(set.forward_p, set.forward_i, set.forward_d, set.forward_int);
            emit signalSetBackward(set.backward_p, set.backward_i, set.backward_d, set.backward_int);
            log("Incoming new settings");
        }   else
        if (bytes.at(0) == SetRequestPackage::packageType)   {
            emit signalUploadSettings();
            log("Incoming settings request");
        }
        else {
            log("Corrupted or illegal package.");
        }
    }
}

void SVServer::slotUIStart(QString adress, quint16 port) {
    start(QHostAddress(adress), port);
}

void SVServer::slotUIStop()    {
    stop();
}

void SVServer::slotUISendAll(QString message) {
    sendAll(message);
}

void SVServer::slotUITestAnswer()   {
    sendAll(AnswerPackage(5, 2));
    currentTaskCOI = 0;
}

void SVServer::slotUITestData(qint32 encoderValue, qint32 potentiometerValue) {
    HighFreqDataPackage data;
    data.m_steeringAngle = potentiometerValue;
    data.m_encoderValue = encoderValue;

    sendAll(data.toBytes());
}

void SVServer::slotTaskDone(quint8 answerType)   {
    sendAll(AnswerPackage(currentTaskCOI, answerType));
    currentTaskCOI = 0;
}

void SVServer::slotSendHighFreqData(HighFreqDataPackage const& data)   {
    sendAll(data.toBytes());
}

void SVServer::slotSendLowFreqData(LowFreqDataPackage const& data)   {
    sendAll(data.toBytes());
}

void SVServer::slotSendSettings(SetPackage const& set)   {
    sendAll(set.toBytes());
}

void SVServer::slotSendMap(MapPackage const& map)  {
    sendAll(map.toBytes());
}
