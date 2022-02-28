#ifndef LOGUP_H
#define LOGUP_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTimer>
#include "global.h"


class Logup : public QDialog
{
    Q_OBJECT

public:
    Logup(QWidget *parent = nullptr);
    ~Logup();

private:
    QLabel* photo;
    QLabel* Name;
    QLabel* Password;
    QPushButton* sign_up;
    QPushButton* back;
    QLineEdit* name;
    QLineEdit* password;

private slots:
    void log_in();
    void checkAccount();

};

#endif // LOGUP_H
