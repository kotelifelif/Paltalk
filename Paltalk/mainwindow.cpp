#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "category.h"
#include "subcategory.h"
#include "treeitem.h"
#include "treemodel.h"
#include "room.h"
#include "user.h"
#include "stylemanager.h"
#include "allroomstab.h"
#include "recentstab.h"
#include "myroomstab.h"

#include <QtWidgets>
#include<QVariant>

MainWindow::MainWindow()
{
    grid = new QGridLayout;
    roomLayout = new QVBoxLayout;
    adminRoomLayout = new QVBoxLayout;
    followRoomLayout = new QVBoxLayout;
    QWidget *widget = new QWidget;
    setCentralWidget(widget);
    widget->setLayout(grid);
    setStyleSheet(StyleManager::getMainWindowStyle());

    connectToDb();
    createActions();

    resize(870, 630);
}

MainWindow::~MainWindow()
{
    db.close();
    delete tabWidget;
}

void MainWindow::createActions()
{
    searchEdit = new QLineEdit;
    //searchEdit->setText("Search Room");
    QFont tabFont;

    tabWidget = new QTabWidget;
    tabWidget->setStyleSheet(StyleManager::getTabWidgetStyle());
    tabWidget->setFont(tabFont);
    tabWidget->addTab(new RecentsTab(db), "Recents");
    tabWidget->addTab(new AllRoomsTab(db), "All Rooms");
    tabWidget->addTab(new MyRoomsTab(db), "My Rooms");

    QWidget *cornerWidget = new QWidget;
    cornerWidget->setObjectName("Corner");
    cornerWidget->setStyleSheet(StyleManager::getCornerWidgetStyle());
    QHBoxLayout *cornerLayout = new QHBoxLayout(cornerWidget);
    cornerLayout->addWidget(searchEdit);
    QCheckBox *adultFilter = new QCheckBox;
    cornerLayout->addWidget(adultFilter);
    tabWidget->setCornerWidget(cornerWidget);

    grid->addWidget(tabWidget, 0, 0);
}

void MainWindow::connectToDb()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("Paltalk");
    db.setUserName("postgres");
    db.setHostName("localhost");
    db.setPassword("12345");
    db.open();
}

void MainWindow::updateLayouts()
{
    clearItems(roomLayout);
    clearItems(followRoomLayout);
    clearItems(adminRoomLayout);
    clearItems(grid);
    roomLayout = new QVBoxLayout;
    followRoomLayout = new QVBoxLayout;
    adminRoomLayout = new QVBoxLayout;
}

void MainWindow::clearItems(QLayout *layout)
{
    // Очистить виджет
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr) {
        delete child->widget(); // delete the widget
        delete child;   // delete the layout item
    }
}



