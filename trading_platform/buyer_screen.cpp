#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QMessageBox>

#include "buyer_screen.h"
#include "user_screen.h"
#include "global.h"
#include "command.h"
#include "Calculator.h"
#include "buy_screen.h"

Buyer_Screen::Buyer_Screen(QWidget *parent, QString id) :
    QMainWindow(parent), Uid(id)
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
    view_coms->setText(tr("查看商品列表"));
    view_coms->setGeometry(QRect(20,250,220,50));

    view_orders = new QPushButton(this);
    view_orders->setText(tr("查看历史订单"));
    view_orders->setGeometry(QRect(250,250,220,50));

    search = new QPushButton(this);
    search->setText(tr("搜索商品"));
    search->setGeometry(QRect(20,300,150,50));

    search_E = new QLineEdit(this);
    search_E->setGeometry(QRect(170,300,300,50));
    search_E->setPlaceholderText(tr("输入商品名以搜索"));
    QRegExpValidator * val1= new QRegExpValidator(QRegExp("[a-zA-Z0-9\u4e00-\u9fa5]{1,20}$"));//大小写字母中文 10位
    search_E->setValidator(val1);

    view_detail = new QPushButton(this);
    view_detail->setText(tr("查看商品详细信息"));
    view_detail->setGeometry(QRect(20,350,150,50));

    view_detail_E = new QLineEdit(this);
    view_detail_E->setGeometry(QRect(170,350,300,50));
    view_detail_E->setPlaceholderText(tr("输入商品ID"));
    QRegExpValidator * val3= new QRegExpValidator(QRegExp("^M[0-9]{3}$"));
    view_detail_E->setValidator(val3);


    buy_com = new QPushButton(this);
    buy_com->setText(tr("购买商品"));
    buy_com->setGeometry(QRect(20,400,220,50));

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
    connect(search,SIGNAL(clicked()),this,SLOT(Search()));
    connect(buy_com,SIGNAL(clicked()),this,SLOT(Buy_Com()));
    connect(view_orders,SIGNAL(clicked()),this,SLOT(View_Orders()));
    connect(view_detail,SIGNAL(clicked()),this,SLOT(View_Detail()));
    connect(back,SIGNAL(clicked()),this,SLOT(Back()));
    connect(my_sort,SIGNAL(clicked()),this,SLOT(My_Sort()));
}

Buyer_Screen::~Buyer_Screen()
{
    delete photo;
    delete view_coms;
    delete buy_com;
    delete search;
    delete view_orders;
    delete view_detail;
    delete search_E;
    delete view_detail_E;
    delete back;
}


void Buyer_Screen::View_Coms(){
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
    Command CMD(Uid+"B");
    QStandardItemModel* model = CMD.deal_with_cmd(cmd);
    model->setParent(table);
    table->setModel(model);
    table->show();
}
void Buyer_Screen::Search(){
    QString com = search_E->text();
    if(com.isEmpty()){
        QStandardItemModel* model = new QStandardItemModel(table);
        model->setColumnCount(6);
        model->setHeaderData(0,Qt::Horizontal, "商品ID");
        model->setHeaderData(1,Qt::Horizontal, "名称");
        model->setHeaderData(2,Qt::Horizontal, "价格");
        model->setHeaderData(3,Qt::Horizontal, "数量");
        model->setHeaderData(4,Qt::Horizontal, "上架时间");
        model->setHeaderData(5,Qt::Horizontal, "卖家ID");
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
    Command CMD(Uid+"B");
    QStandardItemModel* model = CMD.deal_with_cmd(cmd);
    model->setParent(table);
    table->setModel(model);
    table->show();
}
void Buyer_Screen::Buy_Com(){
    Buy_Screen* buy_window = new Buy_Screen(nullptr,Uid);
    buy_window->exec();
    return ;
}
void Buyer_Screen::View_Orders(){
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
    Command CMD(Uid+"B");
    QStandardItemModel* model = CMD.deal_with_cmd(cmd);
    model->setParent(table);
    table->setModel(model);
    table->show();
}
void Buyer_Screen::View_Detail(){
    QString com = view_detail_E->text();
    if(com.isEmpty()){
        QStandardItemModel* model = new QStandardItemModel(table);
        model->setColumnCount(6);
        model->setHeaderData(0,Qt::Horizontal, "商品ID");
        model->setHeaderData(1,Qt::Horizontal, "名称");
        model->setHeaderData(2,Qt::Horizontal, "价格");
        model->setHeaderData(3,Qt::Horizontal, "上架时间");
        model->setHeaderData(4,Qt::Horizontal, "商品描述");
        model->setHeaderData(5,Qt::Horizontal, "卖家ID");
        table->setModel(model);
        table->show();
        return;
    }
    QString cmd = "SELECT * FROM commodity WHERE 商品ID CONTAINS " + com;
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
    Command CMD(Uid+"B");
    QStandardItemModel* model = CMD.deal_with_cmd(cmd);
    model->setParent(table);
    table->setModel(model);
    table->show();
}
void Buyer_Screen::Back(){
    User_Screen* user_window = new User_Screen(nullptr,Uid);
    user_window->show();
    this->close();
}
void Buyer_Screen::My_Sort(){
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
