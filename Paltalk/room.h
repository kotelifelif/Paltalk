#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <QUuid>

class Room : public QObject
{
public:
    Room(const QUuid &roomId = nullptr, const QString &name = nullptr, const QUuid &ownerId = nullptr, const QUuid &subcategoryId = nullptr);
    QUuid RoomId;
    QString Name;
    QUuid OwnerId;
    QUuid SubcategoryId;
};

#endif // ROOM_H
