#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    addressValidator = new AddressValidator();
    portValidator = new PortValidator();

    layout = new QVBoxLayout();
    {
        connectionBox = new QGroupBox("Connection");
        {
            connectionLayout = new QGridLayout();
            connectionLayout->setAlignment(Qt::AlignCenter);
            {
                addressLabel = new QLabel("Server adress");
                connectionLayout->addWidget(addressLabel, 0, 0);

                addressLine = new QLineEdit("127.0.0.1");
                addressLine->setPlaceholderText("Enter server adress here...");
                addressLine->setValidator(addressValidator);
                connectionLayout->addWidget(addressLine, 0, 1);

                portLabel = new QLabel("Port");
                connectionLayout->addWidget(portLabel, 1, 0);

                portLine = new QLineEdit("80");
                portLine->setPlaceholderText("Server port...");
                portLine->setValidator(portValidator);
                connectionLayout->addWidget(portLine, 1, 1);

                connectButton = new QPushButton("Start");
                connectionLayout->addWidget(connectButton, 2, 1, 1, 2);
            }
            connectionBox->setLayout(connectionLayout);
        }
    }
    layout->addWidget(connectionBox);
    {
        serverBox = new QGroupBox("Server");
        {
            serverLayout = new QGridLayout();
            serverLayout->setAlignment(Qt::AlignCenter);
            {

                messageLine = new QLineEdit();
                messageLine->setPlaceholderText("Enter message here...");
                serverLayout->addWidget(messageLine, 0, 0, 1, 1);

                sendButton = new QPushButton("Send");
                serverLayout->addWidget(sendButton, 0, 1, 1, 1);

                answerButton = new QPushButton("Send answer");
                serverLayout->addWidget(answerButton, 1, 0, 1, 2);

                encoderLabel = new QLabel("Encoder value");
                serverLayout->addWidget(encoderLabel, 2, 0, 1, 1);

                potentiometerLabel = new QLabel("Potentiometer value");
                serverLayout->addWidget(potentiometerLabel, 2, 1, 1, 1);

                encoderSpin = new QSpinBox();
                encoderSpin->setRange(-std::numeric_limits<qint32>::max(), std::numeric_limits<qint32>::max());
                encoderSpin->setValue(0);
                serverLayout->addWidget(encoderSpin, 3, 0, 1, 1);

                potentiometerSpin = new QSpinBox();
                potentiometerSpin->setRange(-std::numeric_limits<qint32>::max(), std::numeric_limits<qint32>::max());
                potentiometerSpin->setValue(0);
                serverLayout->addWidget(potentiometerSpin, 3, 1, 1, 1);

                dataButton = new QPushButton("Send data");
                serverLayout->addWidget(dataButton, 4, 0, 1, 2);
            }
            serverBox->setLayout(serverLayout);
        }
    }
    layout->addWidget(serverBox);

    log = new QPlainTextEdit("Logs:");
    log->setReadOnly(true);
    layout->addWidget(log);

    setLayout(layout);

    connect(connectButton, SIGNAL(clicked()), this, SLOT(slotConnectButton()));
    connect(sendButton, SIGNAL(clicked()), this, SLOT(slotSendButton()));
    connect(answerButton, SIGNAL(clicked()), this, SLOT(slotAnswerButton()));
    connect(dataButton, SIGNAL(clicked()), this, SLOT(slotDataButton()));

    slotServerChangeState(false);
}

MainWindow::~MainWindow()
{

}

void MainWindow::slotConnectButton()    {
    if (addressLine->isEnabled())    {
        QString address = addressLine->text();
        quint16 port = static_cast<quint16>(portLine->text().toInt());
        if (!AddressValidator::isFull(address))
            QMessageBox::critical(nullptr, "Error", "Incorrect server address.");
        else
            emit signalServerStart(address, port);
    }   else {
        emit signalServerStop();
    }
}

void MainWindow::slotSendButton()   {
    QString data = messageLine->text();
    //validate
    emit signalServerSendAll(data);
    messageLine->clear();
}

void MainWindow::slotAnswerButton() {
    emit signalServerTestAnswer();
}

void MainWindow::slotDataButton()   {
    emit signalServerTestData(encoderSpin->value(), potentiometerSpin->value());
}

void MainWindow::slotLog(QString message)   {
    log->appendPlainText(message);
}

void MainWindow::slotServerChangeState(bool state)    {
    if (state)  {
        connectButton->setText("Stop");
        addressLine->setEnabled(false);
        portLine->setEnabled(false);

        serverBox->setEnabled(true);
    }   else {
        connectButton->setText("Start");
        addressLine->setEnabled(true);
        portLine->setEnabled(true);

        serverBox->setEnabled(false);
    }
}

void MainWindow::slotRefreshData()  {

}
