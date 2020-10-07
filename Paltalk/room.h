#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <QUuid>

class Room : public QObject
{
public:
    Room(const QUuid &roomId = QUuid(), const QString &name = QString(), const QUuid &ownerId = QString(), const QUuid &subcategoryId = QUuid());
    QUuid RoomId;
    QString Name;
    QUuid OwnerId;
    QUuid SubcategoryId;
};

#endif // ROOM_H
