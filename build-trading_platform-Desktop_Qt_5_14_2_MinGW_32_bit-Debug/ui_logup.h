/********************************************************************************
** Form generated from reading UI file 'logup.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGUP_H
#define UI_LOGUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Logup
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Logup)
    {
        if (Logup->objectName().isEmpty())
            Logup->setObjectName(QString::fromUtf8("Logup"));
        Logup->resize(800, 600);
        menubar = new QMenuBar(Logup);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        Logup->setMenuBar(menubar);
        centralwidget = new QWidget(Logup);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Logup->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(Logup);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Logup->setStatusBar(statusbar);

        retranslateUi(Logup);

        QMetaObject::connectSlotsByName(Logup);
    } // setupUi

    void retranslateUi(QMainWindow *Logup)
    {
        Logup->setWindowTitle(QCoreApplication::translate("Logup", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Logup: public Ui_Logup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGUP_H
