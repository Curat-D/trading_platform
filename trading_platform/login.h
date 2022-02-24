#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "logup.h"
#include "admin_screen.h"
#include "user_screen.h"

class Login : public QDialog
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();


private slots:
    void checkPassword();
    void log_up();
    void log_in();

private:
    QLabel* photo;
    QLabel* Name;
    QLabel* Password;
    QPushButton* sign_in;
    QPushButton* sign_up;
    QLineEdit* name;
    QLineEdit* password;
    User_Screen* user_window;
};
#endif // LOGIN_H
