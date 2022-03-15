#include <QMenuBar>
#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QMessageBox>
#include "admin_screen.h"
#include "login.h"
#include "global.h"
#include "command.h"

Admin_Screen::Admin_Screen(QWidget *parent) :
    QMainWindow(parent)
{
    //set window
    setFixedSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    setWindowTitle(tr("淘淘"));
    setWindowIcon(QIcon(":/image/icon.jpg"));

    QMenuBar *menu_bar = new QMenuBar(this);
    setMenuBar(menu_bar);
    QMenu* logout = menu_bar->addMenu(tr("注销"));


    photo = new QLabel(this);
    QPixmap pic;
    pic.load(":/image/admin.jpg");
    photo->setPixmap(pic);
    photo->setGeometry(QRect(100,70,240,140));

    //add button
    view_all_coms = new QPushButton(this);
    view_all_coms->setText(tr("查看所有商品"));
    view_all_coms->setGeometry(QRect(20,250,150,50));

    search = new QPushButton(this);
    search->setText(tr("搜索商品"));
    search->setGeometry(QRect(20,300,150,50));

    search_E = new QLineEdit(this);
    search_E->setGeometry(QRect(170,300,300,50));
    search_E->setPlaceholderText(tr("输入商品名以搜索"));
    QRegExpValidator * val1= new QRegExpValidator(QRegExp("[a-zA-Z0-9\u4e00-\u9fa5]{1,20}$"));//大小写字母中文 10位
    search_E->setValidator(val1);

    withdraw_com = new QPushButton(this);
    withdraw_com->setText(tr("下架"));
    withdraw_com->setGeometry(QRect(20,350,150,50));

    withdraw_com_E = new QLineEdit(this);
    withdraw_com_E->setGeometry(QRect(170,350,300,50));
    withdraw_com_E->setPlaceholderText(tr("输入商品ID"));
    QRegExpValidator * val2= new QRegExpValidator(QRegExp("^M[0-9]{3}$"));
    withdraw_com_E->setValidator(val2);

    view_all_orders = new QPushButton(this);
    view_all_orders->setText(tr("查看所有订单"));
    view_all_orders->setGeometry(QRect(170,250,150,50));

    view_all_users = new QPushButton(this);
    view_all_users->setText(tr("查看所有用户"));
    view_all_users->setGeometry(QRect(320,250,150,50));

    ban_user = new QPushButton(this);
    ban_user->setText(tr("封禁用户"));
    ban_user->setGeometry(QRect(20,400,150,50));
    ban_user_E = new QLineEdit(this);
    ban_user_E->setGeometry(QRect(170,400,300,50));
    ban_user_E->setPlaceholderText(tr("输入用户ID"));
    QRegExpValidator * val3= new QRegExpValidator(QRegExp("^U[0-9]{3}$"));
    ban_user_E->setValidator(val3);

    table = new QTableView(this);
    table->setGeometry(QRect(600,50,900,600));
    table->hide();
 //   table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setAlternatingRowColors(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);


    QPixmap background1;
    background1.load(":/image/background2.jpg");
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(background1));
    this->setPalette(palette);

    connect(logout,SIGNAL(aboutToShow()),this,SLOT(Log_out()));
    connect(view_all_coms,SIGNAL(clicked()),this,SLOT(View_All_Coms()));
    connect(search,SIGNAL(clicked()),this,SLOT(Search()));
    connect(withdraw_com,SIGNAL(clicked()),this,SLOT(Withdraw_com()));
    connect(view_all_orders,SIGNAL(clicked()),this,SLOT(View_all_orders()));
    connect(view_all_users,SIGNAL(clicked()),this,SLOT(View_all_users()));
    connect(ban_user,SIGNAL(clicked()),this,SLOT(Ban_user()));
}

Admin_Screen::~Admin_Screen()
{
    delete photo;
    delete view_all_coms;
    delete search;
    delete withdraw_com;
    delete view_all_users;
    delete view_all_orders;
    delete ban_user;
    delete log_out;
    delete table;
}

void Admin_Screen::View_All_Coms(){
//    qDebug()<<"1";
    QString cmd = "SELECT * FROM commodity";
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss:");
    QString new_record = current_date + " " + cmd + "\n";
    QFile pf(DIR + "commands.txt");
    if(!pf.open(QIODevice::WriteOnly | QIODevice::Append)){
        qDebug()<<"打开命令文件失败！";
        exit(0);
    }
    QTextStream out(&pf);
    out<<new_record;
    pf.close();
    Command CMD("admin");
    QStandardItemModel* model = CMD.deal_with_cmd(cmd);
    model->setParent(table);
    table->setModel(model);
    table->show();

}
void Admin_Screen::Search(){
    QString com = search_E->text();
    if(com.isEmpty()){
        QStandardItemModel* model = new QStandardItemModel(table);
        model->setColumnCount(7);
        model->setHeaderData(0,Qt::Horizontal, "商品ID");
        model->setHeaderData(1,Qt::Horizontal, "名称");
        model->setHeaderData(2,Qt::Horizontal, "价格");
        model->setHeaderData(3,Qt::Horizontal, "上架时间");
        model->setHeaderData(4,Qt::Horizontal, "卖家ID");
        model->setHeaderData(5,Qt::Horizontal, "数量");
        model->setHeaderData(6,Qt::Horizontal, "商品状态");
        table->setModel(model);
        table->show();
        return;
    }
    QString cmd = "SELECT * FROM commodity WHERE 名称 CONTAINS " + com;
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss:");
    QString new_record = current_date + " " + cmd + "\n";
    QFile pf(DIR + "commands.txt");
    if(!pf.open(QIODevice::WriteOnly | QIODevice::Append)){
        qDebug()<<"打开命令文件失败！";
        exit(0);
    }
    QTextStream out(&pf);
    out<<new_record;
    pf.close();
    Command CMD("admin");
    QStandardItemModel* model = CMD.deal_with_cmd(cmd);
    model->setParent(table);
    table->setModel(model);
    table->show();
}
void Admin_Screen::Withdraw_com(){
    QString Mid = withdraw_com_E->text();
    if(Mid.isEmpty())
        return;
    QFile pf0(DIR+"commodity.txt");
    if(!pf0.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"打开商品文件失败！";
        exit(0);
    }
    QTextStream in(&pf0);
    QString line = in.readLine();
    bool jdg=0;
    while(!line.isNull()){
        QStringList list = line.split(",");
        if(list[0] == Mid){
            jdg=1;
            break;
        }
        line = in.readLine();
    }
    pf0.close();
    if(jdg==0){
        QMessageBox tip;
        tip.setText("不存在该商品!");
        tip.exec();
        return;
    }


    QString cmd = "UPDATE commodity SET 商品状态 = 已下架 WHERE 商品ID = "+Mid;
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss:");
    QString new_record = current_date + " " + cmd + "\n";
    QFile pf(DIR + "commands.txt");
    if(!pf.open(QIODevice::WriteOnly | QIODevice::Append)){
        qDebug()<<"打开命令文件失败！";
        exit(0);
    }
    QTextStream out(&pf);
    out<<new_record;
    pf.close();
    Command CMD("admin");
    QStandardItemModel* model = CMD.deal_with_cmd(cmd);
//    qDebug()<<"1";
    model->setParent(table);
//    qDebug()<<"0";
    table->setModel(model);
    table->show();

}
void Admin_Screen::View_all_orders(){
    //    qDebug()<<"1";
    QString cmd = "SELECT * FROM order";
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss:");
    QString new_record = current_date + " " + cmd + "\n";
    QFile pf(DIR + "commands.txt");
    if(!pf.open(QIODevice::WriteOnly | QIODevice::Append)){
        qDebug()<<"打开命令文件失败！";
        exit(0);
    }
    QTextStream out(&pf);
    out<<new_record;
    pf.close();
    Command CMD("admin");
    QStandardItemModel* model = CMD.deal_with_cmd(cmd);
    model->setParent(table);
    table->setModel(model);
    table->show();
}
void Admin_Screen::View_all_users(){
    table->hide();
    QString cmd = "SELECT * FROM user";
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss:");
    QString new_record = current_date + " " + cmd + "\n";
    QFile pf(DIR + "commands.txt");
    if(!pf.open(QIODevice::WriteOnly | QIODevice::Append)){
        qDebug()<<"打开命令文件失败！";
        exit(0);
    }
    QTextStream out(&pf);
    out<<new_record;
    pf.close();
    Command CMD("admin");
    QStandardItemModel* model = CMD.deal_with_cmd(cmd);
    model->setParent(table);
    table->setModel(model);
    table->show();
}
void Admin_Screen::Ban_user(){
    QString Uid = ban_user_E->text();
    QString cmd = "UPDATE user SET 用户状态 = 封禁 WHERE 用户ID = "+Uid;
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss:");
    QString new_record = current_date + " " + cmd + "\n";
    QFile pf(DIR + "commands.txt");
    if(!pf.open(QIODevice::WriteOnly | QIODevice::Append)){
        qDebug()<<"打开命令文件失败！";
        exit(0);
    }
    QTextStream out(&pf);
    out<<new_record;
    pf.close();
    Command CMD("admin");
    QStandardItemModel* model = CMD.deal_with_cmd(cmd);
//    qDebug()<<"1";
    model->setParent(table);
//    qDebug()<<"0";
    table->setModel(model);
    table->show();
}
void Admin_Screen::Log_out(){
    Login* login_screen = new Login;
    login_screen->show();
    this->close();
}



