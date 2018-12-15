#include "connectionwindow.h"

ConnectionWindow::ConnectionWindow(QWidget *parent) : QWidget(parent)
{
    qDebug() << "Init connection window";
    setWindowTitle("Connection options");
    setAcceptDrops(true);

    layout = new QGridLayout();

    addressLabel = new QLabel("Server adress");
    layout->addWidget(addressLabel, 0, 0);

    addressLine = new QLineEdit("127.0.0.1");
    addressLine->setPlaceholderText("Type address here...");
    layout->addWidget(addressLine, 0, 1);

    portLabel = new QLabel("Port:");
    layout->addWidget(portLabel, 1, 0);

    portLine = new QLineEdit("80");
    portLine->setPlaceholderText("Type port here...");
    layout->addWidget(portLine, 1, 1);

    connectButton = new QPushButton("Connect");
    layout->addWidget(connectButton, 2, 0, 1, 2);

    setLayout(layout);

    connect(connectButton, SIGNAL(clicked()), this, SLOT(slotConnectButton()));
}

void ConnectionWindow::slotConnectButton()  {
    if (!connected) {
        QString address = addressLine->text();
        //validate
        quint16 port = (quint16)portLine->text().toInt();
        //validate
        emit signalConnect(address, port);
    }   else {
        emit signalDisconnect();
    }
}

void ConnectionWindow::slotConnected()  {
    connectButton->setText("Disconnect");
    connected = true;
}

void ConnectionWindow::slotDisconnected()   {
    connectButton->setText("Connect");
    connected = false;
}

void ConnectionWindow::slotError(QString message)   {
    QMessageBox::critical(nullptr, "Error", message);
}
