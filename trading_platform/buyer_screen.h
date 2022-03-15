#ifndef BUYER_SCREEN_H
#define BUYER_SCREEN_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTableView>

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

private:
    QLabel* photo;
    QPushButton *view_coms, *buy_com, *search, *view_orders, *view_detail, *back;
    QLineEdit* search_E, *view_detail_E;
    QString Uid, Balance;
    QTableView* table;
};

#endif // BUYER_SCREEN_H
