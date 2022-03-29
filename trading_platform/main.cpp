#include "login.h"

#include <QApplication>
#include <QTextCodec>
#include <QDebug>
#include <QDir>
int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    Login w;
    w.show();
    return a.exec();
}




