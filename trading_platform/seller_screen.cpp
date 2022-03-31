#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QMessageBox>
#include "seller_screen.h"
#include "user_screen.h"
#include "global.h"
#include "command.h"
#include "modify_screen.h"
#include "release_screen.h"

Seller_Screen::Seller_Screen(QWidget *parent,QString id) :
    QMainWindow(parent),Uid(id)
{
    //set window
    setFixedSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    setWindowTitle(tr("淘淘"));
    setWindowIcon(QIcon(":/image/icon.jpg"));


    photo = new QLabel(this);
    QPixmap pic;
    pic.load(":/image/user.jpg");
    photo->setPixmap(pic);
    photo->setGeometry(QRect(100,70,240,140));


    //add button
    view_coms = new QPushButton(this);
    view_coms->setText(tr("查看发布商品"));
    view_coms->setGeometry(QRect(20,250,220,50));

    view_orders = new QPushButton(this);
    view_orders->setText(tr("查看历史订单"));
    view_orders->setGeometry(QRect(250,250,220,50));

    modify = new QPushButton(this);
    modify->setText(tr("修改商品信息"));
    modify->setGeometry(QRect(20,300,150,50));

    modify_E = new QLineEdit(this);
    modify_E->setGeometry(QRect(170,300,300,50));
    modify_E->setPlaceholderText(tr("输入商品ID以搜索"));
    QRegExpValidator * val1= new QRegExpValidator(QRegExp("^M[0-9]{3}$"));//大小写字母中文 10位
    modify_E->setValidator(val1);

    withdraw_com = new QPushButton(this);
    withdraw_com->setText(tr("下架商品"));
    withdraw_com->setGeometry(QRect(20,350,150,50));

    withdraw_com_E = new QLineEdit(this);
    withdraw_com_E->setGeometry(QRect(170,350,300,50));
    withdraw_com_E->setPlaceholderText(tr("输入商品ID以下架"));
    QRegExpValidator * val3= new QRegExpValidator(QRegExp("^M[0-9]{3}$"));
    withdraw_com_E->setValidator(val3);


    release_com = new QPushButton(this);
    release_com->setText(tr("发布商品"));
    release_com->setGeometry(QRect(20,400,220,50));

    back = new QPushButton(this);
    back->setText(tr("返回用户主界面"));
    back->setGeometry(QRect(250,400,220,50));

    QPixmap background1;
    background1.load(":/image/background2.jpg");
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(background1));
    this->setPalette(palette);

    table = new QTableView(this);
    table->setGeometry(QRect(600,50,900,600));
    table->setAlternatingRowColors(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    sort_attribute = new QComboBox(this);
    sort_attribute->addItem(tr("编号"));
    sort_attribute->addItem(tr("价格"));
    sort_attribute->setGeometry(QRect(600,670,200,50));

    sort_order = new QComboBox(this);
    sort_order->addItem(tr("升序"));
    sort_order->addItem(tr("降序"));
    sort_order->setGeometry(QRect(850,670,200,50));

    my_sort = new QPushButton(this);
    my_sort->setText(tr("排序"));
    my_sort->setGeometry(QRect(1100,670,200,50));

    connect(view_coms,SIGNAL(clicked()),this,SLOT(View_Coms()));
    connect(release_com,SIGNAL(clicked()),this,SLOT(Release_Com()));
    connect(modify,SIGNAL(clicked()),this,SLOT(Modify()));
    connect(view_orders,SIGNAL(clicked()),this,SLOT(View_Orders()));
    connect(withdraw_com,SIGNAL(clicked()),this,SLOT(Withdraw_Com()));
    connect(back,SIGNAL(clicked()),this,SLOT(Back()));
    connect(my_sort,SIGNAL(clicked()),this,SLOT(My_Sort()));
}

Seller_Screen::~Seller_Screen()
{
    delete photo;
    delete view_coms;
    delete  release_com;
    delete modify;
    delete view_orders;
    delete withdraw_com;
    delete back;
    delete  modify_E;
    delete withdraw_com_E;
    delete table;
}

void Seller_Screen::View_Coms(){
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
    Command CMD(Uid+"S");
    QStandardItemModel* model = CMD.deal_with_cmd(cmd);
    model->setParent(table);
    table->setModel(model);
    table->show();
}

void Seller_Screen::Release_Com(){
    Release_Screen* release_window = new Release_Screen(nullptr,Uid);
    release_window->exec();
    return ;
}

void Seller_Screen::Modify(){
    QString Mid = modify_E->text();
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
        if(list[0] == Mid && list[5] == Uid){
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
         qDebug()<<"2";
    Modify_Screen* modify_window = new Modify_Screen(nullptr,Mid);
    modify_window->exec();


    return;
}

void Seller_Screen::View_Orders(){
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
    Command CMD(Uid+"S");
    QStandardItemModel* model = CMD.deal_with_cmd(cmd);
    model->setParent(table);
    table->setModel(model);
    table->show();
}

void Seller_Screen::Withdraw_Com(){
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
        if(list[0] == Mid && list[5] == Uid){
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
    Command CMD(Uid+"S");
    CMD.deal_with_cmd(cmd);
    table->hide();
    QMessageBox tip;
    tip.setText("下架成功!");
    tip.exec();
    return;
}

void Seller_Screen::Back(){
    User_Screen* user_window = new User_Screen(nullptr,Uid);
    user_window->show();
    this->close();
}

void Seller_Screen::My_Sort(){
    int idx1 = sort_attribute->currentIndex();
    int idx2 = sort_order->currentIndex();
    if(idx1==0){
        if(idx2==0)
            table->sortByColumn(0,Qt::AscendingOrder);
        else
            table->sortByColumn(0,Qt::DescendingOrder);
    }
    else{
        if(idx2==0)
            table->sortByColumn(2,Qt::AscendingOrder);
        else
            table->sortByColumn(2,Qt::DescendingOrder);
    }
}
