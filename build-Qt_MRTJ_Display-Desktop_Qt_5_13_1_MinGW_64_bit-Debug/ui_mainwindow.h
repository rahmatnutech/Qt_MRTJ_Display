/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *image_idle;
    QLabel *image_success_in;
    QLabel *image_success_out;
    QPushButton *pb_gatein;
    QPushButton *pb_gateout;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(480, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        image_idle = new QLabel(centralwidget);
        image_idle->setObjectName(QString::fromUtf8("image_idle"));
        image_idle->setGeometry(QRect(0, 0, 480, 800));
        image_idle->setAlignment(Qt::AlignCenter);
        image_success_in = new QLabel(centralwidget);
        image_success_in->setObjectName(QString::fromUtf8("image_success_in"));
        image_success_in->setGeometry(QRect(0, 0, 480, 800));
        image_success_in->setAlignment(Qt::AlignCenter);
        image_success_out = new QLabel(centralwidget);
        image_success_out->setObjectName(QString::fromUtf8("image_success_out"));
        image_success_out->setGeometry(QRect(0, 0, 480, 800));
        image_success_out->setAlignment(Qt::AlignCenter);
        pb_gatein = new QPushButton(centralwidget);
        pb_gatein->setObjectName(QString::fromUtf8("pb_gatein"));
        pb_gatein->setGeometry(QRect(10, 740, 80, 21));
        pb_gateout = new QPushButton(centralwidget);
        pb_gateout->setObjectName(QString::fromUtf8("pb_gateout"));
        pb_gateout->setGeometry(QRect(10, 770, 80, 21));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        image_idle->setText(QString());
        image_success_in->setText(QString());
        image_success_out->setText(QString());
        pb_gatein->setText(QCoreApplication::translate("MainWindow", "Gate In", nullptr));
        pb_gateout->setText(QCoreApplication::translate("MainWindow", "Gate Out", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
