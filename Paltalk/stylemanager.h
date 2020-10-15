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
    static QString getIconStyle();
    static QString getAllButtonStyle();
    static QString getOpenButtonStyle();
    static QString getCornerWidgetStyle();

};

#endif // STYLEMANAGER_H
