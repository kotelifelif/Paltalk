#include "abstracttab.h"
#include "stylemanager.h"

#include <QLayout>
#include <QtWidgets>

AbstractTab::AbstractTab(QWidget *parent) :
    QWidget(parent),
    roomItemLayout(new QHBoxLayout)
{
}

AbstractTab::~AbstractTab()
{
}

void AbstractTab::clearItems(QLayout *layout)
{
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr) {
        if (child->layout())
            clearItems(child->layout());
        delete child->widget(); // delete the widget
        delete child;   // delete the layout item
    }
}

QLabel* AbstractTab::getLabelImage(const QString &path, const int width, const int height, const QString &objectName)
{
    QImage image(path);
    QLabel *imageLabel = new QLabel;
    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->setObjectName(objectName);
    return imageLabel;
}

void AbstractTab::addRoom(QVBoxLayout *layout, QString &name)
{
    // Добавим комнату как вприложении
    roomItemLayout = new QHBoxLayout;
    roomItemLayout->setSpacing(0);
    roomItemLayout->setMargin(0);
    // Основная иконка
    // Не забыть добавить stylesheets к roomItem
    QImage image(":/images/room_icon.png");
    QLabel *roomIcon = getLabelImage(":/images/room_icon.png",
                                     25, 25, "Icon");
    roomIcon->setStyleSheet(StyleManager::getIconStyle());
    roomItemLayout->addWidget(roomIcon);

    QLabel *roomLabel = new QLabel;
    roomLabel->setStyleSheet(StyleManager::getLabelStyle());
    roomLabel->setText(name);
    roomItemLayout->addWidget(roomLabel);

    // Deluxe
    QLabel *deluxeIcon = getLabelImage(":/images/deluxe_icon.png",
                                        25, 25, "Icon");
    deluxeIcon->setStyleSheet(StyleManager::getIconStyle());
    roomItemLayout->addWidget(deluxeIcon);

    QLabel *membersIcon = getLabelImage(":/images/members_icon.png",
                                        25, 25, "Icon");
    membersIcon->setStyleSheet(StyleManager::getIconStyle());
    roomItemLayout->addWidget(membersIcon);
    QLabel *membersCountLabel = new QLabel("1");
    membersCountLabel->setStyleSheet(StyleManager::getLabelStyle());
    roomItemLayout->addWidget(membersCountLabel);

    QLabel *videoIcon = getLabelImage(":/images/video_icon.png",
                                        25, 25, "Icon");
    videoIcon->setStyleSheet(StyleManager::getIconStyle());
    roomItemLayout->addWidget(videoIcon);
    QLabel *videoCountLabel = new QLabel("0");
    videoCountLabel->setStyleSheet(StyleManager::getLabelStyle());
    roomItemLayout->addWidget(videoCountLabel);

    QLabel *followersIcon = getLabelImage(":/images/followers_icon.png",
                                        25, 25, "Icon");
    followersIcon->setStyleSheet(StyleManager::getIconStyle());
    roomItemLayout->addWidget(followersIcon);
    QLabel *followersCountLabel = new QLabel("0");
    followersCountLabel->setStyleSheet(StyleManager::getLabelStyle());
    roomItemLayout->addWidget(followersCountLabel);

    layout->addLayout(roomItemLayout);
}
