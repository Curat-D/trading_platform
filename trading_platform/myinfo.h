#ifndef MYINFO_H
#define MYINFO_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
class MyInfo : public QDialog
{
    Q_OBJECT

public:
    explicit MyInfo(QWidget *parent = nullptr,QString uid = nullptr);
    ~MyInfo();
    QString get_balance();

private slots:
    void change();
    void recharge();
    void back();

private:
    QString Uid;
    QLabel* Name, *Phone, *Address, *Balance;
    QLineEdit* Name_E, *Phone_E, *Address_E, *Balance_E;
    QPushButton* Change, *Recharge, *Back;
};

#endif // MYINFO_H
