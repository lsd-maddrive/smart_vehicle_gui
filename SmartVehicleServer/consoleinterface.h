#ifndef CONSOLEINTERFACE_H
#define CONSOLEINTERFACE_H

#include <QObject>
#include <QTextStream>
#include <QDebug>

class ConsoleInterface : public QObject
{
    Q_OBJECT
private:
    QTextStream *cout;
    QTextStream *cin;
    void print(QString const& message);
    void printLine();
    bool listening = false;

    struct Commands {
        static const QString HELP;
        static const QString EXIT;
        static const QString START;
        static const QString STOP;
        static const QString SENDALL;
    };

public:
    ConsoleInterface();
    ~ConsoleInterface();

    void listen();
    bool isListening() const;
public slots:
    void slotConsoleMessage(QString message);
signals:
    void signalConsoleStart();
    void signalConsoleStop();
    void signalConsoleSend(QString message);
};

#endif // CONSOLEINTERFACE_H
