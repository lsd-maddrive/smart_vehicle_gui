#include "consoleinterface.h"

const QString ConsoleInterface::Commands::HELP = "help";
const QString ConsoleInterface::Commands::EXIT = "exit";
const QString ConsoleInterface::Commands::START = "start";
const QString ConsoleInterface::Commands::STOP = "stop";
const QString ConsoleInterface::Commands::SENDALL = "sendAll";


ConsoleInterface::ConsoleInterface()
{
    cout = new QTextStream(stdout);
    cin = new QTextStream(stdin);
    print("Smart Vehicle control system (server) v0.1");
    print("Speedwagon, 2018");
    print("Console is ready. Type 'help' to show command list.");
    printLine();
}

ConsoleInterface::~ConsoleInterface()   {
    print("Console closing...");
    delete cout;
    delete cin;
}

void ConsoleInterface::print(QString const& message)    {
    (*cout) << message << endl;
}

void ConsoleInterface::printLine()  {
    print("--------------------------------------------------------------------------------------------");
}

void ConsoleInterface::listen() {
    listening = true;
    while (listening)   {
        (*cout) << ">";
        cout->flush();
        QString command = cin->readLine();

        while (command.endsWith(' '))
            command.chop(1);

        if (command == Commands::EXIT)  {
            print("Closing application...");
            print("If this window still open plz push any button. I don't know why it don't want to closing :(");
            exit(0);
        }

        if (command == Commands::HELP)  {
            printLine();
            print("You can use following commands:");
            print(9 + Commands::HELP + " - to show command list");
            print(9 + Commands::EXIT + " - to close the application");
            print(9 + Commands::START + " - to start the server and start listening incomming connections");
            print(9 + Commands::STOP + " - to stop the server and close all connections");
            print(9 + Commands::SENDALL + " + [message] - to send [message] to all connected clients");
            printLine();
            continue;
        }

        if (command == Commands::START) {
            emit signalConsoleStart();
            continue;
        }

        if (command == Commands::STOP)  {
            emit signalConsoleStop();
            continue;
        }

        if (command.startsWith(Commands::SENDALL + ' '))  {
            QString message = command.section(' ', 1);
            emit signalConsoleSend(message);
            continue;
        }

        print("Unknown command: " + command);
    }
}

bool ConsoleInterface::isListening() const  {
    return listening;
}

void ConsoleInterface::slotConsoleMessage(QString message)   {
    print(message);
}
