#ifndef CATEGORY_H
#define CATEGORY_H

#include <QUuid>
#include <QString>
#include <QObject>

class Category : public QObject
{
public:
    Category();
    Category(const QUuid &categoryId = QUuid(), const QString &name = QString());
    QUuid CategoryId;
    QString Name;
};

#endif // CATEGORY_H
