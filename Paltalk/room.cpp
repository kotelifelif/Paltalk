#include "room.h"

Room::Room(const QUuid &roomId, const QString &name, const QUuid &ownerId, const QUuid &subcategoryId) :
    RoomId(roomId),
    Name(name),
    OwnerId(ownerId),
    SubcategoryId(subcategoryId)
{

}
