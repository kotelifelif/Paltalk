#include <QtWidgets>
#include<QVariant>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "category.h"
#include "subcategory.h"
#include "treeitem.h"
#include "treemodel.h"
#include "room.h"

//! [0]
MainWindow::MainWindow()
{
    grid = new QGridLayout;
    QWidget *widget = new QWidget;
    setCentralWidget(widget);
    widget->setLayout(grid);
    //grid->addWidget(widget);
    createActions();
    connectToDb();

    resize(400, 600);
    showAllRooms();
}

MainWindow::~MainWindow()
{
    db.close();
}

void MainWindow::createActions()
{
    recentsAction = new QAction(tr("Recents"), this);
    connect(recentsAction, &QAction::triggered, this, &MainWindow::showRecents);
    menuBar()->addAction(recentsAction);

    allRoomsAction = new QAction(tr("All rooms"), this);
    connect(allRoomsAction, &QAction::triggered, this, &MainWindow::showAllRooms);
    menuBar()->addAction(allRoomsAction);

    myRoomsAction = new QAction(tr("My rooms"), this);
    connect(myRoomsAction, &QAction::triggered, this, &MainWindow::showMyRooms);
    menuBar()->addAction(myRoomsAction);
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

void MainWindow::createMenus()
{

}

void MainWindow::showRecents()
{

}

void MainWindow::showAllRooms()
{
    // Очистить виджет
    for(int i = 0;i<grid->rowCount();i++) {
            for(int j = 0;j<grid->columnCount();j++) {
                QLayoutItem* item = grid->takeAt(i*grid->rowCount() + j);
                if(item != NULL) delete item;
            }
        }

    // Для отображения категорий и подкатегорий
    QVBoxLayout *categories_box = new QVBoxLayout;
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
    categoryView = new QTreeView();
    categoryView->setModel(categoryModel);
    grid->addWidget(categoryView, 0, 0);
    //showSubcategoryRooms();
    connect(categoryView->selectionModel(),
      SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
      SLOT(showSubcategoryRooms(const QItemSelection &, const QItemSelection &))
     );
}

void MainWindow::showMyRooms()
{

}

void MainWindow::showSubcategoryRooms(const QItemSelection &selectedItem, const QItemSelection &deselectedItem)
{
    Q_UNUSED(deselectedItem);
    // Для отображения комнат
    QVBoxLayout *roomLayout = new QVBoxLayout();
    grid->addLayout(roomLayout, 0, 1);
    //QVariant selectedSubcategory = categoryView->model()->data(index);
    QUuid id("39e4b5f7-5392-457f-a638-438e8c0b5864");
    QSqlRelationalTableModel *roomModel = new QSqlRelationalTableModel(nullptr, db);
    roomModel->setTable("\"Rooms\"");
    roomModel->setRelation(3, QSqlRelation("\"Subcategories\"", "\"SubcategoryID\"", "\"SubcategoryID\""));
    roomModel->select();
    for (int i = 0; i < roomModel->rowCount(); ++i) {
        QUuid roomId = roomModel->record(i).value("RoomID").toUuid();
        QString name = roomModel->record(i).value("Name").toString();
        QUuid ownerId = roomModel->record(i).value("OwnerID").toUuid();
        QUuid subcategoryId = roomModel->record(i).value("SubcategoryID").toUuid();

        if (id != subcategoryId)
            continue;

        Room room(roomId, name, ownerId, subcategoryId);
        QLabel *roomLabel = new QLabel;
        roomLabel->setText(room.Name);
        roomLayout->addWidget(roomLabel);
    }
}


