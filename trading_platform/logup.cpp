#include <QDebug>
#include <QFile>
#include <QRegExpValidator>
#include <QMessageBox>
#include "logup.h"
#include "login.h"

Logup::Logup(QWidget *parent) :
    QDialog(parent)
{
    //set window
    setFixedSize(LOGIN_WINDOW_WIDTH, LOGIN_WINDOW_HEIGHT);
    setWindowTitle(tr("淘淘"));
    setWindowIcon(QIcon(":/image/icon.jpg"));

    //add label
    photo = new QLabel(this);
    QPixmap pic;
    pic.load(":/image/sign_up.jpg");
    photo->setPixmap(pic);
    photo->setGeometry(QRect(400,70,240,120));

    Name = new QLabel(this);
    Name->setText(tr("用户名"));
    Name->setGeometry(QRect(350,200,70,30));

    Password = new QLabel(this);
    Password->setText(tr("密码"));
    Password->setGeometry(QRect(350,250,70,30));

    //add LineEdit
    name = new QLineEdit(this);
    name->setGeometry(QRect(420,200,200,30));
    QRegExpValidator * val1= new QRegExpValidator(QRegExp("[a-zA-Z\u4e00-\u9fa5]{1,10}$"));//大小写字母中文 10位
    name->setValidator(val1);

    password = new QLineEdit(this);
    password->setGeometry(QRect(420,250,200,30));
    password->setEchoMode(QLineEdit::Password);
    QRegExpValidator * val2= new QRegExpValidator(QRegExp("[a-z0-9]{1,20}$"));//小写字母和数字，20位
    password->setValidator(val2);

    //add button
    sign_up = new QPushButton(this);
    sign_up->setText(tr("注册"));
    sign_up->setGeometry(QRect(420,300,70,30));

    back = new QPushButton(this);
    back->setText(tr("返回"));
    back->setGeometry(QRect(550,300,70,30));

    QPixmap background1;
    background1.load(":/image/background1.jpg");
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(background1));
    this->setPalette(palette);

    connect(back,SIGNAL(clicked()),this,SLOT(log_in()));
    connect(sign_up,SIGNAL(clicked()),this,SLOT(checkAccount()));
}

Logup::~Logup()
{
    delete photo;
    delete Name;
    delete Password;
    delete back;
    delete sign_up;
    delete name;
    delete password;
}

void Logup::log_in(){
    Login* login_screen = new Login;
    login_screen->show();
    this->close();
}

void Logup::checkAccount(){
    QString NAME = name->text();
    QString PASSWORD = password->text();

    if(NAME.isEmpty()){
        QMessageBox tip;
        tip.setText(tr("用户名不能为空！"));
        tip.exec();
        return;
    }

    if(NAME=="admin"){
        QMessageBox tip;
        tip.setText(tr("用户名不能为admin！"));
        tip.exec();
        return;
    }

    if(PASSWORD.isEmpty()){
        QMessageBox tip;
        tip.setText(tr("密码不能为空！"));
        tip.exec();
        return;
    }

    QFile pf("C:/QT/projects/trading_platform/trading_platform/Info/user.txt");
/*   qDebug() << "permissions before?  " << pf.permissions();
    pf.setPermissions(QFileDevice::WriteOwner | QFileDevice::ReadUser);
    qDebug() << "permissions after?  " << pf.permissions();
    qDebug() << "writable?            " << pf.isWritable();*/
    if(!pf.open(QIODevice::ReadOnly | QIODevice::Text)){
//        qDebug()<<"3";
        return;
    }

    QTextStream in(&pf);
    QString line = in.readLine();
    int max_uid=-1;
    while(!line.isNull()){
        QStringList list = line.split(",");
        if(list[1]==NAME){
            QMessageBox tip;
            tip.setText(tr("用户名已存在！"));
            tip.exec();
            pf.close();
            return;
        }
        QString id_num = list[0].mid(1);
        int uid = id_num.toInt();
        max_uid = max_uid > uid ? max_uid : uid;
        line = in.readLine();
    }
    pf.close();
    if(!pf.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        return;
    }
    max_uid = max_uid + 1;
    QString h = QString::number(max_uid/100);
    QString t = QString::number((max_uid%100)/10);
    QString s = QString::number(max_uid%10);
    QString new_id = "U" + h + t + s;
    QTextStream out(&pf);
    out<<new_id<<","<<NAME<<","<<PASSWORD<<","<<","<<","<<tr("0.0")<<","<<tr("正常")<<"\n";
    pf.close();
//    qDebug()<<"1";
    QMessageBox tip;
    tip.setText(tr("注册成功！"));
    tip.exec();
//    qDebug()<<"注册成功！";
    Login* login_screen = new Login;
    login_screen->show();
    this->close();
    return;
}

