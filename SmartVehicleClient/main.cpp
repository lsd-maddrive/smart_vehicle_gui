#include <QCoreApplication>

#include "svclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SVClient client;
    client.connectToHost("127.0.0.1", 80);

    return a.exec();
}
