#include <QMenuBar>
#include <QDebug>
#include "admin_screen.h"

Admin_Screen::Admin_Screen(QWidget *parent) :
    QMainWindow(parent)
{
    //set window
    setFixedSize(LOGIN_WINDOW_WIDTH, LOGIN_WINDOW_HEIGHT);
    setWindowTitle(tr("淘淘"));
    setWindowIcon(QIcon(":/image/icon.jpg"));

    QMenuBar *menu_bar = new QMenuBar(this);
    setMenuBar(menu_bar);
    QMenu* logout = menu_bar->addMenu(tr("注销"));
//    QAction* Logout = logout->addAction(tr("注销"));


    photo = new QLabel(this);
    QPixmap pic;
    pic.load(":/image/admin.jpg");
    photo->setPixmap(pic);
    photo->setGeometry(QRect(350,70,240,140));

    //add button
    view_all_coms = new QPushButton(this);
    view_all_coms->setText(tr("查看所有商品"));
    view_all_coms->setGeometry(QRect(300,250,150,50));

    search = new QPushButton(this);
    search->setText(tr("搜索商品"));
    search->setGeometry(QRect(300,300,150,50));

    withdraw_com = new QPushButton(this);
    withdraw_com->setText(tr("下架"));
    withdraw_com->setGeometry(QRect(300,350,150,50));

    view_all_orders = new QPushButton(this);
    view_all_orders->setText(tr("查看所有订单"));
    view_all_orders->setGeometry(QRect(500,250,150,50));

    view_all_users = new QPushButton(this);
    view_all_users->setText(tr("查看所有用户"));
    view_all_users->setGeometry(QRect(500,300,150,50));

    ban_user = new QPushButton(this);
    ban_user->setText(tr("封禁用户"));
    ban_user->setGeometry(QRect(500,350,150,50));


    QPixmap background1;
    background1.load(":/image/background1.jpg");
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(background1));
    this->setPalette(palette);

    connect(logout,SIGNAL(aboutToShow()),this,SLOT(Log_out()));
}

Admin_Screen::~Admin_Screen()
{
}

void Admin_Screen::View_All_Coms(){

}
void Admin_Screen::Search(){

}
void Admin_Screen::Withdraw_com(){

}
void Admin_Screen::View_all_orders(){

}
void Admin_Screen::View_all_users(){

}
void Admin_Screen::Ban_user(){

}
void Admin_Screen::Log_out(){
    emit mySignal1();
}



