#include <QString>
#include <QFile>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QDebug>

#include "login.h"
#include "global.h"


Login::Login(QWidget *parent)
    : QDialog(parent)
{
    //initial files
    QFile pf("C:/QT/projects/trading_platform/trading_platform/Info/user.txt");
    pf.open(QIODevice::ReadWrite);
    pf.close();

    //set other windows

    user_window = new User_Screen;

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
    QRegExpValidator * val1= new QRegExpValidator(QRegExp("[a-zA-Z0-9\u4e00-\u9fa5]{1,10}$"));//大小写字母数字中文 10位
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

    //background
    QPixmap background1;
    background1.load(":/image/background1.jpg");
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(background1));
    this->setPalette(palette);

    connect(sign_in,SIGNAL(clicked()),this,SLOT(checkPassword()));
    connect(sign_up,SIGNAL(clicked()),this,SLOT(log_up()));
    connect(user_window,SIGNAL(mySignal2()),this,SLOT(log_in()));
}

Login::~Login()
{
    delete photo;
    delete Name;
    delete Password;
    delete sign_in;
    delete sign_up;
    delete name;
    delete password;
    //delete logup_window;
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
            this->hide();
            Admin_Screen* admin_window = new Admin_Screen;
            admin_window->show();
        //    name->setText("");
      //      password->setText("");
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

    QFile pf("C:/QT/projects/trading_platform/trading_platform/Info/user.txt");
    if(!pf.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    QTextStream in(&pf);
    QString line = in.readLine();
    while(!line.isNull()){
        qDebug()<<"2";
        QStringList list = line.split(",");
        if(list[1]==NAME){
            if(list[2]==PASSWORD){
                QMessageBox tip;
                tip.setText(tr("登陆成功！"));
                tip.exec();
                this->hide();

                user_window->show();
                user_window->uid = list[0];
                user_window->Name->setText(tr("用户")+list[1]);
                user_window->Name->setGeometry((QRect(0,20,150,30)));
//                qDebug()<<user_window->uid;
                name->setText("");
                password->setText("");
                pf.close();
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
    this->hide();
    logup_window->show();
}

void Login::log_in(){
    user_window->hide();
    this->show();
}
