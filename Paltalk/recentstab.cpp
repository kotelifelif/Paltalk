#include "recentstab.h"
#include "user.h"
#include "room.h"
#include "stylemanager.h"

#include <QLabel>

RecentsTab::RecentsTab(QSqlDatabase &db, QWidget *parent):
    roomLayout(new QVBoxLayout),
    grid(new QGridLayout)
{
    updateLayouts();
    // Разделитель
    grid->addLayout(roomLayout, 0, 0);
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

        if (userId == user.UserId) {
            Room room(roomId, name, ownerId);
            QLabel *roomLabel = new QLabel;
            roomLabel->setStyleSheet(StyleManager::getLabelStyle());
            roomLabel->setText(room.Name);
            roomLayout->addWidget(roomLabel);
        }
    }
    setLayout(grid);
}

void RecentsTab::updateLayouts()
{
    clearItems(roomLayout);
    clearItems(grid);
    roomLayout = new QVBoxLayout;
    grid = new QGridLayout;
}


