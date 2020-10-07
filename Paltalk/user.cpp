#include "user.h"


User::User(const QString &nickname, const QUuid &userId, const QString &password) :
    Nickname(nickname),
    UserId(userId),
    Password(password)
{

}
