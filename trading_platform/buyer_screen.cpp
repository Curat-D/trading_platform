#include "buyer_screen.h"
#include "global.h"

Buyer_Screen::Buyer_Screen(QWidget *parent) :
    QMainWindow(parent)
{
    //set window
    setFixedSize(LOGIN_WINDOW_WIDTH, LOGIN_WINDOW_HEIGHT);
    setWindowTitle(tr("淘淘"));
    setWindowIcon(QIcon(":/image/icon.jpg"));


    photo = new QLabel(this);
    QPixmap pic;
    pic.load(":/image/user.jpg");
    photo->setPixmap(pic);
    photo->setGeometry(QRect(350,70,240,180));


    //add button
    view_coms = new QPushButton(this);
    view_coms->setText(tr("查看商品列表"));
    view_coms->setGeometry(QRect(300,250,150,50));

    buy_com = new QPushButton(this);
    buy_com->setText(tr("购买商品"));
    buy_com->setGeometry(QRect(300,300,150,50));

    search = new QPushButton(this);
    search->setText(tr("搜索商品"));
    search->setGeometry(QRect(300,350,150,50));

    view_orders = new QPushButton(this);
    view_orders->setText(tr("查看历史订单"));
    view_orders->setGeometry(QRect(500,250,150,50));

    view_detail = new QPushButton(this);
    view_detail->setText(tr("查看商品详细信息"));
    view_detail->setGeometry(QRect(500,300,150,50));

    back = new QPushButton(this);
    back->setText(tr("返回用户主界面"));
    back->setGeometry(QRect(500,350,150,50));

    QPixmap background1;
    background1.load(":/image/background1.jpg");
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(background1));
    this->setPalette(palette);

    Name = new QLabel(this);

}

Buyer_Screen::~Buyer_Screen()
{

}
