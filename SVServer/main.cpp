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

    server->setUI(&w);

    return a.exec();
}
