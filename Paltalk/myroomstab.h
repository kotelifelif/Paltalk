#ifndef MYROOMSTAB_H
#define MYROOMSTAB_H

#include "abstracttab.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QtSql>
#include <QLabel>
#include <QLayout>
#include <QString>

class MyRoomsTab : public AbstractTab
{
    Q_OBJECT
public:
    explicit MyRoomsTab(QSqlDatabase &db, QWidget *parent = nullptr);
    virtual ~MyRoomsTab();
    void updateLayouts();
private:
    QVBoxLayout *followRoomLayout;
    QVBoxLayout *adminRoomLayout;
    QGridLayout *grid;
    QSqlDatabase db;
};

#endif // MYROOMSTAB_H
