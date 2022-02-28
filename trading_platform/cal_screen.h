#ifndef CAL_SCREEN_H
#define CAL_SCREEN_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "Calculator.h"


class Cal_Screen : public QDialog
{
    Q_OBJECT

public:
    explicit Cal_Screen(QWidget *parent = nullptr);
    ~Cal_Screen();

private:
    QLineEdit* exp_E,*res_E;
    QLabel* exp,*res;
    QPushButton* calculate,*reset,*back;

private slots:
    void Cal();
    void Reset();
    void Back();
};

#endif // CAL_SCREEN_H
