#include <QFile>
#include <QDebug>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QDateTime>
#include "command.h"
#include "modify_screen.h"
#include "global.h"
Modify_Screen::Modify_Screen(QWidget *parent,QString mid) :
    QDialog(parent),Mid(mid)
{
    setFixedSize(INFO_WINDOW_WIDTH, INFO_WINDOW_HEIGHT);
    setWindowTitle("淘淘");
    setWindowIcon(QIcon(":/image/icon.jpg"));

    name = new QLabel(this);
    name->setText(tr("商品名"));
    name->setGeometry(QRect(40,20,70,60));

    price = new QLabel(this);
    price->setText(tr("价格"));
    price->setGeometry(QRect(40,90,70,60));

    describe = new QLabel(this);
    describe->setText(tr("描述"));
    describe->setGeometry(QRect(40,160,70,60));

    change = new QPushButton(this);
    change->setText(tr("修改"));
    change->setGeometry(QRect(80,230,100,60));

    back = new QPushButton(this);
    back->setText(tr("返回"));
    back->setGeometry(QRect(200,230,100,60));

    QFile pf(DIR + "commodity.txt");
    if(!pf.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"Fail to open file";
        exit(0);
    }

   QTextStream in(&pf);
   QString line = in.readLine();
   while(!line.isNull()){
       QStringList list = line.split(",");
       if(list[0] == Mid){
           name_E = new QLineEdit(this);
           name_E->setText(list[1]);
           name_E->setGeometry(QRect(120,20,200,60));
           name_E->setEnabled(false);

           price_E = new QLineEdit(this);
           price_E->setText(list[2]);
           price_E->setGeometry(QRect(120,90,200,60));
           QRegExpValidator * val2= new QRegExpValidator(QRegExp("[0-9]{1,50}(\\.[0-9])?$"));
           price_E->setValidator(val2);
           price_E->setEnabled(false);

           describe_E = new QLineEdit(this);
           describe_E->setText(list[4]);
           describe_E->setGeometry(QRect(120,160,200,60));
           QRegExpValidator * val3= new QRegExpValidator(QRegExp("[a-zA-Z\u4e00-\u9fa50-9]{1,20}$"));
           describe_E->setValidator(val3);
           describe_E->setEnabled(false);

           break;
       }
       line = in.readLine();
   }
   pf.close();

   QPixmap background1;
   background1.load(":/image/background1.jpg");
   QPalette palette(this->palette());
   palette.setBrush(QPalette::Background, QBrush(background1));
   this->setPalette(palette);

   connect(change,SIGNAL(clicked()),this,SLOT(Change()));
   connect(back,SIGNAL(clicked()),this,SLOT(Back()));

}

Modify_Screen::~Modify_Screen()
{

}

void Modify_Screen::Change(){
    if(change->text()==tr("修改")){
        price_E->setEnabled(true);
        describe_E->setEnabled(true);
        change->setText(tr("确定"));
    }
    else{
        price_E->setEnabled(false);
        describe_E->setEnabled(false);
        change->setText(tr("修改"));
        if(price_E->text().isEmpty()){
            QFile pf(DIR + "commodity.txt");
            if(!pf.open(QIODevice::ReadOnly | QIODevice::Text)){
                qDebug()<<"Fail to open file";
                exit(0);
            }
            QTextStream in(&pf);
            QString line = in.readLine();
            while(!line.isNull()){
                QStringList list = line.split(",");
                if(list[0] == Mid){
                    name_E->setText(list[1]);
                    price_E->setText(list[2]);
                    describe_E->setText(list[4]);
                    break;
                }
                line = in.readLine();
            }
            pf.close();

            QMessageBox tip;
            tip.setText(tr("价格不能为空！"));
            tip.exec();
            return;
        }
        else{
            QDateTime current_date_time = QDateTime::currentDateTime();
            QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss:");
            QString cmd1 = "UPDATE commodity SET 价格 = " + price_E->text()+" WHERE 商品ID = " + Mid;
            QString cmd2 = "UPDATE commodity SET 描述 = " + describe_E->text()+" WHERE 商品ID = " + Mid;
            QString new_record1 = current_date + " " + cmd1 + "\n";
            QString new_record2 = current_date + " " + cmd2 + "\n";
            QFile pf(DIR + "commands.txt");
            if(!pf.open(QIODevice::WriteOnly | QIODevice::Append)){
                qDebug()<<"打开命令文件失败！";
                exit(0);
            }
            QTextStream out(&pf);
            out<<new_record1<<new_record2;
            pf.close();
            Command CMD("U999S");
            CMD.deal_with_cmd(cmd1);
            CMD.deal_with_cmd(cmd2);
            QMessageBox tip;
            tip.setText(tr("修改成功！"));
            tip.exec();
        }
    }
}

void Modify_Screen::Back(){
    this->close();
}
