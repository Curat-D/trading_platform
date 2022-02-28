#ifndef USERS_H
#define USERS_H

#include <QMainWindow>


class Users : public QMainWindow
{
    Q_OBJECT

public:
    explicit Users(QWidget *parent = nullptr);
    ~Users();
    void set_info(QString uid);
    QString get_uid();
private:
    QString Uid;
    QString Name;
    QString Password;
    QString Phone;
    QString Address;
    QString Balance;
};

#endif // USERS_H
