#ifndef ALLROOMSTAB_H
#define ALLROOMSTAB_H

#include "abstracttab.h"

#include <QSqlDatabase>
#include <QItemSelection>
#include <QVBoxLayout>

class AllRoomsTab : public AbstractTab
{
    Q_OBJECT
public:
    explicit AllRoomsTab(QWidget *parent = nullptr);
    void updateLayouts();
private:
    QVBoxLayout *roomLayout;
    QGridLayout *grid;
private slots:
    void showSubcategoryRooms(const QItemSelection &selectedItem, const QItemSelection &deselectedItem);
};

#endif // ALLROOMSTAB_H
