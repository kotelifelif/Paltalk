#ifndef MYROOMSTAB_H
#define MYROOMSTAB_H

#include "abstracttab.h"

#include <QGridLayout>
#include <QVBoxLayout>

class MyRoomsTab : public AbstractTab
{
    Q_OBJECT
public:
    explicit MyRoomsTab(QWidget *parent = nullptr);
    void updateLayouts();
private:
    QVBoxLayout *followRoomLayout;
    QVBoxLayout *adminRoomLayout;
    QGridLayout *grid;
};

#endif // MYROOMSTAB_H
