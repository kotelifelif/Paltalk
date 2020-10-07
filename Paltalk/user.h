#ifndef USER_H
#define USER_H

#include <QString>
#include <QUuid>

class User
{
public:
    User(const QString &nickname = QString(), const QUuid &userId = QUuid(), const QString &password = QString());
    QString Nickname;
    QUuid UserId;
    QString Password;

};

#endif // USER_H
