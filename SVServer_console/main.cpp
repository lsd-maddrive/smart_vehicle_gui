#include <QCoreApplication>
#include <iostream>
#include "../SVServer/svserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SVServer server;
    server.start();

    /*
    server.sendData( state , encoder, potentiometer, battery1, battery2);
    server.disconnect();
    */
    return a.exec();
}
