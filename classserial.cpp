#include "classserial.h"

//initialize variabel Serial Port
QSerialPort* ClassSerial::Serial;
QByteArray ClassSerial::receivedData;

QByteArray ClassSerial::triggerData = QByteArray::fromHex("020004E101");
QByteArray ClassSerial::inData = QByteArray::fromHex("0100E5");
QByteArray ClassSerial::outData = QByteArray::fromHex("0200E6");

QString ClassSerial::StatusMessage;
int ClassSerial::statusTrigger = 0;


ClassSerial::ClassSerial()
{
    Serial = new QSerialPort(Serial);
}

bool ClassSerial::Serial_Connect(QString PortName, qint32 Baudrate)
{
     //Initialize Serial Port Settings
    Serial->setPortName(PortName);
    Serial->setBaudRate(Baudrate);
    Serial->setDataBits(QSerialPort::Data8);
    Serial->setParity(QSerialPort::NoParity);
    Serial->setStopBits(QSerialPort::OneStop);
    Serial->setFlowControl(QSerialPort::NoFlowControl);

    if(!Serial->isOpen()){

        //Validation if Serial is Can Opened
        if(Serial->open(QIODevice::ReadWrite))
        {
            //disable DTR & RTS
            Serial->setDataTerminalReady(false);
            Serial->setRequestToSend(false);
            QObject::connect(Serial, SIGNAL(readyRead()),
                             this, SLOT(Event_SerialReceiveData()),Qt::QueuedConnection);
            StatusMessage = "OK";
            return true;
        }
        else
        {
            StatusMessage = "Failed Open " + Serial->portName() + " - " + Serial->errorString();
        }
    }
    else
    {
        StatusMessage =  "Port " + Serial->portName() + "  Is Already Opened";
        return true;
    }
    return false;
}

void ClassSerial::Serial_Disconnect()
{
    Serial->close();
}

//Thread
ReceiveThread::ReceiveThread(QObject *parent) : QThread((parent))
{

}

void ReceiveThread::run()
{
    MainWindow::DisplayStatus statusTrigger = MainWindow::Standby;
    while(ClassSerial::Serial->isOpen())
    {
        if(ClassSerial::receivedData.length() >= 8)
        {
            if(static_cast<quint8>(ClassSerial::receivedData[0]) == ClassSerial::triggerData[0] &&
               static_cast<quint8>(ClassSerial::receivedData[1]) == ClassSerial::triggerData[1] &&
               static_cast<quint8>(ClassSerial::receivedData[2]) == ClassSerial::triggerData[2] &&
               static_cast<quint8>(ClassSerial::receivedData[3]) == ClassSerial::triggerData[3] &&
               static_cast<quint8>(ClassSerial::receivedData[4]) == ClassSerial::triggerData[4])
            {

                if(static_cast<quint8>(ClassSerial::receivedData[5]) == ClassSerial::inData[0] &&
                   static_cast<quint8>(ClassSerial::receivedData[6]) == ClassSerial::inData[1] &&
                   static_cast<quint8>(ClassSerial::receivedData[7]) == ClassSerial::inData[2])
                {
                    statusTrigger = MainWindow::In;
                }
                else if (static_cast<quint8>(ClassSerial::receivedData[5]) == ClassSerial::outData[0] &&
                         static_cast<quint8>(ClassSerial::receivedData[6]) == ClassSerial::outData[1] &&
                         static_cast<quint8>(ClassSerial::receivedData[7]) == ClassSerial::outData[2])
                {
                    statusTrigger = MainWindow::Out;
                }

                ClassSerial::receivedData.clear();
                emit ReceiveDataProcess(statusTrigger);
            }
        }
    }
}

void ClassSerial::Event_SerialReceiveData()
{
    //Must have delay before receive data
    QThread::msleep(5);

    // Read all available data
    receivedData = Serial->readAll();
}
