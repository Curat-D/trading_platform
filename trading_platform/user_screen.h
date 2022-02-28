#ifndef USER_SCREEN_H
#define USER_SCREEN_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include "users.h"
#include "global.h"

class User_Screen : public Users
{
    Q_OBJECT

public:
    explicit User_Screen(QWidget *parent = nullptr);
    ~User_Screen();

private slots:
//    void Buyer();
 //   void Seller();
    void PersonalInfo();
    void Log_out();

private:
    QLabel* photo;
    QPushButton *buyer, *seller, *personal_info;
    QString Uid;

};


#endif // USER_SCREEN_H
