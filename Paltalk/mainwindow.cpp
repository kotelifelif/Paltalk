#include <QtWidgets>
#include<QVariant>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "category.h"
#include "subcategory.h"
#include "treeitem.h"
#include "treemodel.h"


//! [0]
MainWindow::MainWindow()
{
    grid = new QGridLayout;
    QWidget *widget = new QWidget;
    setCentralWidget(widget);
    //grid->addWidget(widget);
    createActions();
    connectToDb();

    resize(400, 600);
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
    //model->setRelation(0, QSqlRelation("\"Subcategories\"", "\"CategoryID\"", "\"Name\""));
    categoriesModel->select();
    //TreeItem item;
    //QTreeView *view = new QTreeView();
    QTreeWidget *categoryWidget = new QTreeWidget();
    //view->setModel(model);
    //view->show();

    // Выбор подкатегорий
    TreeModel *categoryModel = new TreeModel;
    QStringList cols;
    cols << "Name" << "CategoryID" << "SubcategoryID";
    categoryModel->setColumns(cols);
    for (int i = 0; i < categoriesModel->rowCount(); ++i) {
        QSqlRelationalTableModel *subcategoriesModel = new QSqlRelationalTableModel(nullptr, db);
        subcategoriesModel->setTable("\"Subcategories\"");
        subcategoriesModel->setRelation(2, QSqlRelation("\"Subcategories\"", "\"CategoryID\"", "\"Name\""));

        QString name = categoriesModel->record(i).value("Name").toString();
        QUuid categoryId = categoriesModel->record(i).value("CategoryID").toUuid();
        Category *category = new Category(categoryId, name);
        QVector<Category> categoryData;
        //categoryData.append(category);

        TreeItem parentItem(QVariant::fromValue(category));
        QVector<Subcategory> subcategoryData;
        QObject *cat = new QObject();
        categoryModel->addItem(cat, QModelIndex());
        for (int j = 0; j < subcategoriesModel->rowCount(); ++j) {
            QString name = subcategoriesModel->record(j).value("Name").toString();
            QUuid categoryId = subcategoriesModel->record(j).value("CategoryID").toUuid();
            QUuid subcategoryId = subcategoriesModel->record(j).value("SubategoryID").toUuid();
            Subcategory subcategory(subcategoryId, categoryId, name);
            subcategoryData.append(subcategory);

            TreeItem childItem(QVariant::fromValue(subcategory), &parentItem);
            parentItem.appendChild(&childItem);
        }
    }
    QTreeView *view = new QTreeView();
    view->setModel(categoryModel);
    view->show();

    grid->addWidget(new QWidget(), 0, 0);





    // Для отображения комнат
    grid->addWidget(new QWidget(), 0, 1);


}

void MainWindow::showMyRooms()
{

}

