#include "login.h"
#include "global.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
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

    password = new QLineEdit(this);
    password->setGeometry(QRect(420,250,200,30));

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
 //   ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

