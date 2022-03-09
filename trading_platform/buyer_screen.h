#ifndef BUYER_SCREEN_H
#define BUYER_SCREEN_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

class Buyer_Screen : public QMainWindow
{
    Q_OBJECT

public:
    explicit Buyer_Screen(QWidget *parent = nullptr, QString id = nullptr);
    ~Buyer_Screen();

private:
    QLabel* photo, *uid;
    QPushButton *view_coms, *buy_com, *search, *view_orders, *view_detail, *back;
    QString Uid, Balance;
};

#endif // BUYER_SCREEN_H
