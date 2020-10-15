#ifndef ABSTRACTTAB_H
#define ABSTRACTTAB_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>

class AbstractTab : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractTab(QWidget *parent = nullptr);
    ~AbstractTab();
    void clearItems(QLayout *layout);
    QLabel *getLabelImage(const QString &path, const int width, const int height, const QString &objectName = "");
    void addRoom(QVBoxLayout *layout, QString &name);
protected:
    QHBoxLayout *roomItemLayout;
};



#endif // ABSTRACTTAB_H
