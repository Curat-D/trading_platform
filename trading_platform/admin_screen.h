#ifndef ADMIN_SCREEN_H
#define ADMIN_SCREEN_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include "global.h"

class Admin_Screen : public QMainWindow
{
    Q_OBJECT

public:
    explicit Admin_Screen(QWidget *parent = nullptr);
    ~Admin_Screen();

private slots:
    void View_All_Coms();
    void Search();
    void Withdraw_com();
    void View_all_orders();
    void View_all_users();
    void Ban_user();
    void Log_out();

signals:
    void mySignal1();

private:
    QLabel* photo;
    QPushButton *view_all_coms, *search, *withdraw_com, *view_all_orders, *view_all_users, *ban_user, *log_out;

};

#endif // ADMIN_SCREEN_H
