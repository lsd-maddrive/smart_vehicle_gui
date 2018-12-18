#include "mainwindow.h"
#include <QApplication>
#include "svserver.h"
#include "datapackage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    SVServer *server = new SVServer();

    QObject::connect(server, SIGNAL(signalUILog(QString)), &w, SLOT(slotLog(QString)));
    QObject::connect(server, SIGNAL(signalUIChangeState(bool)), &w, SLOT(slotServerChangeState(bool)));
    QObject::connect(&w, SIGNAL(signalServerStart(QString, quint16)), server, SLOT(slotUIStart(QString, quint16)));
    QObject::connect(&w, SIGNAL(signalServerStop()), server, SLOT(slotUIStop()));
    QObject::connect(&w, SIGNAL(signalServerSendAll(QString)), server, SLOT(slotUISendAll(QString)));
    QObject::connect(&w, SIGNAL(signalServerTestSend(QString)), server, SLOT(slotUITestSend(QString)));

    return a.exec();
}
