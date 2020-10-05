#ifndef CATEGORY_H
#define CATEGORY_H

#include <QUuid>
#include <QString>
#include <QObject>

class Category : public QObject
{
public:
    Category();
    Category(const QUuid &categoryId = nullptr, const QString &name = nullptr);
    QUuid CategoryId;
    QString Name;
};

#endif // CATEGORY_H
