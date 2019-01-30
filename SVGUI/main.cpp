#include "mainwindow.h"
#include <QApplication>
#include "svclient.h"
#include "connectionwindow.h"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    ConnectionWindow connectionWindow;
    connectionWindow.show();

    SVClient *client = new SVClient();

    QObject::connect(&connectionWindow, SIGNAL(signalConnect(QString, quint16)), client, SLOT(slotUIConnect(QString, quint16)));
    QObject::connect(&connectionWindow, SIGNAL(signalDisconnect()), client, SLOT(slotUIDisconnect()));
    QObject::connect(client, SIGNAL(signalUIConnected()), &connectionWindow, SLOT(slotConnected()));
    QObject::connect(client, SIGNAL(signalUIDisconnected()), &connectionWindow, SLOT(slotDisconnected()));
    QObject::connect(client, SIGNAL(signalUIError(QString)), &connectionWindow, SLOT(slotError(QString)));

    return a.exec();
}
