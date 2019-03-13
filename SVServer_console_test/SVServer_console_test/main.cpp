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

    static float t = 0;

    MapPackage map({{1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 1, 1, 1, 1, 0, 1},
                    {1, 0, 1, 0, 0, 1, 0, 1},
                    {1, 0, 1, 0, 0, 0, 0, 1},
                    {1, 0, 1, 1, 1, 1, 1, 1}});

    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [&server, &map] {
        DataPackage data;
        t += 0.01f;
        float v = sin(t) * 15;

        data.m_encoderValue = v;
        data.m_steeringAngle = v;
        data.m_compBatteryPerc = qrand() % 100;
        data.m_motorBatteryPerc = qrand() % 100;

        server.slotSendData(data);
        server.slotSendMap(map);
    });
    timer->start(50); // <- delay between sending

    return a.exec();
}
