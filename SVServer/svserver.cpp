#include "svserver.h"

Server::Server(QObject* parent)    {}

//void Server::incomingConnection(qintptr socketDescriptor)   {
//    emit newConnection(socketDescriptor);
//}

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

void SVServer::setUI(QObject const *UI)   {
    log("Setting UI");
    QObject::connect(this, SIGNAL(signalUILog(QString)), UI, SLOT(slotLog(QString)));
    QObject::connect(this, SIGNAL(signalUIChangeState(bool)), UI, SLOT(slotServerChangeState(bool)));
    QObject::connect(UI, SIGNAL(signalServerStart(QString, quint16)), this, SLOT(slotUIStart(QString, quint16)));
    QObject::connect(UI, SIGNAL(signalServerStop()), this, SLOT(slotUIStop()));
    QObject::connect(UI, SIGNAL(signalServerSendAll(QString)), this, SLOT(slotUISendAll(QString)));
    QObject::connect(UI, SIGNAL(signalServerTestAnswer()), this, SLOT(slotUITestAnswer()));
    QObject::connect(UI, SIGNAL(signalServerTestData(qint32, qint32)), this, SLOT(slotUITestData(qint32, qint32)));
    log("Done. UI for server is ready.");
}

void SVServer::log(QString message) {
    QString timedMessage = QTime::currentTime().toString() + ": " + message;
    emit signalUILog(timedMessage);
    qDebug() << timedMessage;
}

void SVServer::log(AnswerPackage answer)    {
    QString message = "Sending answer package: ";
    message.append("COI: ");
    message.append(QString::number(answer.COI));
    message.append("; Answer type: ");
    message.append(QString::number(answer.answerType));

    log(message);
}

void SVServer::log(DataPackage data)    {
    QString message = "Sending data package: ";
    message.append("State type: ");
    message.append(QString::number(data.stateType));
    message.append("; Data block size: ");
    message.append(QString::number(data.dataBlockSize));
    message.append("; Data: ");
    for (int i = 0; i < data.dataBlockSize; i++)    {
//        message.append(" type: " + QString::number(data.data[i].first) + ", value: " + QString::number(data.data[i].second) + "; ");
    }

    log(message);
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
        log("Warning! Server is already disabled,");
    }
}

void SVServer::sendAll(QString const& data)    {
    if (server->isListening())   {
        log("Sending data [" + data + "] to all... (number of clients: " + QString::number(connections.size()) + ")");
        foreach (QTcpSocket* socket, connections)  {
            sendTo(socket, data);
        }
        log("Done.");
    }   else    {
        log("Warning! Server is disabled");
    }
}

void SVServer::sendAll(QByteArray const& data)    {
    if (server->isListening())   {
        log("Sending data [" + QString(data) + "] to all...  (number of clients: " + QString::number(connections.size()) + ")");
        foreach (QTcpSocket* socket, connections)  {
            sendTo(socket, data);
        }
        log("Done.");
    }   else    {
        log("Warning! Server is disabled");
    }
}

void SVServer::sendAll(AnswerPackage const &answer) {
    log(answer);
    sendAll(answer.toBytes());
}

void SVServer::sendAll(DataPackage const &data) {
    log(data);
    sendAll(data.toBytes());
}

void SVServer::sendData(DataPackage const &data)   {
    sendAll(data);
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

void SVServer::sendTo(QTcpSocket *socket, DataPackage const& data) {
    sendTo(socket, data.toBytes());
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

void SVServer::slotNewConnection()  {
    QTcpSocket* newConnection = dynamic_cast<QTcpSocket*>(server->nextPendingConnection());
    log("New connection: " + QString::number(newConnection->socketDescriptor()));
    if (newConnection != nullptr)
        connections.insert(newConnection->socketDescriptor(), newConnection);
    else {
        log("null");
    }
    log("insert");
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
        char size = 0;
        client->read(&size, 1);
        QByteArray bytes = client->readAll();
        QString message(bytes);
        if (message.endsWith("\r\n"))
            message.chop(2);

        log("Data[" + QString::number(size) + "]: " + message);
        log("First byte: " + QString::number(bytes[0]));

        if (bytes.at(0) == AuthPackage::packageType && size == 11)    {
            log("First byte: " + QString::number(bytes[0]));

            if (message.endsWith(validAuthPackage.authRequest)) {
                log("Valid GUI device connected.");
                sendTo(client, AuthAnswerPackage(1, 2, 3));
            }
        }   else
        if (bytes.at(0) == TaskPackage::packageType)    {
            TaskPackage task;
            task.COI = bytes.at(1);
            task.taskType = bytes.at(2);
            task.paramBlockSize = bytes.at(3);
            for (int i = 0; i < task.paramBlockSize; i++)   {
                BI bi = {(unsigned char) bytes.at(4 + i * 4), (unsigned char) bytes.at(5 + i * 4),
                         (unsigned char) bytes.at(6 + i * 4), (unsigned char) bytes.at(7 + i * 4)};
                task.params.push_back(static_cast<qint32>(bi.I));
            }

            log("Task package:");
            log("COI: " + QString::number(task.COI) + "; TaskType: " + QString::number(task.taskType) + "; Parameters:");
            for (qint32 const& param : task.params)
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
            SetPackage set;
            set.COI = bytes.at(1);
            BI bi[4];
            for (int i = 0; i < 4; i++) {
                bi[i] = {(unsigned char) bytes.at(2 + i * 5), (unsigned char) bytes.at(3 + i * 5),
                         (unsigned char) bytes.at(4 + i * 5), (unsigned char) bytes.at(5 + i * 5)};
            }
            set.p = bi[0].I;
            set.i = bi[1].I;
            set.d = bi[2].I;
            set.servoZero = bi[3].I;
            log("Set package:");
            log("COI: " + QString::number(set.COI) + "; Parameters:");
            log("p: " + QString::number(set.p) + ", ");
            log("i: " + QString::number(set.i) + ", ");
            log("d: " + QString::number(set.d) + ", ");
            log("servo zero state: " + QString::number(set.servoZero) + ", ");
            if (!currentTaskCOI)    {
                currentTaskCOI = set.COI;
                emit signalSetPID(set.p, set.i, set.d);
                emit signalSetServoZero(set.servoZero);
            }   else {
                log("Vehicle is busy.");
            }
        }   else {
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
    DataPackage data( DataPackage::State::WAIT );
    data.m_steeringAngle = potentiometerValue;
    data.m_encoderValue = encoderValue;

    sendData(data);
}

void SVServer::slotTaskDone(quint8 answerType)   {
    sendAll(AnswerPackage(currentTaskCOI, answerType));
    currentTaskCOI = 0;
}

void SVServer::slotSendData(DataPackage data)   {
    sendAll(data);
}
