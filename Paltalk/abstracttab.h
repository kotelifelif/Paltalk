#ifndef ABSTRACTTAB_H
#define ABSTRACTTAB_H

#include <QWidget>

class AbstractTab : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractTab(QWidget *parent = nullptr);
    ~AbstractTab();
    void clearItems(QLayout *layout);
};



#endif // ABSTRACTTAB_H
