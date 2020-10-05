#include "subcategory.h"

Subcategory::Subcategory(const QUuid &subcategoryId, const QUuid &categoryId, const QString &name) :
    SubcategoryId(subcategoryId),
    CategoryId(categoryId),
    Name(name)
{

}
