#include <QFile>
#include <QDebug>
#include <QHash>
#include <QMessageBox>
#include "command.h"
#include "global.h"


Command::Command(QString uid){
    id = uid;
    com_map.insert("商品ID",0);
    com_map.insert("名称",1);
    com_map.insert("价格",2);
    com_map.insert("数量",3);
    com_map.insert("描述",4);
    com_map.insert("卖家ID",5);
    com_map.insert("上架时间",6);
    com_map.insert("商品状态",7);

    user_map.insert("用户ID",0);
    user_map.insert("用户名",1);
    user_map.insert("密码",2);
    user_map.insert("联系方式",3);
    user_map.insert("地址",4);
    user_map.insert("钱包余额",5);
    user_map.insert("用户状态",6);
}

QStandardItemModel* Command::deal_with_cmd(QString cmd){
    QStringList list = cmd.split(" ");
    if(id == "admin"){
        if(list[0] == "SELECT"){
            if(list.size() == 4){
                return select_admin(list[3]);
            }
            else{
                return select_admin(list[3], list[7]);
            }
        }
        if(list[0] == "UPDATE"){
            QStringList change_att,change_val;
            int i=3;
            while(list[i]!="WHERE"){
                change_att<<list[i];
                change_val<<list[i+2];
                i+=3;
            }
            return update_admin(list[1],change_att,change_val,list[7],list[9]);
        }
    }
    else if(id[4] == 'B'){
        if(list[0] == "SELECT"){
            if(list.size() == 4){
                return select_B(list[3]);
            }
            else{
                return select_B(list[3], list[5],list[7]);
            }
        }
        else if(list[0] == "INSERT"){
            insert(list[2], list[4].mid(1,list[4].size()-2));
            return nullptr;
        }
        else{
            update_B(list[1],list[3],list[5],list[7],list[9]);
            return nullptr;
        }
    }
    else{
        if(list[0] == "SELECT"){
            if(list.size() == 4){
                return select_S(list[3]);
            }
            else{
                return select_S(list[3], list[5],list[7]);
            }
        }
        else if(list[0] == "INSERT"){
            insert(list[2], list[4].mid(1,list[4].size()-2));
            return nullptr;
        }
        else{
            update_S(list[1],list[3],list[5],list[7],list[9]);
            return nullptr;
        }
    }
    return nullptr;
}

QStandardItemModel* Command::select_admin(QString table){
    QStandardItemModel* model = new QStandardItemModel;
    QFile pf(DIR + table + ".txt");
    int row = 0;
    if(!pf.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"打开表文件失败";
        exit(0);
    }
    QTextStream in(&pf);
    QString line = in.readLine();
    if(table == "commodity"){
        model->setColumnCount(7);
        model->setHeaderData(0,Qt::Horizontal, "商品ID");
        model->setHeaderData(1,Qt::Horizontal, "名称");
        model->setHeaderData(2,Qt::Horizontal, "价格");
        model->setHeaderData(3,Qt::Horizontal, "上架时间");
        model->setHeaderData(4,Qt::Horizontal, "卖家ID");
        model->setHeaderData(5,Qt::Horizontal, "数量");
        model->setHeaderData(6,Qt::Horizontal, "商品状态");
        while(!line.isNull()){
            QStringList list = line.split(",");
            QList<QStandardItem*> tuple;
            tuple << new QStandardItem(list[0]) << new QStandardItem(list[1])
                  << new QStandardItem(list[2]) << new QStandardItem(list[6])
                  << new QStandardItem(list[5]) << new QStandardItem(list[3])
                  << new QStandardItem(list[7]);
            model->insertRow(row, tuple); //在第0行插入一条记录
            row++;
            line = in.readLine();
        }
        pf.close();
        return model;
    }
    else if(table == "order"){
        model->setColumnCount(7);
        model->setHeaderData(0,Qt::Horizontal, "订单ID");
        model->setHeaderData(1,Qt::Horizontal, "商品ID");
        model->setHeaderData(2,Qt::Horizontal, "交易单价");
        model->setHeaderData(3,Qt::Horizontal, "数量");
        model->setHeaderData(4,Qt::Horizontal, "交易时间");
        model->setHeaderData(5,Qt::Horizontal, "卖家ID");
        model->setHeaderData(6,Qt::Horizontal, "买家ID");
        while(!line.isNull()){
            QStringList list = line.split(",");
            QList<QStandardItem*> tuple;
            tuple << new QStandardItem(list[0]) << new QStandardItem(list[1])
                  << new QStandardItem(list[2]) << new QStandardItem(list[3])
                  << new QStandardItem(list[4]) << new QStandardItem(list[5])
                  << new QStandardItem(list[6]);
            model->insertRow(row, tuple); //在第0行插入一条记录
            row++;
            line = in.readLine();
        }
        pf.close();
        return model;
    }
    else if(table == "user"){
        model->setColumnCount(6);
        model->setHeaderData(0,Qt::Horizontal, "用户ID");
        model->setHeaderData(1,Qt::Horizontal, "用户名");
        model->setHeaderData(2,Qt::Horizontal, "联系方式");
        model->setHeaderData(3,Qt::Horizontal, "地址");
        model->setHeaderData(4,Qt::Horizontal, "钱包余额");
        model->setHeaderData(5,Qt::Horizontal, "用户状态");
        while(!line.isNull()){
            QStringList list = line.split(",");
            QList<QStandardItem*> tuple;
            tuple << new QStandardItem(list[0]) << new QStandardItem(list[1])
                  << new QStandardItem(list[3]) << new QStandardItem(list[4])
                  << new QStandardItem(list[5]) << new QStandardItem(list[6]);
            model->insertRow(row, tuple); //在第0行插入一条记录
            row++;
            line = in.readLine();
        }
        pf.close();
        return model;
    }
    return model;
}

QStandardItemModel* Command::select_admin(QString table, QString value){
    QStandardItemModel* model = new QStandardItemModel;
    QFile pf(DIR + table + ".txt");
    int row = 0;
    if(!pf.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"打开表文件失败";
        exit(0);
    }
    QTextStream in(&pf);
    QString line = in.readLine();
    if(table == "commodity"){
        qDebug()<<"2";
        model->setColumnCount(7);
        model->setHeaderData(0,Qt::Horizontal, "商品ID");
        model->setHeaderData(1,Qt::Horizontal, "名称");
        model->setHeaderData(2,Qt::Horizontal, "价格");
        model->setHeaderData(3,Qt::Horizontal, "上架时间");
        model->setHeaderData(4,Qt::Horizontal, "卖家ID");
        model->setHeaderData(5,Qt::Horizontal, "数量");
        model->setHeaderData(6,Qt::Horizontal, "商品状态");
        while(!line.isNull()){
            QStringList list = line.split(",");
            if(list[1].contains(value)){
                qDebug()<<"3";
                QList<QStandardItem*> tuple;
                tuple << new QStandardItem(list[0]) << new QStandardItem(list[1])
                      << new QStandardItem(list[2]) << new QStandardItem(list[6])
                      << new QStandardItem(list[5]) << new QStandardItem(list[3])
                      << new QStandardItem(list[7]);
                model->insertRow(row, tuple); //在第0行插入一条记录
                row++;
            }
            line = in.readLine();
        }
    }
    pf.close();
    return model;
}

QStandardItemModel* Command::update_admin(QString table, QStringList change_attribute, QStringList change_value, QString attribute, QString value){
    QStandardItemModel* model = new QStandardItemModel;
    QFile pf(DIR + table + ".txt");
    int row = 0;
    if(!pf.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"打开表文件失败";
        exit(0);
    }
    QTextStream in(&pf);
    QString line = in.readLine();
    QStringList info;
    if(table == "commodity"){
        model->setColumnCount(7);
        model->setHeaderData(0,Qt::Horizontal, "商品ID");
        model->setHeaderData(1,Qt::Horizontal, "名称");
        model->setHeaderData(2,Qt::Horizontal, "价格");
        model->setHeaderData(3,Qt::Horizontal, "上架时间");
        model->setHeaderData(4,Qt::Horizontal, "卖家ID");
        model->setHeaderData(5,Qt::Horizontal, "数量");
        model->setHeaderData(6,Qt::Horizontal, "商品状态");
        bool jdg=0;
        while(!line.isNull()){
            QStringList list = line.split(",");
            int att_idx=com_map[attribute];
            if(list[att_idx] == value){
                jdg=1;
                for(int k=0;k<change_attribute.size();k++){
                    list[com_map[change_attribute[k]]] = change_value[k];
                }
                info<<(list[0]+","+list[1]+","+list[2]+","+list[3]+","+list[4]+","+list[5]+","+list[6]+","+list[7]+"\n");
                QList<QStandardItem*> tuple;
                tuple << new QStandardItem(list[0]) << new QStandardItem(list[1])
                      << new QStandardItem(list[2]) << new QStandardItem(list[6])
                      << new QStandardItem(list[5]) << new QStandardItem(list[3])
                      << new QStandardItem(list[7]);
                model->insertRow(row, tuple); //在第0行插入一条记录
                row++;
            }
            else{
                info<<(line+"\n");
            }
            line = in.readLine();
        }
        pf.close();
        if(jdg==0){
            QMessageBox tip;
            tip.setText("未找到该商品");
            tip.exec();
            return model;
        }
        if(!pf.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)){
            qDebug()<<"Fail to open file";
            exit(0);
        }
        QTextStream out(&pf);
        for(int i=0;i<info.size();i++){
            QString tmp = info[i];
            out<<tmp;
        }
        pf.close();
        QMessageBox tip;
        tip.setText("下架成功!");
        tip.exec();
        return model;
    }
    else if(table == "user"){
        model->setColumnCount(6);
        model->setHeaderData(0,Qt::Horizontal, "用户ID");
        model->setHeaderData(1,Qt::Horizontal, "用户名");
        model->setHeaderData(2,Qt::Horizontal, "联系方式");
        model->setHeaderData(3,Qt::Horizontal, "地址");
        model->setHeaderData(4,Qt::Horizontal, "钱包余额");
        model->setHeaderData(5,Qt::Horizontal, "用户状态");
        bool jdg=0;
        while(!line.isNull()){
            QStringList list = line.split(",");
            int att_idx=user_map[attribute];
            if(list[att_idx] == value){
                jdg=1;
                for(int k=0;k<change_attribute.size();k++){
                    list[user_map[change_attribute[k]]] = change_value[k];
                }
                info<<(list[0]+","+list[1]+","+list[2]+","+list[3]+","+list[4]+","+list[5]+","+list[6]+"\n");
                QList<QStandardItem*> tuple;
                tuple << new QStandardItem(list[0]) << new QStandardItem(list[1])
                      << new QStandardItem(list[3]) << new QStandardItem(list[4])
                      << new QStandardItem(list[5]) << new QStandardItem(list[6]);
                model->insertRow(row, tuple); //在第0行插入一条记录
                row++;
            }
            else{
                info<<(line+"\n");
            }
            line = in.readLine();
        }
        pf.close();
        if(jdg==0){
            QMessageBox tip;
            tip.setText("未找到该用户");
            tip.exec();
            return model;
        }
        if(!pf.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)){
            qDebug()<<"Fail to open file";
            exit(0);
        }
        QTextStream out(&pf);
        for(int i=0;i<info.size();i++){
            QString tmp = info[i];
            out<<tmp;
        }
        pf.close();
        QMessageBox tip;
        tip.setText("封禁成功!");
        tip.exec();
        return model;
    }
    return model;
}

QStandardItemModel* Command::select_B(QString table){
    QStandardItemModel* model = new QStandardItemModel;
    QFile pf(DIR + table + ".txt");
    int row = 0;
    if(!pf.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"打开表文件失败";
        exit(0);
    }
    QTextStream in(&pf);
    QString line = in.readLine();
    if(table == "commodity"){
        model->setColumnCount(6);
        model->setHeaderData(0,Qt::Horizontal, "商品ID");
        model->setHeaderData(1,Qt::Horizontal, "名称");
        model->setHeaderData(2,Qt::Horizontal, "价格");
        model->setHeaderData(3,Qt::Horizontal, "数量");
        model->setHeaderData(4,Qt::Horizontal, "上架时间");
        model->setHeaderData(5,Qt::Horizontal, "卖家ID");
        while(!line.isNull()){
            QStringList list = line.split(",");
            if(list[7] == "销售中"){
                QList<QStandardItem*> tuple;
                QStandardItem* Price = new QStandardItem();
                Price->setData(list[2].toFloat(),Qt::DisplayRole);
                tuple << new QStandardItem(list[0]) << new QStandardItem(list[1])
                      << Price << new QStandardItem(list[3])
                      << new QStandardItem(list[6])<< new QStandardItem(list[5]);
                model->insertRow(row, tuple); //在第0行插入一条记录
                row++;
            }
            line = in.readLine();
        }
        pf.close();
        return model;
    }
    else if(table == "order"){
        model->setColumnCount(6);
        model->setHeaderData(0,Qt::Horizontal, "订单ID");
        model->setHeaderData(1,Qt::Horizontal, "商品ID");
        model->setHeaderData(2,Qt::Horizontal, "交易单价");
        model->setHeaderData(3,Qt::Horizontal, "数量");
        model->setHeaderData(4,Qt::Horizontal, "交易时间");
        model->setHeaderData(5,Qt::Horizontal, "卖家ID");
        while(!line.isNull()){
            QStringList list = line.split(",");
            if(list[6] == id.mid(0,4)){
                QList<QStandardItem*> tuple;
                QStandardItem* Price = new QStandardItem();
                Price->setData(list[2].toFloat(),Qt::DisplayRole);
                tuple << new QStandardItem(list[0]) << new QStandardItem(list[1])
                      << Price << new QStandardItem(list[3])
                      << new QStandardItem(list[4]) << new QStandardItem(list[5]);
                model->insertRow(row, tuple); //在第0行插入一条记录
                row++;
            }
            line = in.readLine();
        }
        pf.close();
        return model;
    }
    pf.close();
    return model;
}
QStandardItemModel* Command::select_B(QString table, QString attribute, QString value){
    QStandardItemModel* model = new QStandardItemModel;
    QFile pf(DIR + table + ".txt");
    int row = 0;
    if(!pf.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"打开表文件失败";
        exit(0);
    }
    QTextStream in(&pf);
    QString line = in.readLine();
    if(table == "commodity"){
        if(com_map[attribute] == 1){
            model->setColumnCount(6);
            model->setHeaderData(0,Qt::Horizontal, "商品ID");
            model->setHeaderData(1,Qt::Horizontal, "名称");
            model->setHeaderData(2,Qt::Horizontal, "价格");
            model->setHeaderData(3,Qt::Horizontal, "数量");
            model->setHeaderData(4,Qt::Horizontal, "上架时间");
            model->setHeaderData(5,Qt::Horizontal, "卖家ID");
            while(!line.isNull()){
                QStringList list = line.split(",");
                if(list[7] == "销售中")
                    if(list[1].contains(value)){
                        QList<QStandardItem*> tuple;
                        QStandardItem* Price = new QStandardItem();
                        Price->setData(list[2].toFloat(),Qt::DisplayRole);
                        tuple << new QStandardItem(list[0]) << new QStandardItem(list[1])
                              << Price << new QStandardItem(list[3])
                              << new QStandardItem(list[6])<< new QStandardItem(list[5]);
                        model->insertRow(row, tuple); //在第0行插入一条记录
                        row++;
                    }
                line = in.readLine();
            }
        }
        else if(com_map[attribute] == 0){
            model->setColumnCount(6);
            model->setHeaderData(0,Qt::Horizontal, "商品ID");
            model->setHeaderData(1,Qt::Horizontal, "名称");
            model->setHeaderData(2,Qt::Horizontal, "价格");
            model->setHeaderData(3,Qt::Horizontal, "上架时间");
            model->setHeaderData(4,Qt::Horizontal, "商品描述");
            model->setHeaderData(5,Qt::Horizontal, "卖家ID");
            bool jdg = 0;
            while(!line.isNull()){
                QStringList list = line.split(",");
                if(list[7] == "销售中")
                    if(list[0] == value){
                        jdg=1;
                        QList<QStandardItem*> tuple;
                        tuple << new QStandardItem(list[0]) << new QStandardItem(list[1])
                              << new QStandardItem(list[2]) << new QStandardItem(list[6])
                              << new QStandardItem(list[4])<< new QStandardItem(list[5]);
                        model->insertRow(row, tuple); //在第0行插入一条记录
                        row++;
                    }
                line = in.readLine();
            }
            if(jdg==0){
                QMessageBox tip;
                tip.setText("未找到该商品");
                tip.exec();
                return model;
            }
        }
    }
    pf.close();
    return model;
}
void Command::update_B(QString table, QString change_attribute, QString change_value, QString attribute, QString value){
    QFile pf(DIR + table + ".txt");
    if(!pf.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"打开表文件失败";
        exit(0);
    }
    QTextStream in(&pf);
    QString line = in.readLine();
    QStringList info;
    if(table == "commodity"){
        while(!line.isNull()){
            QStringList list = line.split(",");
            int att_idx=com_map[attribute];
      //      qDebug()<<list[att_idx];
            if(list[att_idx] == value){
                list[com_map[change_attribute]] = change_value;
                if(com_map[change_attribute] == 3 && change_value == "0")
                    list[7] = "已下架";
                info<<(list[0]+","+list[1]+","+list[2]+","+list[3]+","+list[4]+","+list[5]+","+list[6]+","+list[7]+"\n");
            }
            else{
                info<<(line+"\n");
            }
            line = in.readLine();
        }
        pf.close();
        if(!pf.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)){
            qDebug()<<"Fail to open file";
            exit(0);
        }
        QTextStream out(&pf);
        for(int i=0;i<info.size();i++){
            QString tmp = info[i];
            out<<tmp;
        }
        pf.close();
        return;
    }
}

QStandardItemModel* Command::select_S(QString table){
    QStandardItemModel* model = new QStandardItemModel;
    QFile pf(DIR + table + ".txt");
    int row = 0;
    if(!pf.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"打开表文件失败";
        exit(0);
    }
    QTextStream in(&pf);
    QString line = in.readLine();
    if(table == "commodity"){
        model->setColumnCount(6);
        model->setHeaderData(0,Qt::Horizontal, "商品ID");
        model->setHeaderData(1,Qt::Horizontal, "名称");
        model->setHeaderData(2,Qt::Horizontal, "价格");
        model->setHeaderData(3,Qt::Horizontal, "数量");
        model->setHeaderData(4,Qt::Horizontal, "上架时间");
        model->setHeaderData(5,Qt::Horizontal, "商品状态");
        while(!line.isNull()){
            QStringList list = line.split(",");
            if(list[5] == id.mid(0,4)){
                QList<QStandardItem*> tuple;
                QStandardItem* Price = new QStandardItem();
                Price->setData(list[2].toFloat(),Qt::DisplayRole);
                tuple << new QStandardItem(list[0]) << new QStandardItem(list[1])
                      << Price << new QStandardItem(list[3])
                      << new QStandardItem(list[6])<< new QStandardItem(list[7]);
                model->insertRow(row, tuple); //在第0行插入一条记录
                row++;
            }
            line = in.readLine();
        }
        pf.close();
        return model;
    }
    else if(table == "order"){
        model->setColumnCount(6);
        model->setHeaderData(0,Qt::Horizontal, "订单ID");
        model->setHeaderData(1,Qt::Horizontal, "商品ID");
        model->setHeaderData(2,Qt::Horizontal, "交易单价");
        model->setHeaderData(3,Qt::Horizontal, "数量");
        model->setHeaderData(4,Qt::Horizontal, "交易时间");
        model->setHeaderData(5,Qt::Horizontal, "买家ID");
        while(!line.isNull()){
            QStringList list = line.split(",");
            if(list[5] == id.mid(0,4)){
                QList<QStandardItem*> tuple;
                QStandardItem* Price = new QStandardItem();
                Price->setData(list[2].toFloat(),Qt::DisplayRole);
                tuple << new QStandardItem(list[0]) << new QStandardItem(list[1])
                      << Price << new QStandardItem(list[3])
                      << new QStandardItem(list[4]) << new QStandardItem(list[6]);
                model->insertRow(row, tuple); //在第0行插入一条记录
                row++;
            }
            line = in.readLine();
        }
        pf.close();
        return model;
    }
    pf.close();
    return model;
}
QStandardItemModel* Command::select_S(QString table, QString attribute, QString value){
    QStandardItemModel* model = new QStandardItemModel;
    QFile pf(DIR + table + ".txt");
    int row = 0;
    if(!pf.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"打开表文件失败";
        exit(0);
    }
    QTextStream in(&pf);
    QString line = in.readLine();
    if(table == "commodity"){
        if(com_map[attribute] == 1){
            model->setColumnCount(6);
            model->setHeaderData(0,Qt::Horizontal, "商品ID");
            model->setHeaderData(1,Qt::Horizontal, "名称");
            model->setHeaderData(2,Qt::Horizontal, "价格");
            model->setHeaderData(3,Qt::Horizontal, "数量");
            model->setHeaderData(4,Qt::Horizontal, "上架时间");
            model->setHeaderData(5,Qt::Horizontal, "卖家ID");
            while(!line.isNull()){
                QStringList list = line.split(",");
                if(list[7] == "销售中")
                    if(list[1].contains(value)){
                        QList<QStandardItem*> tuple;
                        QStandardItem* Price = new QStandardItem();
                        Price->setData(list[2].toFloat(),Qt::DisplayRole);
                        tuple << new QStandardItem(list[0]) << new QStandardItem(list[1])
                              << Price << new QStandardItem(list[3])
                              << new QStandardItem(list[6])<< new QStandardItem(list[5]);
                        model->insertRow(row, tuple); //在第0行插入一条记录
                        row++;
                    }
                line = in.readLine();
            }
        }
        else if(com_map[attribute] == 0){
            model->setColumnCount(6);
            model->setHeaderData(0,Qt::Horizontal, "商品ID");
            model->setHeaderData(1,Qt::Horizontal, "名称");
            model->setHeaderData(2,Qt::Horizontal, "价格");
            model->setHeaderData(3,Qt::Horizontal, "上架时间");
            model->setHeaderData(4,Qt::Horizontal, "商品描述");
            model->setHeaderData(5,Qt::Horizontal, "卖家ID");
            bool jdg = 0;
            while(!line.isNull()){
                QStringList list = line.split(",");
                if(list[7] == "销售中")
                    if(list[0] == value){
                        jdg=1;
                        QList<QStandardItem*> tuple;
                        QStandardItem* Price = new QStandardItem();
                        Price->setData(list[2].toFloat(),Qt::DisplayRole);
                        tuple << new QStandardItem(list[0]) << new QStandardItem(list[1])
                              << Price << new QStandardItem(list[6])
                              << new QStandardItem(list[4])<< new QStandardItem(list[5]);
                        model->insertRow(row, tuple); //在第0行插入一条记录
                        row++;
                    }
                line = in.readLine();
            }
            if(jdg==0){
                QMessageBox tip;
                tip.setText("未找到该商品");
                tip.exec();
                return model;
            }
        }
    }
    pf.close();
    return model;
}
void Command::update_S(QString table, QString change_attribute, QString change_value, QString attribute, QString value){
    QFile pf(DIR + table + ".txt");
    if(!pf.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"打开表文件失败";
        exit(0);
    }
    QTextStream in(&pf);
    QString line = in.readLine();
    QStringList info;

    if(table == "commodity"){
        while(!line.isNull()){
            QStringList list = line.split(",");
            int att_idx=com_map[attribute];
     //       qDebug()<<list[att_idx]<<" "<<value;
            if(list[att_idx] == value){
     //           qDebug()<<"2";
                list[com_map[change_attribute]] = change_value;;
                info<<(list[0]+","+list[1]+","+list[2]+","+list[3]+","+list[4]+","+list[5]+","+list[6]+","+list[7]+"\n");
            }
            else{
                info<<(line+"\n");
            }
            line = in.readLine();
        }
        pf.close();
        qDebug()<<"1";
        if(!pf.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)){
            qDebug()<<"Fail to open file";
            exit(0);
        }

        QTextStream out(&pf);
        for(int i=0;i<info.size();i++){
            QString tmp = info[i];
            out<<tmp;
        }
        pf.close();
        return;
    }
}


void Command::insert(QString table, QString value){
    QFile pf(DIR + table + ".txt");
    if(!pf.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        qDebug()<<"打开表文件失败";
        exit(0);
    }
    QTextStream out(&pf);
    out<<value<<"\n";
    pf.close();
}
