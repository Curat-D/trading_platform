#include <QFile>
#include <QDebug>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QDateTime>
#include "command.h"
#include "release_screen.h"
#include "global.h"

Release_Screen::Release_Screen(QWidget *parent, QString uid) :
    QDialog(parent),Uid(uid)
{
    setFixedSize(INFO_WINDOW_WIDTH, INFO_WINDOW_HEIGHT);
    setWindowTitle("淘淘");
    setWindowIcon(QIcon(":/image/icon.jpg"));

    name = new QLabel(this);
    name->setText(tr("商品名"));
    name->setGeometry(QRect(40,20,70,60));

    name_E = new QLineEdit(this);
    name_E->setPlaceholderText(tr("输入商品名"));
    name_E->setGeometry(QRect(120,20,200,60));
    QRegExpValidator * val= new QRegExpValidator(QRegExp("[a-zA-Z\u4e00-\u9fa50-9]{1,20}$"));
    name_E->setValidator(val);

    price = new QLabel(this);
    price->setText(tr("价格"));
    price->setGeometry(QRect(40,90,70,60));

    price_E = new QLineEdit(this);
    price_E->setPlaceholderText(tr("输入价格"));
    price_E->setGeometry(QRect(120,90,200,60));
    QRegExpValidator * val2= new QRegExpValidator(QRegExp("[0-9]{1,50}(\\.[0-9])?$"));
    price_E->setValidator(val2);

    num = new QLabel(this);
    num->setText(tr("数量"));
    num->setGeometry(QRect(40,160,70,60));

    num_E = new QLineEdit(this);
    num_E->setPlaceholderText(tr("输入数量"));
    num_E->setGeometry(QRect(120,160,200,60));
    QRegExpValidator * val3= new QRegExpValidator(QRegExp("[0-9]{1,20}$"));
    num_E->setValidator(val3);

    describe = new QLabel(this);
    describe->setText(tr("描述"));
    describe->setGeometry(QRect(40,230,70,60));


    describe_E = new QLineEdit(this);
    describe_E->setPlaceholderText(tr("输入描述"));
    describe_E->setGeometry(QRect(120,230,200,60));
    QRegExpValidator * val4= new QRegExpValidator(QRegExp("[a-zA-Z\u4e00-\u9fa50-9]{1,20}$"));
    describe_E->setValidator(val4);

    release = new QPushButton(this);
    release->setText(tr("发布"));
    release->setGeometry(QRect(80,300,100,60));

    back = new QPushButton(this);
    back->setText(tr("返回"));
    back->setGeometry(QRect(200,300,100,60));

    QFile pf(DIR + "commodity.txt");
    if(!pf.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"Fail to open file";
        exit(0);
    }

   int max_mid = -1;
   QTextStream in(&pf);
   QString line = in.readLine();
   while(!line.isNull()){
       QStringList list = line.split(",");
       int id = (list[0].mid(1)).toInt();
       max_mid = max_mid > id ? max_mid : id;
       line = in.readLine();
   }
   pf.close();

   max_mid++;
   QString h = QString::number(max_mid/100);
   QString t = QString::number((max_mid%100)/10);
   QString s = QString::number(max_mid%10);
   Mid = "M" + h + t + s;

   QPixmap background1;
   background1.load(":/image/background1.jpg");
   QPalette palette(this->palette());
   palette.setBrush(QPalette::Background, QBrush(background1));
   this->setPalette(palette);

   connect(release,SIGNAL(clicked()),this,SLOT(Release()));
   connect(back,SIGNAL(clicked()),this,SLOT(Back()));

}

Release_Screen::~Release_Screen()
{

}

void Release_Screen::Release(){
    if(name_E->text().isEmpty()){
        QMessageBox tip;
        tip.setText(tr("商品名不能为空！"));
        tip.exec();
        return ;
    }
    else if(price_E->text().isEmpty()){
        QMessageBox tip;
        tip.setText(tr("价格不能为空！"));
        tip.exec();
        return ;
    }
    else if(num_E->text().isEmpty()){
        QMessageBox tip;
        tip.setText(tr("数量不能为空！"));
        tip.exec();
        return ;
    }

    int num = num_E->text().toInt();
    QString NUM = QString::number(num);
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss:");
    QString cmd = "INSERT INTO commodity VALUES (" + Mid + "," +name_E->text()+","+price_E->text()+","+NUM+","+describe_E->text()+","+Uid+","+current_date_time.toString("yyyy-MM-dd")+","+"销售中\n";
    QString new_record = current_date +" "+cmd+"\n";
    QFile pf(DIR+"commands.txt");
    if(!pf.open(QIODevice::WriteOnly | QIODevice::Append)){
        qDebug()<<"打开命令文件失败！";
        exit(0);
    }
    QTextStream out(&pf);
    out<<new_record;
    pf.close();

    Command CMD(Uid+"S");
    CMD.deal_with_cmd(cmd);
    QMessageBox tip;
    tip.setText(tr("发布成功！"));
    tip.exec();
    this->close();
}

void Release_Screen::Back(){
    this->close();
}
