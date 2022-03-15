#ifndef COMMAND_H
#define COMMAND_H
#include <QString>
#include <QStandardItemModel>
class Command{
public:
    Command(QString uid);
    QStandardItemModel* deal_with_cmd(QString cmd);
    QStandardItemModel* select_admin(QString table);
    QStandardItemModel* select_admin(QString table, QString value);
    QStandardItemModel* update_admin(QString table, QStringList change_attribute, QStringList change_value, QString attribute, QString value);
    QStandardItemModel* select_B(QString table);
    QStandardItemModel* select_B(QString table, QString attribute, QString value);
    void update_B(QString table, QString change_attribute, QString change_value, QString attribute, QString value);

    QStandardItemModel* select_S(QString table);
    QStandardItemModel* select_S(QString table, QString attribute, QString value);
    void update_S(QString table, QString change_attribute, QString change_value, QString attribute, QString value);

    void insert(QString table, QString value);
private:
    QString id;
    QHash<QString, int> com_map;
    QHash<QString, int> user_map;
};

#endif // COMMAND_H
