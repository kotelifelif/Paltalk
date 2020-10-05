#ifndef SUBCATEGORY_H
#define SUBCATEGORY_H

#include <QUuid>
#include <QString>
#include <QObject>

class Subcategory : public QObject
{
public:
    Subcategory(const QUuid &subcategoryId = nullptr, const QUuid &categoryId = nullptr, const QString &name = nullptr);
    QUuid SubcategoryId;
    QUuid CategoryId;
    QString Name;
};

#endif // SUBCATEGORY_H
