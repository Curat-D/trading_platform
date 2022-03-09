#ifndef COMMAND_H
#define COMMAND_H
#include <QString>
#include <QStandardItemModel>
class Command{
public:
    Command(QString uid);
    QStandardItemModel* deal_with_cmd(QString cmd);
    QStandardItemModel* select_admin(QString table);
    QStandardItemModel* select_admin(QString table, QString attribute, QString value);
    QStandardItemModel* update_admin(QString table, QStringList* change_attribute, QStringList* change_value, QString attribute, QString value);
    QStandardItemModel* insert(QString table, QStringList* value);
private:
    QString id;
};

#endif // COMMAND_H
