#include "users.h"

Users::Users(QWidget *parent):
    QMainWindow(parent)
{
}

Users::~Users()
{

}

void Users::set_info(QString uid){
    Uid = uid;
}

QString Users::get_uid(){
    return Uid;
}


