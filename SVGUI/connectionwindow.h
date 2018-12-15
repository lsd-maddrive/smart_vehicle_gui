#ifndef CONNECTIONWINDOW_H
#define CONNECTIONWINDOW_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

class ConnectionWindow : public QWidget
{
    Q_OBJECT
private:
    QGridLayout *layout;
    QLabel *addressLabel;
    QLineEdit *addressLine;
    QLabel *portLabel;
    QLineEdit *portLine;
    QPushButton *connectButton;

    bool connected = false;
public:
    explicit ConnectionWindow(QWidget *parent = nullptr);

signals:
    void signalConnect(QString address = "127.0.0.1", quint16 port = 80);
    void signalDisconnect();
private slots:
    void slotConnectButton();
public slots:
    void slotConnected();
    void slotDisconnected();
    void slotError(QString message);
};

#endif // CONNECTIONWINDOW_H
