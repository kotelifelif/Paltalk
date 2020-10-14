#ifndef MYROOMSTAB_H
#define MYROOMSTAB_H

#include "abstracttab.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QtSql>

class MyRoomsTab : public AbstractTab
{
    Q_OBJECT
public:
    explicit MyRoomsTab(QSqlDatabase &db, QWidget *parent = nullptr);
    void updateLayouts();
private:
    QVBoxLayout *followRoomLayout;
    QVBoxLayout *adminRoomLayout;
    QGridLayout *grid;
    QSqlDatabase db;
};

#endif // MYROOMSTAB_H
