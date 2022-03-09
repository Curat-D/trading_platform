#include <QFile>
#include <QDebug>
#include "command.h"
#include "global.h"
Command::Command(QString uid){
    id = uid;
}

QStandardItemModel* Command::deal_with_cmd(QString cmd){
    QStringList list = cmd.split(" ");
    if(id == "admin"){
        if(list[0] == "SELECT"){
            if(list.size() == 4){
                return select_admin(list[3]);
            }
            else{
                return select_admin(list[3], list[5], list[7]);
            }
        }
    }

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
        return model;
    }


}

QStandardItemModel* Command::select_admin(QString table, QString attribute, QString value){
    return NULL;
}

QStandardItemModel* Command::update_admin(QString table, QStringList* change_attribute, QStringList* change_value, QString attribute, QString value){

}

QStandardItemModel* Command::insert(QString table, QStringList* value){}
