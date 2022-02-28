#include <QMessageBox>
#include <QDebug>
#include "cal_screen.h"
#include "global.h"

Cal_Screen::Cal_Screen(QWidget *parent) :
    QDialog(parent)
{
    setFixedSize(INFO_WINDOW_WIDTH, INFO_WINDOW_HEIGHT);
    setWindowTitle("淘淘");
    setWindowIcon(QIcon(":/image/icon.jpg"));
    //background
    QPixmap background1;
    background1.load(":/image/background1.jpg");
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(background1));
    this->setPalette(palette);

    exp = new QLabel(this);
    exp->setText(tr("请输入表达式："));
    exp->setGeometry(QRect(40,20,200,30));

    res = new QLabel(this);
    res->setText(tr("结果："));
    res->setGeometry((QRect(40,100,200,30)));

    exp_E = new QLineEdit(this);
    exp_E->setGeometry(QRect(40,60,300,30));

    res_E = new QLineEdit(this);
    res_E->setGeometry(QRect(40,140,300,30));
    res_E->setEnabled(false);

    calculate = new QPushButton(this);
    calculate->setText(tr("计算"));
    calculate->setGeometry(QRect(80,180,60,30));

    reset = new QPushButton(this);
    reset->setText(tr("清空"));
    reset->setGeometry(QRect(140,180,60,30));

    back = new QPushButton(this);
    back->setText(tr("返回"));
    back->setGeometry(QRect(200,180,60,30));

    connect(calculate,SIGNAL(clicked()),this,SLOT(Cal()));
    connect(reset,SIGNAL(clicked()),this,SLOT(Reset()));
    connect(back,SIGNAL(clicked()),this,SLOT(Back()));
}

Cal_Screen::~Cal_Screen()
{
    delete res;
    delete exp;
    delete res_E;
    delete exp_E;
    delete calculate;
    delete reset;
    delete back;
}

void Cal_Screen::Cal(){
    qDebug()<<"1";
    QString s=exp_E->text();
    qDebug()<<s;
    if(s.isEmpty()){
        res_E->setText("");
        QMessageBox tip;
        tip.setText(tr("表达式不能为空！"));
        tip.exec();
        return;
    }
    string EXP = s.toStdString();
    cal Calculator;
    string RES = Calculator.calculator(EXP);
    QString res = QString::fromStdString(RES);
    qDebug()<<res;
    res_E->setText(res);
}

void Cal_Screen::Reset(){
    exp_E->setText("");
    res_E->setText("");
}

void Cal_Screen::Back(){
    this->close();
}
