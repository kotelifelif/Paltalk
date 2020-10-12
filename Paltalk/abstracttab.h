#ifndef ABSTRACTTAB_H
#define ABSTRACTTAB_H

#include <QWidget>
#include <QtSql>

class AbstractTab : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractTab(QWidget *parent = nullptr);
    ~AbstractTab();
    void clearItems(QLayout *layout);
protected:
    QSqlDatabase db;
private:
    void connectToDb();
};



#endif // ABSTRACTTAB_H
