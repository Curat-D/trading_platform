#ifndef MODIFY_SCREEN_H
#define MODIFY_SCREEN_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
class Modify_Screen : public QDialog
{
    Q_OBJECT

public:
    explicit Modify_Screen(QWidget *parent = nullptr,QString mid = nullptr);
    ~Modify_Screen();

private slots:
    void Change();
    void Back();

private:
    QString Mid;
    QLabel* name,*price,*describe;
    QLineEdit* name_E,*price_E,*describe_E;
    QPushButton* change,*back;
};

#endif // MODIFY_SCREEN_H
