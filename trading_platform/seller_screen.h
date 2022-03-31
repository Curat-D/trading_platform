#ifndef SELLER_SCREEN_H
#define SELLER_SCREEN_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTableView>
#include <QComboBox>

class Seller_Screen : public QMainWindow
{
    Q_OBJECT

public:
    explicit Seller_Screen(QWidget *parent = nullptr, QString id = nullptr);
    ~Seller_Screen();

private slots:
    void View_Coms();
    void Release_Com();
    void Modify();
    void View_Orders();
    void Withdraw_Com();
    void Back();
    void My_Sort();

private:
    QLabel* photo;
    QPushButton *view_coms, *release_com, *modify, *view_orders, *withdraw_com, *back,*my_sort;
    QLineEdit* modify_E,*withdraw_com_E;
    QString Uid;
    QTableView* table;
    QComboBox* sort_attribute, *sort_order;
};

#endif // SELLER_SCREEN_H
