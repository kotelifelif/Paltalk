#ifndef STYLEMANAGER_H
#define STYLEMANAGER_H

#include <QString>

class StyleManager
{
public:
    static QString getTabWidgetStyle();
    static QString getWidgetStyle();
    static QString getLabelStyle();
    static QString getTreeViewStyle();
    static QString getMainWindowStyle();
    static QString getTitleStyle();

};

#endif // STYLEMANAGER_H
