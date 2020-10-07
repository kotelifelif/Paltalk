#ifndef SUBCATEGORY_H
#define SUBCATEGORY_H

#include <QUuid>
#include <QString>
#include <QObject>

class Subcategory : public QObject
{
public:
    Subcategory(const QUuid &subcategoryId = QUuid(), const QUuid &categoryId = QUuid(), const QString &name = QString());
    QUuid SubcategoryId;
    QUuid CategoryId;
    QString Name;
};

#endif // SUBCATEGORY_H
