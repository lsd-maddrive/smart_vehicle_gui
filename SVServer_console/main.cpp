#include <QCoreApplication>
#include <iostream>
#include <svserver.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SVServer server;
    server.start(QHostAddress("127.0.0.1"), 5556);

    DataPackage data( DataPackage::WAIT );
    data.m_encoderValue = 100;

    server.slotSendData( data );
    server.disconnect();

    return a.exec();
}
