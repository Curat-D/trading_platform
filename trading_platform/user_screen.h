#ifndef USER_SCREEN_H
#define USER_SCREEN_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include "global.h"
//#include "login.h"

class User_Screen : public QMainWindow
{
    Q_OBJECT

public:
    explicit User_Screen(QWidget *parent = nullptr);
    ~User_Screen();

private slots:
//    void Buyer();
 //   void Seller();
  //  void PersonalInfor();
    void Log_out();

signals:
    void mySignal2();

private:
    QLabel* photo, *Name;
    QPushButton *buyer, *seller, *personal_info;
    QString uid;

    friend class Login;
};


#endif // USER_SCREEN_H
