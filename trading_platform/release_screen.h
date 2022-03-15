#ifndef RELEASE_SCREEN_H
#define RELEASE_SCREEN_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class Release_Screen : public QDialog
{
    Q_OBJECT

public:
    explicit Release_Screen(QWidget *parent = nullptr,QString uid = nullptr);
    ~Release_Screen();

private slots:
    void Release();
    void Back();

private:
    QString Uid,Mid;
    QLabel* name,*price,*num,*describe;
    QLineEdit* name_E,*price_E,*num_E,*describe_E;
    QPushButton* release,*back;
};

#endif // RELEASE_SCREEN_H
