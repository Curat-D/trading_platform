#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private:
    QLabel* photo;
    QLabel* Name;
    QLabel* Password;
    QPushButton* sign_in;
    QPushButton* sign_up;
    QLineEdit* name;
    QLineEdit* password;
    Ui::Login *ui;
};
#endif // LOGIN_H
