#include "mainwindow.h"
#include "ui_mainwindow.h"

//initialize library
ClassSerial libSerial;
ClassUtility LibUtility;
ReceiveThread *Thread;

//config
MainWindow::ConfigData config;
int tmrInterval = 200;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    GetConfig();

    Thread = new ReceiveThread(this);
    connect(Thread, SIGNAL(ReceiveDataProcess(qint32)),
                this,SLOT(ReceiveDataOutput(qint32)));

    CheckSerial();

    tmrIntervalStandby = new QTimer(this);
    connect(tmrIntervalStandby, SIGNAL(timeout()), this, SLOT(IntervalToStandby()));

    SetLCDStatus(Standby);

}

MainWindow::~MainWindow()
{
    libSerial.Serial_Disconnect();
    Thread->stop = true;
    if(tmrIntervalStandby->isActive()) tmrIntervalStandby->stop();

    delete ui;
}


void MainWindow::CheckSerial()
{
    if(!libSerial.Serial->isOpen())
    {
        bool ret = libSerial.Serial_Connect(config.serialPortName, config.serialBaudrate);
        if(ret)
        {
            //subscribe event receive data
            if(!Thread->isRunning()) Thread->start();
        }
    }
}

void MainWindow::ReceiveDataOutput(MainWindow::DisplayStatus StatusTrigger)
{
    SetLCDStatus(StatusTrigger);
}

void MainWindow::SetLCDStatus(MainWindow::DisplayStatus StatusTrigger)
{
    switch (StatusTrigger) {
    case In:
        ui->image_idle->hide();
        ui->image_success_in->show();
        ui->image_success_out->hide();

        targetTimeStandby = QDateTime::currentDateTime().addMSecs(config.intervalToStandby);
        if(!tmrIntervalStandby->isActive()){
            tmrIntervalStandby->start(tmrInterval);
        }
        break;
    case Out:
        ui->image_idle->hide();
        ui->image_success_in->show();
        ui->image_success_out->hide();

        targetTimeStandby = QDateTime::currentDateTime().addMSecs(config.intervalToStandby);
        if(!tmrIntervalStandby->isActive()){
            tmrIntervalStandby->start(tmrInterval);
        }
        break;
    default:
        ui->image_idle->show();
        ui->image_success_in->hide();
        ui->image_success_out->hide();

        break;
    }
}

void MainWindow::IntervalToStandby()
{
    if(QDateTime::currentDateTime()> targetTimeStandby)
    {
        SetLCDStatus(Standby);
    }

    if(tmrIntervalStandby->isActive()){
        tmrIntervalStandby->stop();
    }
}

//Function Get Config from .ini file
void MainWindow::GetConfig()
{
    QString FileDir = QApplication::applicationDirPath() + "/config.ini";
    QSettings settings(FileDir, QSettings::IniFormat);

    //UI
    config.intervalToStandby = settings.value("IntervalToStandby", "").toInt();

    //Serial
    config.serialPortName = settings.value("Serial/Port", "").toString();
    config.serialBaudrate = settings.value("Serial/Baudrate", "").toInt();

    //Image & Gif
    config.imagePath = settings.value("Image/ImagePath", "").toString();
    config.imageInName = settings.value("Image/InImageName", "").toString();
    config.imageOutName = settings.value("Image/OutImageName", "").toString();

    config.soundPath = settings.value("Sound/SoundPath", "").toString();
    config.soundInName = settings.value("Sound/InSoundName", "").toString();
    config.soundOutName = settings.value("Sound/OutSoundName", "").toString();
}
