#ifndef ALLROOMSTAB_H
#define ALLROOMSTAB_H

#include "abstracttab.h"

#include <QtSql>
#include <QItemSelection>
#include <QVBoxLayout>
#include <QTreeView>

class AllRoomsTab : public AbstractTab
{
    Q_OBJECT
public:
    explicit AllRoomsTab(QSqlDatabase &db, QWidget *parent = nullptr);
    virtual ~AllRoomsTab();
    void updateLayouts();
private:
    QVBoxLayout *roomLayout;
    QGridLayout *grid;
    QSqlDatabase db;
    QTreeView *categoryView;
private slots:
    void showSubcategoryRooms(const QItemSelection &selectedItem, const QItemSelection &deselectedItem);
};

#endif // ALLROOMSTAB_H
