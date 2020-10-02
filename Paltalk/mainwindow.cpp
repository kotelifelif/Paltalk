#include <QtWidgets>
#include "mainwindow.h"
#include "ui_mainwindow.h"
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
    for (int i = 0; i < categoriesModel->rowCount(); ++i) {
        QSqlRelationalTableModel *subcategoriesModel = new QSqlRelationalTableModel(nullptr, db);
        subcategoriesModel->setTable("\"Subcategories\"");
        subcategoriesModel->setRelation(2, QSqlRelation("\"Subcategories\"", "\"CategoryID\"", "\"Name\""));
        QVector<QVariant> categoryData;
        categoryData.append(categoriesModel->record(i).value("Name"));
        //TreeItem categoryItem(categoryData, nullptr);
        QTreeWidgetItem *categoryItem = new QTreeWidgetItem();
        categoryItem->setText(0, categoriesModel->record(i).value("Name").toString());
        for (int j = 0; j < subcategoriesModel->rowCount(); ++j) {
          //categoryItem->addChild();
          categoryWidget->insertTopLevelItem(i, new QTreeWidgetItem);
        }
    }
    categoryWidget->show();
    grid->addWidget(new QWidget(), 0, 0);





    // Для отображения комнат
    grid->addWidget(new QWidget(), 0, 1);


}

void MainWindow::showMyRooms()
{

}

