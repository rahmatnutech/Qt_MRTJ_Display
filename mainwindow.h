#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QDateTime>

//panggil header serial
#include "classserial.h"

//panggil header logging
#include "classutility.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    struct ConfigData
    {
        qint32 intervalToStandby;

        QString serialPortName;
        qint32 serialBaudrate;

        QString imagePath;
        QString imageInName;
        QString imageOutName;

        QString soundPath;
        QString soundInName;
        QString soundOutName;
    };

    enum DisplayStatus{
        Standby,
        In,
        Out
    };

private:
    Ui::MainWindow *ui;

    QTimer* tmrIntervalStandby;
    QDateTime targetTimeStandby;

    void GetConfig();
    void CheckSerial();

public slots:
    void ReceiveDataOutput(DisplayStatus);
    void IntervalToStandby();

private slots:
    void SetLCDStatus(DisplayStatus);

};
#endif // MAINWINDOW_H
