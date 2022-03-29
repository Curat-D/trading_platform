#include <QFile>
#include <QDebug>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QDateTime>
#include <unordered_map>
#include "myinfo.h"
#include "global.h"
#include "Calculator.h"

MyInfo::MyInfo(QWidget *parent, QString uid) :
    QDialog(parent),Uid(uid)
{
    setFixedSize(INFO_WINDOW_WIDTH, INFO_WINDOW_HEIGHT);
    setWindowTitle("淘淘");
    setWindowIcon(QIcon(":/image/icon.jpg"));

  //  qDebug()<<"2";
    Name = new QLabel(this);
    Name->setText(tr("用户名"));
    Name->setGeometry(QRect(40,20,70,30));

    Phone = new QLabel(this);
    Phone->setText(tr("联系方式"));
    Phone->setGeometry(QRect(40,60,70,30));

    Address = new QLabel(this);
    Address->setText(tr("地址"));
    Address->setGeometry(QRect(40,100,70,30));

    Balance = new QLabel(this);
    Balance->setText(tr("余额"));
    Balance->setGeometry(QRect(40,140,70,30));

    Change = new QPushButton(this);
    Change->setText(tr("修改"));
    Change->setGeometry(QRect(80,180,40,30));

    Recharge = new QPushButton(this);
    Recharge->setText(tr("充值"));
    Recharge->setGeometry(QRect(130,180,40,30));

    Back = new QPushButton(this);
    Back->setText(tr("返回"));
    Back->setGeometry(QRect(180,180,40,30));

     QFile pf(DIR + "user.txt");
     if(!pf.open(QIODevice::ReadOnly | QIODevice::Text)){
         qDebug()<<"Fail to open file";
         exit(0);
     }

    QTextStream in(&pf);
    QString line = in.readLine();
    while(!line.isNull()){
        QStringList list = line.split(",");
        if(list[0] == Uid){
            Name_E = new QLineEdit(this);
            Name_E->setText(list[1]);
            Name_E->setGeometry(QRect(120,20,70,30));
            QRegExpValidator * val1= new QRegExpValidator(QRegExp("[a-zA-Z\u4e00-\u9fa5]{1,10}$"));
            Name_E->setValidator(val1);
            Name_E->setEnabled(false);

            Phone_E = new QLineEdit(this);
            Phone_E->setText(list[3]);
            Phone_E->setGeometry(QRect(120,60,70,30));
            QRegExpValidator * val2= new QRegExpValidator(QRegExp("[0-9]{1,20}$"));
            Phone_E->setValidator(val2);
            Phone_E->setEnabled(false);

            Address_E = new QLineEdit(this);
            Address_E->setText(list[4]);
            Address_E->setGeometry(QRect(120,100,70,30));
            QRegExpValidator * val3= new QRegExpValidator(QRegExp("[a-zA-Z\u4e00-\u9fa5]{1,20}$"));
            Address_E->setValidator(val3);
            Address_E->setEnabled(false);

            Balance_E = new QLineEdit(this);
            Balance_E->setText(get_balance());
            Balance_E->setGeometry(QRect(120,140,70,30));
            QRegExpValidator * val4= new QRegExpValidator(QRegExp("[0-9]{1,50}(\\.[0-9])?$"));
            Balance_E->setValidator(val4);
            Balance_E->setEnabled(false);

            break;
        }
        line = in.readLine();
    }
    pf.close();

    //background
    QPixmap background1;
    background1.load(":/image/background1.jpg");
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(background1));
    this->setPalette(palette);

    connect(Change,SIGNAL(clicked()),this,SLOT(change()));
    connect(Back,SIGNAL(clicked()),this,SLOT(back()));
    connect(Recharge,SIGNAL(clicked()),this,SLOT(recharge()));
}

MyInfo::~MyInfo()
{
    delete Name;
    delete Phone;
    delete Address;
    delete Balance;
    delete Name_E;
    delete Phone_E;
    delete Address_E;
    delete Balance_E;
}

void MyInfo::change(){
    if(Change->text()==tr("修改")){
        Name_E->setEnabled(true);
        Phone_E->setEnabled(true);
        Address_E->setEnabled(true);
        Change->setText(tr("确定"));
    }
    else{
        Name_E->setEnabled(false);
        Phone_E->setEnabled(false);
        Address_E->setEnabled(false);
        Change->setText(tr("修改"));
        if(Name_E->text().isEmpty()){
            QFile pf(DIR + "user.txt");
            if(!pf.open(QIODevice::ReadOnly | QIODevice::Text)){
                qDebug()<<"Fail to open file";
                exit(0);
            }
            QTextStream in(&pf);
            QString line = in.readLine();
            while(!line.isNull()){
                QStringList list = line.split(",");
                if(list[0] == Uid){
                    Name_E->setText(list[1]);
                    Phone_E->setText(list[3]);
                    Address_E->setText(list[4]);
                    Balance_E->setText(list[5]);
                    break;
                }
                line = in.readLine();
            }
            pf.close();

            QMessageBox tip;
            tip.setText(tr("用户名不能为空！"));
            tip.exec();
            return;
        }
        QFile pf(DIR + "user.txt");
        if(!pf.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug()<<"Fail to open file";
            exit(0);
        }
        QTextStream in(&pf);
        QStringList infos;
        QString line = in.readLine();
        bool jdg = 1;
        QStringList fro_info;
        while(!line.isEmpty()){
            QStringList list = line.split(",");
            if(list[0]==Uid){
             //   qDebug()<<"1";
                fro_info<<list[1]<<list[3]<<list[4]<<list[5];
                infos<<(list[0]+","+Name_E->text()+","+list[2]+","+Phone_E->text()+","+Address_E->text()+","+list[5]+","+list[6]+"\n");
            }
            else{
                if(list[1] == Name_E->text()){
                    jdg=0;
                }
                infos<<(line + "\n");
            }
       //     qDebug()<<infos;
            line = in.readLine();
        }
        pf.close();
        if(jdg==0){
            Name_E->setText(fro_info[0]);
            Phone_E->setText(fro_info[1]);
            Address_E->setText(fro_info[2]);
            Balance_E->setText(fro_info[3]);
            QMessageBox tip;
            tip.setText(tr("用户名已存在"));
            tip.exec();
            return;
        }
        if(!pf.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)){
            qDebug()<<"Fail to open file";
            exit(0);
        }
        QTextStream out(&pf);
        for(int i=0;i<infos.size();i++){
            QString tmp = infos[i];
            out<<tmp;
        }
        pf.close();
        QMessageBox tip;
        tip.setText(tr("修改成功！"));
        tip.exec();
    }

}

void MyInfo::recharge(){
    if(Recharge->text()=="充值"){
        Balance->setText(tr("输入金额"));
        Balance_E->setEnabled(true);
        Recharge->setText(tr("确定"));
        Balance_E->setText("");
    }
    else{
        QString t = Balance_E->text();
        if(t.isEmpty()){
            QMessageBox tip;
            tip.setText(tr("充值金额不能为空！"));
            tip.exec();
            QString new_balance = get_balance();
            Balance_E->setText(new_balance);
            Balance_E->setEnabled(false);
            Balance->setText(tr("余额"));
            Recharge->setText(("充值"));
        }
        else{
            QString recharge_file = DIR + Uid + ".txt";
            QFile pf(recharge_file);
            if(!pf.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
                qDebug()<<"打开个人充值文件失败";
                exit(0);
            }
            QDateTime current_date_time =QDateTime::currentDateTime();
            QString current_date =current_date_time.toString("yyyy-MM-dd");
            string R = t.toStdString();
            string::size_type idx_of_point;
            idx_of_point = R.find(".");
            if (idx_of_point == R.npos) {
                R += ".0";
            }
            else if(idx_of_point == R.size()-1){
                R += "0";
            }
            else {
                R = R.substr(0, idx_of_point + 2);
            }
            QString new_record = current_date + "," + QString::fromStdString(R);
            QTextStream out(&pf);
            out<<new_record<<"\n";
            pf.close();
            QString new_balance = get_balance();
            Balance_E->setText(new_balance);
            Balance_E->setEnabled(false);
            Balance->setText(tr("余额"));
            Recharge->setText(("充值"));

            //写入文件
            QFile pf1(DIR + "user.txt");
            if(!pf1.open(QIODevice::ReadOnly | QIODevice::Text)){
                qDebug()<<"Fail to open file";
                exit(0);
            }
            QTextStream in(&pf1);
            QStringList infos;
            QString line = in.readLine();
            while(!line.isEmpty()){
                QStringList list = line.split(",");
                if(list[0]==Uid){
                    infos<<(list[0]+","+list[1]+","+list[2]+","+list[2]+","+list[4]+","+new_balance+","+list[6]+"\n");
                }
                else{
                    infos<<(line + "\n");
                }
                line = in.readLine();
            }
            pf1.close();
            if(!pf1.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)){
                qDebug()<<"Fail to open file";
                exit(0);
            }
            QTextStream out1(&pf1);
            for(int i=0;i<infos.size();i++){
                QString tmp = infos[i];
                out1<<tmp;
            }
            pf1.close();
        }
    }

}

void MyInfo::back(){
    this->close();
}

QString MyInfo::get_balance(){
    QString all_changes = "0";
    unordered_map<QString,QString> orders;  //数量，金额
    QFile pf(DIR + "order.txt");
    if(!pf.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"打开订单文件失败";
        exit(0);
    }
    QTextStream in(&pf);
    QString line = in.readLine();
    while(!line.isNull()){
        QStringList list = line.split(",");
    //    qDebug()<<line;
        //seller
        if(list[5] == Uid){
            //new num
            if(orders.find(list[3])==orders.end()){
                orders.insert(pair<QString,QString>(list[3],list[2]));
            }
            //already have this num
            else{
                QString tmp = orders[list[3]];
                tmp = tmp + "+" + list[2];
                orders[list[3]] = tmp;
            }
        }
        //buyer
        else if(list[6] == Uid){
            //new num
            if(orders.find(list[3])==orders.end()){
                QString tmp = "-" + list[2];
                orders.insert(pair<QString,QString>(list[3],tmp));
            }
            //already have this num
            else{
                QString tmp = orders[list[3]];
                tmp = tmp + "-" + list[2];
                orders[list[3]] = tmp;
            }

        }
        line = in.readLine();
    }
    pf.close();


    QString recharge_file = DIR + Uid + ".txt";
    QFile pf1(recharge_file);
    if(!pf1.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"打开个人充值文件失败";
        exit(0);
    }
    QTextStream in1(&pf1);
    QString line1 = in1.readLine();
    while (!line1.isNull()) {
        QStringList list = line1.split(",");
  //      qDebug()<<line1;
  //      qDebug()<<list[0];
        all_changes = all_changes + "+" + list[1];
        line1 = in1.readLine();
    }
    pf1.close();
    for(auto& it:orders){
     //   qDebug()<<"it.first "<<it.first<<"it.second "<<orders["10"];
        all_changes = all_changes + "+" + it.first + "*(" + it.second + ")";
    }
     //   qDebug()<<"2";
    cal C;
  //  qDebug()<<all_changes;
    string exp = all_changes.toStdString();
    string res = C.calculator(exp);
    return QString::fromStdString(res);
}
