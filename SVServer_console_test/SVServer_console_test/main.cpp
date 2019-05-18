#include <QCoreApplication>
#include <svserver.h>
#include <QTime>
#include <QTimer>

#include <cmath>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SVServer server;
    bool result = server.start(QHostAddress("0.0.0.0"), 5556);

    MapPackage map({{1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 1, 1, 1, 1, 0, 1},
                    {1, 0, 1, 0, 0, 1, 0, 1},
                    {1, 0, 1, 0, 0, 0, 0, 1},
                    {1, 0, 1, 1, 1, 1, 1, 1}});

    if (result) {
        QTime midnight(0,0,0);
        qsrand(midnight.secsTo(QTime::currentTime()));

        static float t = 0;
        static float x = 0;
        static float angle = 0;

        QObject::connect(&server, &SVServer::signalNewConnection, [&server, &map] {
            server.slotSendMap(map);
        });

        QTimer *timerHighFreq = new QTimer();
        QObject::connect(timerHighFreq, &QTimer::timeout, [&server] {
            HighFreqDataPackage data;
            t += 0.01f;
            float v = sin(t) * 15;
            //x += 0.1f + (qrand() % 100 - 50) / 100;
            x += 0.1f;
            angle += 1;

            data.m_encoderValue = x;
            data.m_steeringAngle = v;
            data.x = 1.5;
            data.y = 2.5;
            data.angle = angle;

            server.slotSendHighFreqData(data);

        });
        timerHighFreq->start(50); // <- delay between sending

        QTimer *timerLowFreq = new QTimer();
        QObject::connect(timerLowFreq, &QTimer::timeout, [&server] {
            LowFreqDataPackage data;

            data.stateType = LowFreqDataPackage::State::WAIT;
            data.m_compBatteryPerc = qrand() % 100;
            data.m_motorBatteryPerc = qrand() % 100;
            data.m_temp = qrand() % 100;

            server.slotSendLowFreqData(data);
        });
        timerLowFreq->start(1000); // <- delay between sending

    }

    return a.exec();
}
