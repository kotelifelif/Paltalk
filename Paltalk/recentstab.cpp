#include "recentstab.h"
#include "user.h"
#include "room.h"
#include "stylemanager.h"

#include <QLabel>
#include <QRadioButton>

RecentsTab::RecentsTab(QSqlDatabase &db, QWidget *parent):
    roomLayout(new QVBoxLayout),
    grid(new QGridLayout)
{
    updateLayouts();

    QHBoxLayout *titleLayout = new QHBoxLayout;
    grid->addLayout(titleLayout, 0, 0);

    QLabel *titleLabel = new QLabel;
    titleLabel->setText("Recents");
    titleLayout->addWidget(titleLabel);
    titleLayout->addSpacerItem(new QSpacerItem(660, 10));

    QRadioButton *allButton = new QRadioButton;
    allButton->setStyleSheet(StyleManager::getAllButtonStyle() + StyleManager::getToolTipStyle());
    allButton->setToolTip("Show all chat rooms");
    allButton->setObjectName("All");
    titleLayout->addWidget(allButton);

    QRadioButton *openButton = new QRadioButton;
    openButton->setObjectName("Open");
    openButton->setToolTip("Only show open chat rooms");
    openButton->setStyleSheet(StyleManager::getOpenButtonStyle() + StyleManager::getToolTipStyle());
    titleLayout->addWidget(openButton);

    grid->addLayout(roomLayout, 1, 0);
    titleLabel->setObjectName("TitleLabel");
    titleLabel->setStyleSheet(StyleManager::getTitleStyle());
    roomLayout->addWidget(titleLabel);

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
            addRoom(roomLayout, room.Name);
            //
            //roomLayout->addWidget(roomLabel);
        }
    }
    setLayout(grid);
}

RecentsTab::~RecentsTab()
{
    clearItems(grid);
    delete grid;
}

void RecentsTab::updateLayouts()
{
    clearItems(roomLayout);
    clearItems(grid);
    roomLayout = new QVBoxLayout;
    grid = new QGridLayout;
}




