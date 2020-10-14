#include "abstracttab.h"

#include <QLayout>
#include <QtWidgets>

AbstractTab::AbstractTab(QWidget *parent) : QWidget(parent)
{
}

AbstractTab::~AbstractTab()
{
}

void AbstractTab::clearItems(QLayout *layout)
{
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr) {
        delete child->widget(); // delete the widget
        delete child;   // delete the layout item
    }
}
