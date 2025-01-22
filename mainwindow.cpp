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


    GetConfig();
    InitUI();


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

void MainWindow::InitUI()
{
    QMovie *img_idle = new QMovie(config.imagePath+config.imageIdleName);
    QMovie *img_success_in = new QMovie(config.imagePath+config.imageInName);
    QMovie *img_success_out = new QMovie(config.imagePath+config.imageOutName);

    ui->image_idle->setMovie(img_idle);
    ui->image_success_in->setMovie(img_success_in);
    ui->image_success_out->setMovie(img_success_out);

    img_idle->start();
    img_success_in->start();
    img_success_out->start();

    ui->image_idle->setAttribute(Qt::WA_TranslucentBackground, true);
    ui->image_success_in->setAttribute(Qt::WA_TranslucentBackground, true);
    ui->image_success_out->setAttribute(Qt::WA_TranslucentBackground, true);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    this->setStyleSheet("background:rgb(255,255,255);");

    connect(ui->pb_gatein, &QPushButton::clicked, this, &MainWindow::onButtonEntryClicked);
    connect(ui->pb_gateout, &QPushButton::clicked, this, &MainWindow::onButtonExitClicked);
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

void MainWindow::ReceiveDataOutput(qint32 StatusTrigger)
{
    DisplayStatus sts = static_cast<DisplayStatus>(StatusTrigger);
    SetLCDStatus(sts);
}

void MainWindow::SetLCDStatus(MainWindow::DisplayStatus StatusTrigger)
{
    switch (StatusTrigger) {
    case In:
        ui->image_idle->hide();
        ui->image_success_in->show();
        ui->image_success_out->hide();

        LibUtility.PlayMusicFile(config.soundPath+config.soundInName);

        targetTimeStandby = QDateTime::currentDateTime().addMSecs(config.intervalToStandby);
        if(!tmrIntervalStandby->isActive()){
            tmrIntervalStandby->start(tmrInterval);
        }
        break;
    case Out:
        ui->image_idle->hide();
        ui->image_success_in->hide();
        ui->image_success_out->show();

        LibUtility.PlayMusicFile(config.soundPath+config.soundOutName);

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

        if(tmrIntervalStandby->isActive()){
            tmrIntervalStandby->stop();
        }
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
    config.imageIdleName = settings.value("Image/IdleImageName", "").toString();
    config.imageInName = settings.value("Image/InImageName", "").toString();
    config.imageOutName = settings.value("Image/OutImageName", "").toString();

    config.soundPath = settings.value("Sound/SoundPath", "").toString();
    config.soundInName = settings.value("Sound/InSoundName", "").toString();
    config.soundOutName = settings.value("Sound/OutSoundName", "").toString();
}


void MainWindow::onButtonEntryClicked()
{
    SetLCDStatus(DisplayStatus::In);
}

void MainWindow::onButtonExitClicked()
{
    SetLCDStatus(DisplayStatus::Out);
}
