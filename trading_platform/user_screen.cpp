#include <QDebug>
#include "user_screen.h"
#include "ui_user.h"

User_Screen::User_Screen(QWidget *parent) :
    QMainWindow(parent)
{
    //set window
    setFixedSize(LOGIN_WINDOW_WIDTH, LOGIN_WINDOW_HEIGHT);
    setWindowTitle(tr("淘淘"));
    setWindowIcon(QIcon(":/image/icon.jpg"));

    QMenuBar *menu_bar = new QMenuBar(this);
    setMenuBar(menu_bar);
    QMenu* logout = menu_bar->addMenu(tr("注销"));


    photo = new QLabel(this);
    QPixmap pic;
    pic.load(":/image/user.jpg");
    photo->setPixmap(pic);
    photo->setGeometry(QRect(350,70,240,180));


    buyer = new QPushButton(this);
    buyer->setText(tr("我是买家"));
    buyer->setGeometry(QRect(300,270,150,50));

    seller = new QPushButton(this);
    seller->setText(tr("我是卖家"));
    seller->setGeometry(QRect(500,270,150,50));

    personal_info = new QPushButton(this);
    personal_info->setText(tr("个人信息管理"));
    personal_info->setGeometry(QRect(400,350,150,50));

    QPixmap background1;
    background1.load(":/image/background1.jpg");
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(background1));
    this->setPalette(palette);

    Name = new QLabel(this);
    connect(logout,SIGNAL(aboutToShow()),this,SLOT(Log_out()));
}

User_Screen::~User_Screen()
{

}

void User_Screen::Log_out(){
    emit mySignal2();
}
