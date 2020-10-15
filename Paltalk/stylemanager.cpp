#include "stylemanager.h"

QString StyleManager::getTabWidgetStyle()
{
    return QString("QTabWidget {"
                   "width: 870px;"
                   "background-color: #366190;"
                   "}"

                   "QTabWidget::tab-bar:top {"
                        "top: 1px;"
                   "}"

                   "QTabWidget::tab-bar:bottom {"
                       "bottom: 1px;"
                   "}"

                   "QTabWidget::tab-bar:left {"
                       "right: 1px;"
                   "}"

                   "QTabWidget::tab-bar:right {"
                       "left: 1px;"
                   "}"

                   "QTabBar::tab {"
                       "font-size: 13px;"
                       "background-color: #366190;"
                       "height: 40px;"
                       "width: 235px;"
                   "}"

                   "QTabBar::tab:selected {"
                       "text-decoration: underline;"
                       "background: #366190;"
                       "color: #9abed8;"
                   "}"

                   "QTabBar::tab:!selected {"
                       "background: #366190;"
                       "color: #9abed8;"
                   "}"

                   "QTabBar::tab:!selected:hover {"
                       "background: #366190;"
                       "color: white;"
                   "}"

                   "QTabBar::tab:selected:hover {"
                       "background: #366190;"
                       "color: white;"
                   "}");
}

QString StyleManager::getWidgetStyle()
{
    return "QWidget { "
           "background-color: #366190; "
           "border: 1px solid black; "
           "}";
}

QString StyleManager::getLabelStyle()
{
    return QString("QLabel {"
                   "font-size: 12px;"
                   "background-color: white;"
                   "color: #808080;"
                   "}");
}

QString StyleManager::getTreeViewStyle()
{
    return QString("QTreeView {"
                   "background-color: #f2f2f2;"
                   "}"

                   "QTreeView::branch:has-children:!has-siblings:closed,"
                   "QTreeView::branch:closed:has-children:has-siblings {"
                    "image: none;"
                   "}"

                   "QTreeView::branch:has-children:!has-siblings:open,"
                   "QTreeView::branch:open:has-children:has-siblings {"
                   "image: none;"
                   "}"

                   "QTreeView::item {"
                   "color: #808080;"
                   "}"

                   "QTreeView::item:hover {"
                     "background-color: #cbe8f7;"
                   "}"

                   "QTreeView::item:selected:active {"
                   "background-color: #cbe8f7;"
                   "}");
}

QString StyleManager::getMainWindowStyle()
{
    return QString("background-color: #f2f2f2;");
}

QString StyleManager::getTitleStyle()
{
    return QString("QLabel#TitleLabel {"
                   "font-size: 15px;"
                   "color: #808080;"
                   "}");
}

QString StyleManager::getIconStyle()
{
    return QString("QLabel#Icon {"
                   "background-color: white;"
                   "}");
}

QString StyleManager::getAllButtonStyle()
{
    return QString("QRadioButton#All::indicator::checked {"
                   "image: url(:/images/all_active_icon.png);"
                   "}"
                   "QRadioButton#All::indicator::unchecked {"
                   "image: url(:/images/all_not_active_icon.png);"
                   "}");
}

QString StyleManager::getOpenButtonStyle()
{
    return QString("QRadioButton#Open::indicator::checked {"
                   "image: url(:/images/open_active_icon.png);"
                   "}"
                   "QRadioButton#Open::indicator::unchecked {"
                   "image: url(:/images/open_not_active_icon.png);"
                   "}");
}

QString StyleManager::getCornerWidgetStyle()
{
    return QString("QWidget#Corner {"
                   "border-color: #366190;"
                   "background-color: #366190;"
                   "}");
}
