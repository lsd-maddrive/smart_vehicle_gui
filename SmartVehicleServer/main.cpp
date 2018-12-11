#include <QCoreApplication>
#include "svserver.h"
#include "consoleinterface.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ConsoleInterface *console = new ConsoleInterface();

    SVServer server(console);
    server.start();

    return a.exec();
}
