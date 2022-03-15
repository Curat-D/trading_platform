#ifndef BUY_SCREEN_H
#define BUY_SCREEN_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
class Buy_Screen : public QDialog
{
    Q_OBJECT

public:
    explicit Buy_Screen(QWidget *parent = nullptr,QString uid = nullptr);
    ~Buy_Screen();

private slots:
    void buy();
    void back();

private:
   QString Uid;
   QLabel* Name,*Num;
   QLineEdit* Name_E,*Num_E;
   QPushButton* Buy,*Back;
};

#endif // BUY_SCREEN_H
