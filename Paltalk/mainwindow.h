#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtSql>

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//! [0]
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
private slots:
    void showRecents();
    void showAllRooms();
    void showMyRooms();
    void showSubcategoryRooms(const QItemSelection &selectedItem, const QItemSelection &deselectedItem);
private:
    void connectToDb();
    void updateLayouts();
    void createActions();
    void createMenus();
    void clearItems(QLayout *layout);

    QMenu *recentsMenu;
    QMenu *allRoomsMenu;
    QMenu *myRoomsMenu;

    QAction *recentsAction;
    QAction *allRoomsAction;
    QAction *myRoomsAction;

    // Room Browser new elements
    QTabWidget *tabWidget;
    QWidget *recentsButton;
    QWidget *allRoomsButton;
    QWidget *myRoomsButton;
    QWidget *searchEdit;



    QSqlDatabase db;

    QGridLayout *grid;
    QVBoxLayout *roomLayout;
    QVBoxLayout *adminRoomLayout;
    QVBoxLayout *followRoomLayout;

    QWidget *widget;
    QTreeView *categoryView;
};

#endif
