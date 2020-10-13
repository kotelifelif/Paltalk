#include "stylemanager.h"

QString StyleManager::getTabWidgetStyle()
{
    return QString("QTabWidget {"
                   "width: 870px;"
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
                       "background-color: #366190;"
                       "height: 54px;"
                   "}"

                   "QTabBar::tab:selected {"
                       "background: #366190;"
                       "color: #9abed8;"
                       "text-decoration: underline;"
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
                   "font-size: 10px;"
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

                   "QTreeView: item {"
                   "font-size: 10px;"
                   "}"

                   "QTreeView:item:hover {"
                   "background-color: #cbe8f7;"
                   "}"

                   "QTreeView:item:selected:active {"
                   "background-color: #cbe8f7;"
                   "}"

                   "QTreeView::branch:has-siblings:adjoins-item {"
                   "background: red;"
                   "}");
}

QString StyleManager::getMainWindowStyle()
{
    return QString("background-color: #f2f2f2;");
}
