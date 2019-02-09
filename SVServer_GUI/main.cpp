#include "mainwindow.h"
#include <QApplication>
#include "svserver.h"
#include "datapackage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    QObject *ui = &w;

    SVServer *server = new SVServer();

    QObject::connect(server, SIGNAL(signalUILog(QString)),
                     ui, SLOT(slotLog(QString)));
    QObject::connect(server, SIGNAL(signalUIChangeState(bool)),
                     ui, SLOT(slotServerChangeState(bool)));
    QObject::connect(ui, SIGNAL(signalServerStart(QString, quint16)),
                     server, SLOT(slotUIStart(QString, quint16)));
    QObject::connect(ui, SIGNAL(signalServerStop()),
                     server, SLOT(slotUIStop()));
    QObject::connect(ui, SIGNAL(signalServerSendAll(QString)),
                     server, SLOT(slotUISendAll(QString)));
    QObject::connect(ui, SIGNAL(signalServerTestAnswer()),
                     server, SLOT(slotUITestAnswer()));

    QObject::connect(ui, SIGNAL(signalSendData(DataPackage const&)),
                     server, SLOT(sendData(DataPackage const&)));

    return a.exec();
} 
