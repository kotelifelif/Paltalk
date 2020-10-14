#ifndef RECENTSTAB_H
#define RECENTSTAB_H

#include "abstracttab.h"
#include <QtSql>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>

class RecentsTab : public AbstractTab
{
    Q_OBJECT
public:
    explicit RecentsTab(QSqlDatabase &db, QWidget *parent = nullptr);
    virtual ~RecentsTab();
    void updateLayouts();
private:
    QVBoxLayout *roomLayout;
    QGridLayout *grid;
    QSqlDatabase db;
};

#endif // RECENTSTAB_H
