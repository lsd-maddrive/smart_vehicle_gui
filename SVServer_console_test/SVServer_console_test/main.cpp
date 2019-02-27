#include <QCoreApplication>
#include <svserver.h>
#include <QTime>
#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SVServer server;
    server.start(QHostAddress("127.0.0.1"), 5556);

    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));

    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [&server] {
        DataPackage data;

        data.m_encoderValue = qrand() % 20 - 10;
        data.m_steeringAngle = qrand() % 20 - 10;
        data.m_compBatteryPerc = qrand() % 100;
        data.m_motorBatteryPerc = qrand() % 100;

        server.slotSendData(data);
    });
    timer->start(50); // <- delay between sending

    return a.exec();
}
