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

    createActions();
    connectToDb();
    //this->setStyleSheet(StyleManager::getWidgetStyle());

    resize(870, 630);
    //showAllRooms();
}

MainWindow::~MainWindow()
{
    db.close();
}

void MainWindow::createActions()
{
    recentsAction = new QAction(tr("Recents"), this);
    connect(recentsAction, &QAction::triggered, this, &MainWindow::showRecents);
    //menuBar()->addAction(recentsAction);

    allRoomsAction = new QAction(tr("All rooms"), this);
    connect(allRoomsAction, &QAction::triggered, this, &MainWindow::showAllRooms);
    //menuBar()->addAction(allRoomsAction);

    myRoomsAction = new QAction(tr("My rooms"), this);
    connect(myRoomsAction, &QAction::triggered, this, &MainWindow::showMyRooms);
    //menuBar()->addAction(myRoomsAction);


    QFont menuBarFont;
    menuBarFont.setPointSize(11);
    //menuBar()->setFont(menuBarFont);
    //menuBar()->setStyleSheet();

    recentsButton = new QWidget;
    //recentsButton->setText("Recents");
    //recentsButton->setStyleSheet(StyleManager::getToolButtonStyle());
    //recentsButton->setFont(menuBarFont);

    allRoomsButton = new QWidget;
    //allRoomsButton->setText("All Rooms");
    //allRoomsButton->setStyleSheet(StyleManager::getToolButtonStyle());
    //allRoomsButton->setFont(menuBarFont);

    myRoomsButton = new QWidget;
    //myRoomsButton->setText("My Rooms");
    //myRoomsButton->setStyleSheet(StyleManager::getToolButtonStyle());
    //myRoomsButton->setFont(menuBarFont);

    searchEdit = new QLineEdit;
    //searchEdit->setText("Search Room");

    tabWidget = new QTabWidget;
    tabWidget->addTab(new RecentsTab(), "Recents");
    tabWidget->addTab(new AllRoomsTab(), "All Rooms");
    tabWidget->addTab(new MyRoomsTab(), "My Rooms");
    grid->addWidget(tabWidget, 0, 0);
    //connect(allRoomsButton, &QAction::triggered, this, &MainWindow::showMyRooms);
    //grid->addLayout(tabWidget, 0, 0, Qt::AlignTop);
    //menuLayout->addWidget(recentsButton);;
    //menuLayout->addWidget(allRoomsButton);
    //menuLayout->addWidget(myRoomsButton);
    //menuLayout->addWidget(searchEdit);
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

void MainWindow::showRecents()
{
    updateLayouts();
    // Разделитель
    grid->addLayout(roomLayout, 0, 0);
    QSqlRelationalTableModel *roomsModel = new QSqlRelationalTableModel(nullptr, db);
    roomsModel->setTable("\"Users_Rooms\"");
    roomsModel->setRelation(1, QSqlRelation("\"Rooms\"", "\"RoomID\"", "\"Name\", \"OwnerID\", \"SubcategoryID\""));
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
            roomLabel->setText(room.Name);
            roomLayout->addWidget(roomLabel);
        }
    }
}

void MainWindow::showAllRooms()
{
    updateLayouts();
    // Для отображения категорий и подкатегорий
    // Выбор категорий
    QSqlRelationalTableModel *categoriesModel = new QSqlRelationalTableModel(nullptr, db);
    categoriesModel->setTable("\"Categories\"");
    categoriesModel->select();


    // Выбор подкатегорий
    TreeModel *categoryModel = new TreeModel;
    QStringList cols;
    cols << "Name" << "CategoryID" << "SubcategoryID";
    categoryModel->setColumns(cols);
    for (int i = 0; i < categoriesModel->rowCount(); ++i) {
        QSqlRelationalTableModel *subcategoriesModel = new QSqlRelationalTableModel(nullptr, db);
        subcategoriesModel->setTable("\"Subcategories\"");
        subcategoriesModel->setRelation(2, QSqlRelation("\"Categories\"", "\"CategoryID\"", "\"CategoryID\""));
        subcategoriesModel->select();


        QUuid categoryId = categoriesModel->record(i).value("CategoryID").toUuid();
        QString name = categoriesModel->record(i).value("Name").toString();
        Category *category = new Category(categoryId, name);
        QVector<Category> categoryData;

        category->setProperty("Name", name);
        category->setProperty("CategoryID", categoryId);
        categoryModel->addItem(category, QModelIndex());
        for (int j = 0; j < subcategoriesModel->rowCount(); ++j) {
            name = subcategoriesModel->record(j).value("Name").toString();
            QUuid subcategoryId = subcategoriesModel->record(j).value("SubcategoryID").toUuid();
            categoryId = subcategoriesModel->record(j).value("CategoryID").toUuid();

            if (categoryId != category->CategoryId)
                continue;

            Subcategory *subcategory = new Subcategory(subcategoryId, categoryId, name);
            subcategory->setParent(category);
            subcategory->setProperty("Name", name);
            subcategory->setProperty("CategoryID", categoryId);
            subcategory->setProperty("SubcategoryID", subcategoryId);
        }
    }

    categoryView = new QTreeView;
    categoryView->setModel(categoryModel);
    categoryView->expandAll();

    connect(categoryView->selectionModel(),
      SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
      SLOT(showSubcategoryRooms(const QItemSelection &, const QItemSelection &))
     );
    int row = 0;
    // Ищем категорию с подкатегорией
    QModelIndex parent(categoryView->model()->index(row, 0));
    while(parent != QModelIndex()) {
        if (parent.child(0, 0) != QModelIndex())
            break;
        ++row;
        parent = categoryView->model()->index(row, 0);
    }

    QModelIndex topLeft(parent.child(row, 0));
    QModelIndex bottomRight(parent.child(row, parent.column() + 1));
    QItemSelection selection(topLeft, bottomRight);
    categoryView->selectionModel()->select(selection,
                                           QItemSelectionModel::SelectionFlag::Select | QItemSelectionModel::SelectionFlag::Rows);
    grid->addWidget(categoryView, 1, 0, Qt::AlignJustify);
    grid->addLayout(roomLayout, 1, 1, Qt::AlignJustify);
}

void MainWindow::showMyRooms()
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
}

void MainWindow::showSubcategoryRooms(const QItemSelection &selectedItem, const QItemSelection &deselectedItem)
{
    Q_UNUSED(deselectedItem);
    clearItems(roomLayout);
    // Для отображения комнат
    QList<QModelIndex> indexes = selectedItem.indexes();
    QSqlRelationalTableModel *roomModel = new QSqlRelationalTableModel(nullptr, db);
    roomModel->setTable("\"Rooms\"");
    roomModel->setRelation(3, QSqlRelation("\"Subcategories\"", "\"SubcategoryID\"", "\"SubcategoryID\""));
    roomModel->select();
    for (int i = 0; i < roomModel->rowCount(); ++i) {
        QUuid roomId = roomModel->record(i).value("RoomID").toUuid();
        QString name = roomModel->record(i).value("Name").toString();
        QUuid ownerId = roomModel->record(i).value("OwnerID").toUuid();
        QUuid roomSubcategoryId = roomModel->record(i).value("SubcategoryID").toUuid();

        QModelIndex index = selectedItem.indexes().at(2);
        QUuid subcategoryId = index.data().toUuid();

        if (subcategoryId != roomSubcategoryId)
            continue;

        Room room(roomId, name, ownerId, subcategoryId);
        QLabel *roomLabel = new QLabel;
        roomLabel->setText(room.Name);
        roomLayout->addWidget(roomLabel);
    }
}


