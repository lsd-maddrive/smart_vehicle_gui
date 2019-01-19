#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStatusBar>
#include <QLabel>
#include <QTextBrowser>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QTimer>
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QSpinBox>
#include "addressvalidator.h"

class MainWindow : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout *layout;
        QGroupBox *connectionBox;
            QGridLayout *connectionLayout;
                QLabel *addressLabel;
                QLineEdit *addressLine;
                QLabel *portLabel;
                QLineEdit *portLine;
                QPushButton *connectButton;

        QGroupBox *serverBox;
            QGridLayout *serverLayout;
                QLineEdit *messageLine;
                QPushButton *sendButton;
                QPushButton *answerButton;
                QLabel *encoderLabel;
                QLabel *potentiometerLabel;
                QSpinBox *encoderSpin;
                QSpinBox *potentiometerSpin;
                QPushButton *dataButton;

    QPlainTextEdit *log;
    QStatusBar *statusBar;

    QTimer *refreshTimer;

    AddressValidator *addressValidator;
    PortValidator *portValidator;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void slotConnectButton();
    void slotSendButton();
    void slotAnswerButton();
    void slotDataButton();
public slots:
    void slotLog(QString message);
    void slotServerChangeState(bool state);
    void slotRefreshData();
signals:
    void signalServerStart(QString adress = "0.0.0.0", quint16 port = 80);
    void signalServerStop();
    void signalServerSendAll(QString data);
    void signalServerTestAnswer();
    void signalServerTestData(qint32 encoderValue, qint32 potentiometerValue);
};

#endif // MAINWINDOW_H
