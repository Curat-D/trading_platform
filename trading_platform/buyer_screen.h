#ifndef BUYER_SCREEN_H
#define BUYER_SCREEN_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTableView>
#include <QComboBox>

class Buyer_Screen : public QMainWindow
{
    Q_OBJECT

public:
    explicit Buyer_Screen(QWidget *parent = nullptr, QString id = nullptr);
    ~Buyer_Screen();


private slots:
    void View_Coms();
    void Search();
    void Buy_Com();
    void View_Orders();
    void View_Detail();
    void Back();
    void My_Sort();

private:
    QLabel* photo;
    QPushButton *view_coms, *buy_com, *search, *view_orders, *view_detail, *back, *my_sort;
    QLineEdit* search_E, *view_detail_E;
    QString Uid, Balance;
    QTableView* table;
    QComboBox* sort_attribute, *sort_order;
};

#endif // BUYER_SCREEN_H
