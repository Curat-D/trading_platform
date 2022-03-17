#include <QRegExpValidator>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>
#include "Calculator.h"
#include "command.h"
#include "buy_screen.h"
#include "global.h"
Buy_Screen::Buy_Screen(QWidget *parent, QString uid) :
    QDialog(parent),Uid(uid)
{
    setFixedSize(INFO_WINDOW_WIDTH, INFO_WINDOW_HEIGHT);
    setWindowTitle("淘淘");
    setWindowIcon(QIcon(":/image/icon.jpg"));

    //background
    QPixmap background1;
    background1.load(":/image/background1.jpg");
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(background1));
    this->setPalette(palette);

    Name = new QLabel(this);
    Name->setText(tr("商品ID"));
    Name->setGeometry(QRect(40,20,60,60));

    Name_E = new QLineEdit(this);
    Name_E->setGeometry(QRect(120,20,200,60));
    Name_E->setPlaceholderText(tr("输入商品ID"));
    QRegExpValidator * val1= new QRegExpValidator(QRegExp("^M[0-9]{3}$"));
    Name_E->setValidator(val1);

    Num = new QLabel(this);
    Num->setText(tr("数量"));
    Num->setGeometry(QRect(40,100,60,60));

    Num_E = new QLineEdit(this);
    Num_E->setGeometry(QRect(120,100,200,60));
    Num_E->setPlaceholderText(tr("输入购买数量"));
    QRegExpValidator * val2= new QRegExpValidator(QRegExp("[0-9]{1,20}$"));
    Num_E->setValidator(val2);

    Buy = new QPushButton(this);
    Buy->setText(tr("购买"));
    Buy->setGeometry(QRect(130,180,40,30));

    Back = new QPushButton(this);
    Back->setText(tr("返回"));
    Back->setGeometry(QRect(180,180,40,30));

    connect(Buy,SIGNAL(clicked()),this,SLOT(buy()));
    connect(Back,SIGNAL(clicked()),this,SLOT(back()));
}

Buy_Screen::~Buy_Screen()
{
    delete Name;
    delete Num;
    delete Name_E;
    delete Num_E;
    delete Buy;
    delete Back;
}

void Buy_Screen::buy(){
    QString com = Name_E->text();
    QString num = Num_E->text();

    if(com.isEmpty()||num.isEmpty()){
        return;
    }
    //查看商品是否存在
    QFile pf(DIR + "commodity.txt");
    if(!pf.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"打开商品文件失败！";
        exit(0);
    }
    QTextStream in(&pf);
    QString line = in.readLine();
    bool jdg = 0;
    QString number=0;
    QString price=0;
    QString seller;
    QString seller_balance;
    while(!line.isNull()){
        QStringList list = line.split(",");
        if(list[7] == "销售中"){
            if(list[0] == com){
                if(list[5]==Uid){
                    QMessageBox tip;
                    tip.setText("不能购买自己的商品！");
                    tip.exec();
                    pf.close();
                    return;
                }
                jdg=1;
                number=list[3];
                price=list[2];
                seller=list[5];
                break;
            }
        }

        line = in.readLine();
    }
    if(jdg==0 || num =="0"){
        QMessageBox tip;
        tip.setText("该商品不存在！");
        tip.exec();
        pf.close();
        return;
    }
    if(num.toInt() > number.toInt()){
        QMessageBox tip;
        tip.setText("该商品库存不足！");
        tip.exec();
        pf.close();
        return;
    }
    pf.close();
    //查看余额是否足够
    QFile pf1(DIR + "user.txt");
    if(!pf1.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"打开用户文件失败！";
        exit(0);
    }
    QTextStream in1(&pf1);
    line = in1.readLine();
    QString balance=0;
    while(!line.isNull()){
        QStringList list = line.split(",");
        if(list[0] == Uid){
            balance = list[5];
        }
        if(list[0] == seller){
            seller_balance = list[5];
        }
        line = in1.readLine();
    }
    if(balance.toFloat() < price.toFloat()*num.toInt()){
        QMessageBox tip;
        tip.setText("余额不足！");
        tip.exec();
        pf1.close();
        return;
    }
    pf1.close();
    //查看订单编号
    QFile pf2(DIR + "order.txt");
    if(!pf2.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"打开订单文件失败！";
        exit(0);
    }
    QTextStream in2(&pf2);
    line = in2.readLine();
    QString order_id="0";
    while(!line.isNull()){
        QStringList list = line.split(",");
        order_id = list[0];
        line=in2.readLine();
    }
    pf2.close();
    if(order_id == "0")
        order_id = "T000";
    else{
        int n = (order_id.mid(1,3)).toInt();
        n++;
        order_id[1] = n/100 + '0';
        order_id[2] = (n%100)/10 + '0';
        order_id[3] = n%10 + '0';
    }
    int new_num = number.toInt() - num.toInt();
    number=QString::number(new_num);
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss:");
    QString cmd1 = "INSERT INTO order VALUES (" + order_id + "," + com + "," + price + "," + num + "," + current_date_time.toString("yyyy-MM-dd") + "," + seller + "," + Uid + ")";
    QString cmd2 = "UPDATE commodity SET 数量 = " + number +" WHERE 商品ID = " + com;
    QString new_record1 = current_date + " " + cmd1 + "\n";
    QString new_record2 = current_date + " " + cmd2 + "\n";
    QFile pf3(DIR + "commands.txt");
    if(!pf3.open(QIODevice::WriteOnly | QIODevice::Append)){
        qDebug()<<"打开命令文件失败！";
        exit(0);
    }
    QTextStream out(&pf3);
    out<<new_record1<<new_record2;
    pf3.close();

    Command CMD(Uid+"B");
    CMD.deal_with_cmd(cmd1);
    CMD.deal_with_cmd(cmd2);


   //修改余额
    cal C;
    QString exp1 = balance + "-" + price + "*" + num;
    QString new_balance1 = QString::fromStdString(C.calculator(exp1.toStdString()));
    QString exp2 = seller_balance + "+" + price + "*" + num;
    QString new_balance2 = QString::fromStdString(C.calculator(exp2.toStdString()));
    QFile pf4(DIR + "user.txt");
    if(!pf4.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"Fail to open file";
        exit(0);
    }
    QTextStream in4(&pf4);
    QStringList infos;
    line = in4.readLine();
    while(!line.isEmpty()){
        QStringList list = line.split(",");
        if(list[0]==Uid){
            infos<<(list[0]+","+list[1]+","+list[2]+","+list[3]+","+list[4]+","+new_balance1+","+list[6]+"\n");
        }
        else if(list[0]==seller){
            infos<<(list[0]+","+list[1]+","+list[2]+","+list[3]+","+list[4]+","+new_balance2+","+list[6]+"\n");
        }
        else{
            infos<<(line + "\n");
        }
        line = in4.readLine();
    }
    pf4.close();
    if(!pf4.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)){
        qDebug()<<"Fail to open file";
        exit(0);
    }
    QTextStream out1(&pf4);
    for(int i=0;i<infos.size();i++){
        QString tmp = infos[i];
        out1<<tmp;
    }
    pf4.close();
    QMessageBox tip;
    tip.setText("购买成功！");
    tip.exec();
    this->close();
    return;
}

void Buy_Screen::back(){
    this->close();
}
