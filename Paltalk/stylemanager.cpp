#include "stylemanager.h"

QString StyleManager::getToolButtonStyle()
{
    return "QToolButton {"
           "background-color: #366190;"
           "spacing: 3px;"
            "color: #547ea5;"
           "border: none;"
       "}"
           "QToolButton:hover {"
           "color: white;"
           "}";
}

QString StyleManager::getWidgetStyle()
{
    return "QWidget { "
           "background-color: #366190; "
           "border: 1px solid black; "
           "}";
}
