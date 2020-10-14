#include "myroomstab.h"
#include "user.h"
#include "room.h"

#include <QLabel>


MyRoomsTab::MyRoomsTab(QSqlDatabase &db, QWidget *parent) :
    followRoomLayout(new QVBoxLayout),
    adminRoomLayout(new QVBoxLayout),
    grid(new QGridLayout),
    db(db)
{
    updateLayouts();
    QSqlRelationalTableModel *roomsModel = new QSqlRelationalTableModel(nullptr, db);
    roomsModel->setTable("\"Users_Rooms\"");
    roomsModel->setRelation(1, QSqlRelation("\"Rooms\"", "\"RoomID\"", "\"RoomID\", \"Name\", \"OwnerID\", \"SubcategoryID\""));
    roomsModel->select();

    // Временная заглушка
    User user("user", QUuid("173a6805-0948-4b05-9fec-40dcb744aa39"), "827ccb0eea8a706c4c34a16891f84e7b");
    for (int i = 0; i < roomsModel->rowCount(); ++i) {
        QUuid roomId = roomsModel->record(i).value("RoomID").toUuid();
        QUuid userId = roomsModel->record(i).value("UserID").toUuid();
        QUuid ownerId = roomsModel->record(i).value("OwnerID").toUuid();
        QString name = roomsModel->record(i).value("Name").toString();
        bool isAdmin = roomsModel->record(i).value("IsAdmin").toBool();
        bool isFollowed = roomsModel->record(i).value("IsFollowed").toBool();

        if (userId == user.UserId) {
            Room room(roomId, name, ownerId);
            QLabel *roomLabel = new QLabel;
            roomLabel->setText(room.Name);
            if (userId == ownerId && isAdmin)
                adminRoomLayout->addWidget(roomLabel);
            else if (isFollowed)
                followRoomLayout->addWidget(roomLabel);
        }
    }
    // Разделитель
    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    grid->addLayout(adminRoomLayout, 0, 0);
    grid->addWidget(line, 1, 0);
    grid->addLayout(followRoomLayout, 2, 0);
    setLayout(grid);
}

MyRoomsTab::~MyRoomsTab()
{
    clearItems(followRoomLayout);
    clearItems(adminRoomLayout);
    clearItems(grid);
    delete grid;
}

void MyRoomsTab::updateLayouts()
{
    clearItems(adminRoomLayout);
    clearItems(followRoomLayout);
    clearItems(grid);
    adminRoomLayout = new QVBoxLayout;
    followRoomLayout = new QVBoxLayout;
    grid = new QGridLayout;
}
