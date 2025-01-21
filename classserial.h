#ifndef CLASSSERIAL_H
#define CLASSSERIAL_H

#include <QObject>
#include <QWidget>
#include <mainwindow.h>

//add library serial port
#include<QtSerialPort/QSerialPort>

//add library timer & thread
#include <QTimer>
#include <QThread>

class ClassSerial :public QObject
{
    Q_OBJECT
public:
    ClassSerial();

    //Variabel message global & data serial yang diterima
    static QString StatusMessage;
    static QByteArray receivedData;
    static int statusTrigger;

    //variabel buff data serial
    static QSerialPort* Serial;

    //function Connect & Disconnect Serial Port
    bool Serial_Connect(QString, qint32);
    void Serial_Disconnect();


    QTimer *TimerTimeout;

    static QByteArray triggerData;
    static QByteArray inData;
    static QByteArray outData;

private slots:
    void Event_SerialReceiveData();
};

//Class untuk thread
class ReceiveThread : public QThread
{
    Q_OBJECT
public :
    explicit ReceiveThread(QObject *parent = nullptr); //QObject *parent = 0
    void run();
    bool stop;

signals:
    void ReceiveDataProcess(MainWindow::DisplayStatus);

public slots:

};

#endif // CLASSSERIAL_H
