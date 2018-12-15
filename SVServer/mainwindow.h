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
public slots:
    void slotLog(QString message);
    void slotServerChangeState(bool state);
    void slotRefreshData();
signals:
    void signalServerStart(QString adress = "0.0.0.0", quint16 port = 80);
    void signalServerStop();
    void signalServerSendAll(QString data);
};

#endif // MAINWINDOW_H
