#include <QFile>
#include <QDebug>
#include <QRegExpValidator>
#include <QMessageBox>
#include "myinfo.h"
#include "global.h"

MyInfo::MyInfo(QWidget *parent, QString uid) :
    QDialog(parent),Uid(uid)
{
   // qDebug()<<"1";
    QFile pf("C:/QT/projects/trading_platform/trading_platform/Info/user.txt");
    if(!pf.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"Fail to open file";
        exit(0);
    }

    setFixedSize(INFO_WINDOW_WIDTH, INFO_WINDOW_HEIGHT);
    setWindowTitle("淘淘");
    setWindowIcon(QIcon(":/image/icon.jpg"));

  //  qDebug()<<"2";
    Name = new QLabel(this);
    Name->setText(tr("用户名"));
    Name->setGeometry(QRect(40,20,70,30));

    Phone = new QLabel(this);
    Phone->setText(tr("联系方式"));
    Phone->setGeometry(QRect(40,60,70,30));

    Address = new QLabel(this);
    Address->setText(tr("地址"));
    Address->setGeometry(QRect(40,100,70,30));

    Balance = new QLabel(this);
    Balance->setText(tr("余额"));
    Balance->setGeometry(QRect(40,140,70,30));

    Change = new QPushButton(this);
    Change->setText(tr("修改"));
    Change->setGeometry(QRect(80,180,40,30));

    Recharge = new QPushButton(this);
    Recharge->setText(tr("充值"));
    Recharge->setGeometry(QRect(130,180,40,30));

    Back = new QPushButton(this);
    Back->setText(tr("返回"));
    Back->setGeometry(QRect(180,180,40,30));

  //  qDebug()<<"3";
    QTextStream in(&pf);
    QString line = in.readLine();
    while(!line.isNull()){
        QStringList list = line.split(",");
        if(list[0] == Uid){
            Name_E = new QLineEdit(this);
            Name_E->setText(list[1]);
            Name_E->setGeometry(QRect(120,20,70,30));
            QRegExpValidator * val1= new QRegExpValidator(QRegExp("[a-zA-Z\u4e00-\u9fa5]{1,10}$"));
            Name_E->setValidator(val1);
            Name_E->setEnabled(false);

            Phone_E = new QLineEdit(this);
            Phone_E->setText(list[3]);
            Phone_E->setGeometry(QRect(120,60,70,30));
            QRegExpValidator * val2= new QRegExpValidator(QRegExp("[0-9]{1,20}$"));
            Phone_E->setValidator(val2);
            Phone_E->setEnabled(false);

            Address_E = new QLineEdit(this);
            Address_E->setText(list[4]);
            Address_E->setGeometry(QRect(120,100,70,30));
            QRegExpValidator * val3= new QRegExpValidator(QRegExp("[a-zA-Z\u4e00-\u9fa5]{1,20}$"));
            Address_E->setValidator(val3);
            Address_E->setEnabled(false);

            Balance_E = new QLineEdit(this);
            Balance_E->setText(list[5]);
            Balance_E->setGeometry(QRect(120,140,70,30));
            Balance_E->setEnabled(false);

            break;
        }
        line = in.readLine();
    }
    pf.close();

    //background
    QPixmap background1;
    background1.load(":/image/background1.jpg");
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(background1));
    this->setPalette(palette);

    connect(Change,SIGNAL(clicked()),this,SLOT(change()));
    connect(Back,SIGNAL(clicked()),this,SLOT(back()));
}

MyInfo::~MyInfo()
{
    delete Name;
    delete Phone;
    delete Address;
    delete Balance;
    delete Name_E;
    delete Phone_E;
    delete Address_E;
    delete Balance_E;
}

void MyInfo::change(){
    if(Change->text()==tr("修改")){
        Name_E->setEnabled(true);
        Phone_E->setEnabled(true);
        Address_E->setEnabled(true);
        Change->setText(tr("确定"));
    }
    else{
        Name_E->setEnabled(false);
        Phone_E->setEnabled(false);
        Address_E->setEnabled(false);
        QFile pf("C:/QT/projects/trading_platform/trading_platform/Info/user.txt");
        if(!pf.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug()<<"Fail to open file";
            exit(0);
        }
        QTextStream in(&pf);
        QStringList infos;
        QString line = in.readLine();
        while(!line.isEmpty()){
            QStringList list = line.split(",");
            if(list[0]==Uid){
             //   qDebug()<<"1";
                infos<<(list[0]+","+Name_E->text()+","+list[2]+","+Phone_E->text()+","+Address_E->text()+","+list[5]+","+list[6]+"\n");
            }
            else{
                infos<<line;
            }
            line = in.readLine();
        }
        pf.close();
        if(!pf.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)){
            qDebug()<<"Fail to open file";
            exit(0);
        }
        QTextStream out(&pf);
        for(int i=0;i<infos.size();i++){
            QString tmp = infos[i];
            out<<tmp<<"\n";
        }
        pf.close();
        QMessageBox tip;
        tip.setText(tr("修改成功！"));
        tip.exec();
    }

}

void MyInfo::recharge(){

}

void MyInfo::back(){
    this->close();
}
