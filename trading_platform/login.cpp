#include <QString>
#include <QFile>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QDebug>

#include "login.h"
#include "logup.h"
#include "admin_screen.h"
#include "user_screen.h"
#include "global.h"
#include "cal_screen.h"

Login::Login(QWidget *parent)
    : QDialog(parent)
{
    //initial files
    QFile pf(DIR + "user.txt");
    if(!pf.open(QIODevice::ReadWrite)){
        qDebug()<<"Fail to create file1";
        exit(0);
    }
    pf.close();
    QFile pf1(DIR + "commands.txt");
    if(!pf1.open(QIODevice::ReadWrite)){
        qDebug()<<"Fail to create file";
        exit(0);
    }
    pf1.close();
    QFile pf2(DIR + "commodity.txt");
    if(!pf2.open(QIODevice::ReadWrite)){
        qDebug()<<"Fail to create file";
        exit(0);
    }
    pf2.close();
    QFile pf3(DIR + "order.txt");
    if(!pf3.open(QIODevice::ReadWrite)){
        qDebug()<<"Fail to create file";
        exit(0);
    }
    pf3.close();


    //set the window
    setFixedSize(LOGIN_WINDOW_WIDTH, LOGIN_WINDOW_HEIGHT);
    setWindowTitle("淘淘");
    setWindowIcon(QIcon(":/image/icon.jpg"));

    //add label
    photo = new QLabel(this);
    QPixmap pic;
    pic.load(":/image/photo.jpg");
    photo->setPixmap(pic);
    photo->setGeometry(QRect(450,70,120,120));

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
    sign_in = new QPushButton(this);
    sign_in->setText(tr("登录"));
    sign_in->setGeometry(QRect(420,300,70,30));

    sign_up = new QPushButton(this);
    sign_up->setText(tr("注册"));
    sign_up->setGeometry(QRect(550,300,70,30));

    cal = new QPushButton(this);
    cal->setText(tr("计算器"));
    cal->setGeometry(QRect(500,350,70,30));

    //background
    QPixmap background1;
    background1.load(":/image/background1.jpg");
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(background1));
    this->setPalette(palette);

    connect(sign_in,SIGNAL(clicked()),this,SLOT(checkPassword()));
    connect(sign_up,SIGNAL(clicked()),this,SLOT(log_up()));
    connect(cal,SIGNAL(clicked()),this,SLOT(calculator()));
}

Login::~Login()
{
    delete photo;
    delete Name;
    delete Password;
    delete sign_in;
    delete sign_up;
    delete cal;
    delete name;
    delete password;
}

void Login::checkPassword(){
    QString NAME = name->text();
    QString PASSWORD = password->text();

    if(NAME.isEmpty()||PASSWORD.isEmpty()){
        QMessageBox tip;
        tip.setText(tr("用户名和密码不能为空！"));
        tip.exec();
        return;
    }
    if(NAME=="admin"){
        if(PASSWORD=="123456"){
            QMessageBox tip;
            tip.setText(tr("登陆成功！"));
            tip.exec();
            this->close();
            Admin_Screen* admin_window = new Admin_Screen;
            admin_window->show();
            return;
        }
        else{
            QMessageBox tip;
            tip.setText(tr("密码错误！"));
            tip.exec();
            password->setText("");
            return;
        }
    }

 //   QFile pf("C:/QT/projects/trading_platform/trading_platform/Info/user.txt");
    QFile pf(DIR + "user.txt");
    if(!pf.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"Fail to open user file!";
        exit(0);
    }
    QTextStream in(&pf);
    QString line = in.readLine();
    while(!line.isNull()){
        QStringList list = line.split(",");
        if(list[1]==NAME){
            if(list[2]==PASSWORD){
                if(list[6] == tr("封禁")){
                    QMessageBox tip;
                    tip.setText(tr("该用户已被封禁！"));
                    tip.exec();
                    return;
                }
                pf.close();
                QMessageBox tip;
                tip.setText(tr("登陆成功！"));
                tip.exec();
                this->close();
                User_Screen* user_window = new User_Screen(nullptr, list[0]);
                user_window->show();
//                qDebug()<<user_window->uid;

                return;
            }
            else{
                QMessageBox tip;
                tip.setText(tr("用户不存在或密码错误！"));
                tip.exec();
                pf.close();
                password->setText("");
                return ;
            }
        }
        line = in.readLine();
    }
    QMessageBox tip;
    tip.setText(tr("用户不存在或密码错误！"));
    tip.exec();
    pf.close();
    password->setText("");
    return ;
}

void Login::log_up(){
    Logup* logup_window = new Logup;
    this->close();
    logup_window->show();
}

void Login::calculator(){
    Cal_Screen* cal_window = new Cal_Screen;
    cal_window->show();
}
