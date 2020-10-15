#include "allroomstab.h"

#include "allroomstab.h"
#include "treemodel.h"
#include "category.h"
#include "subcategory.h"
#include "room.h"
#include "stylemanager.h"

#include <QtSql>
#include <QModelIndex>
#include <QUuid>
#include <QString>
#include <QTreeView>
#include <QSqlRelationalTableModel>
#include <QVBoxLayout>
#include <QLabel>


AllRoomsTab::AllRoomsTab(QSqlDatabase &db, QWidget *parent) :
    roomLayout(new QVBoxLayout),
    grid(new QGridLayout),
    db(db)
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
    categoryView->setStyleSheet(StyleManager::getTreeViewStyle());
    categoryView->hideColumn(1);
    categoryView->hideColumn(2);
    categoryView->expandAll();

    connect(categoryView->selectionModel(),
      SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
      SLOT(showSubcategoryRooms(const QItemSelection &, const QItemSelection &))
     );
    int row = 0;
    // Ищем категорию с подкатегорией
    QModelIndex parentCategory(categoryView->model()->index(row, 0));
    while(parentCategory != QModelIndex()) {
        if (parentCategory.child(0, 0) != QModelIndex())
            break;
        ++row;
        parentCategory = categoryView->model()->index(row, 0);
    }

    QModelIndex topLeft(parentCategory.child(row, 0));
    QModelIndex bottomRight(parentCategory.child(row, parentCategory.column() + 1));
    QItemSelection selection(topLeft, bottomRight);
    categoryView->selectionModel()->select(selection,
                                           QItemSelectionModel::SelectionFlag::Select | QItemSelectionModel::SelectionFlag::Rows);
    grid->addWidget(categoryView, 0, 0);
    grid->addLayout(roomLayout, 0, 1);
    setLayout(grid);
}

AllRoomsTab::~AllRoomsTab()
{
    clearItems(roomLayout);
    clearItems(grid);
    delete grid;
}

void AllRoomsTab::updateLayouts()
{
    clearItems(roomLayout);
    clearItems(grid);
    roomLayout = new QVBoxLayout;
    grid = new QGridLayout;
}

void AllRoomsTab::showSubcategoryRooms(const QItemSelection &selectedItem, const QItemSelection &deselectedItem)
{
    Q_UNUSED(deselectedItem);
    //updateLayouts();
    QModelIndex index = selectedItem.indexes().at(2);
    QUuid subcategoryId = index.data().toUuid();
    if (subcategoryId == QUuid())
        return;
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


        if (subcategoryId != roomSubcategoryId)
            continue;

        Room room(roomId, name, ownerId, subcategoryId);
        addRoom(roomLayout, room.Name);
        //QLabel *roomLabel = new QLabel;
        //roomLabel->setText(room.Name);
        //roomLabel->setStyleSheet(StyleManager::getLabelStyle());
        //roomLayout->addWidget(roomLabel);
    }
}
