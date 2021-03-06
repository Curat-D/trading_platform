#include <QDebug>
#include <QMenuBar>
#include "user_screen.h"
#include "login.h"
#include "myinfo.h"
#include "buyer_screen.h"
#include "seller_screen.h"

User_Screen::User_Screen(QWidget *parent, QString id) :
    QMainWindow(parent),Uid(id)
{
    //change balance


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

    connect(logout,SIGNAL(aboutToShow()),this,SLOT(Log_out()));
    connect(personal_info,SIGNAL(clicked()),this,SLOT(PersonalInfo()));
    connect(buyer,SIGNAL(clicked()),this,SLOT(Buyer()));
    connect(seller,SIGNAL(clicked()),this,SLOT(Seller()));
}

User_Screen::~User_Screen()
{
    delete photo;
    delete buyer;
    delete seller;
    delete personal_info;
}

void User_Screen::Log_out(){
    Login* login_screen = new Login;
    login_screen->show();
    this->close();
}

void User_Screen::PersonalInfo(){
    MyInfo* info_screen = new MyInfo(nullptr, Uid);
    info_screen->exec();
}

void User_Screen::Seller(){
    Seller_Screen* seller_window = new Seller_Screen(nullptr,Uid);
    seller_window->show();
    this->close();
}

void User_Screen::Buyer(){
    Buyer_Screen* buyer_window = new Buyer_Screen(nullptr,Uid);
    buyer_window->show();
    this->close();
}
