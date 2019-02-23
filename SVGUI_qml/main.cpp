#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include "svclient.h"
#include "adapter.h"

void initConnections(SVClient *client, Adapter *adapter)  {
    QObject::connect(adapter, SIGNAL(signalConnect(QString const&, quint16 const&)), client, SLOT(slotUIConnect(QString const&, quint16 const&)));
    QObject::connect(adapter, SIGNAL(signalDisconnect()), client, SLOT(slotUIDisconnect()));
    QObject::connect(adapter, SIGNAL(signalCommand(TaskPackage const&)), client, SLOT(slotUICommand(TaskPackage const&)));
    QObject::connect(adapter, SIGNAL(signalSearch()), client, SLOT(slotUISearch()));
    QObject::connect(adapter, SIGNAL(signalSettingsLoad(SetPackage const&)), client, SLOT(slotUISettingsLoad(SetPackage const&)));
    QObject::connect(adapter, SIGNAL(signalSettingsUpload()), client, SLOT(slotUISettingsUpload()));

    QObject::connect(client, SIGNAL(signalUIAddresses(QList<QString> const&)), adapter, SLOT(slotAddresses(QList<QString> const&)));
    QObject::connect(client, SIGNAL(signalUIConnected(qint8 const&)), adapter, SLOT(slotConnected(qint8 const&)));
    QObject::connect(client, SIGNAL(signalUIDisconnected()), adapter, SLOT(slotDisconnected()));
    QObject::connect(client, SIGNAL(signalUIError(QString)), adapter, SLOT(slotConnectionError(QString)));
    QObject::connect(client, SIGNAL(signalUIData(DataPackage const&)), adapter, SLOT(slotData(DataPackage const&)));
    QObject::connect(client, SIGNAL(signalUIDone(qint8 const&, qint8 const&)), adapter, SLOT(slotDone(qint8 const&, qint8 const&)));
    QObject::connect(client, SIGNAL(signalUISettings(SetPackage const&)), adapter, SLOT(slotSettings(SetPackage const&)));
}

int main(int argc, char *argv[])
{
    qDebug() << "Application initializing...";
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication guiApp(argc, argv);

    qDebug() << "User interface initializing...";
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    //QQuickView view(QUrl::fromLocalFile("main.qml"));
    QObject *root = engine.rootObjects().first();
    qDebug() << "Done. User interface is ready.";

    SVClient *client = new SVClient();

    Adapter *adapter = new Adapter(root);
    engine.rootContext()->setContextProperty("adapter", adapter);

    initConnections(client, adapter);

    qDebug() << "Done. Aplication has been initialized and ready to work.";
    qDebug() << "----------------------------------------------";

    //view.show();

    return guiApp.exec();
}
