#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

class Login : public QDialog
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();


private slots:
    void checkPassword();
    void log_up();
    void calculator();

private:
    QLabel* photo;
    QLabel* Name;
    QLabel* Password;
    QPushButton* sign_in;
    QPushButton* sign_up;
    QPushButton* cal;
    QLineEdit* name;
    QLineEdit* password;
};
#endif // LOGIN_H
