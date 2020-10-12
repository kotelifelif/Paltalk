#include "abstracttab.h"

#include <QLayout>

AbstractTab::AbstractTab(QWidget *parent) : QWidget(parent)
{
    connectToDb();
}

AbstractTab::~AbstractTab()
{
    db.close();
}

void AbstractTab::clearItems(QLayout *layout)
{
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr) {
        delete child->widget(); // delete the widget
        delete child;   // delete the layout item
    }
}

void AbstractTab::connectToDb()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("Paltalk");
    db.setUserName("postgres");
    db.setHostName("localhost");
    db.setPassword("12345");
    db.open();
}
