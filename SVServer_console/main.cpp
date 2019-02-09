#include <QCoreApplication>
#include <iostream>
#include <svserver.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SVServer server;
    server.start(QHostAddress("192.168.31.56"), 5555);

    DataPackage data( DataPackage::WAIT );
    data.m_encoderValue = 100;

    server.sendData( data );
    server.disconnect();

    return a.exec();
}
