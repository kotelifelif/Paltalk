#include "treemodel.h"
#include <QDebug>
#include <QAbstractItemModel>

TreeModel::TreeModel(QObject *parent)
  : QAbstractItemModel(parent)
{
  //Creating instance of virtual root item
  _rootItem = new QObject(this);
}

void TreeModel::setColumns(QStringList cols)
{
  _columns = cols;
}

void TreeModel::addItem(QObject *item, const QModelIndex &parentIdx)
{
  beginInsertRows(parentIdx, rowCount(parentIdx), rowCount(parentIdx));
  item->setParent(objByIndex(parentIdx));
  endInsertRows();
}

QObject *TreeModel::objByIndex(const QModelIndex &index) const
{
  if (!index.isValid())
    return _rootItem;
  return static_cast<QObject*>(index.internalPointer());
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
  if (!hasIndex(row, column, parent))
    return QModelIndex();
  QObject* parentObj = objByIndex(parent);
  return createIndex(row, column, parentObj->children().at(row));
}

QModelIndex TreeModel::parent(const QModelIndex &child) const
{
  QObject* childObj = objByIndex(child);
  QObject* parentObj = childObj->parent();
  //Virtual root item has invalid index (QModelIndex())
  if (parentObj == _rootItem)
    return QModelIndex();
  //Grand parent item is used to get row coordinate for parent item
  QObject* grandParentObj = parentObj->parent();
  int row = grandParentObj->children().indexOf(parentObj);
  //First row cell is used as parent index
  return createIndex(row, 0, parentObj);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
  return objByIndex(parent)->children().count();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return _columns.count();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();
  //Cell values retrieved from QObject properties
  if (role == Qt::DisplayRole) {
    return objByIndex(index)->property(_columns.at(index.column()).toUtf8());
  }
  return QVariant();
}
