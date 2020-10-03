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
private:
    void connectToDb();
    void createActions();
    void createMenus();

    QMenu *recentsMenu;
    QMenu *allRoomsMenu;
    QMenu *myRoomsMenu;

    QAction *recentsAction;
    QAction *allRoomsAction;
    QAction *myRoomsAction;

    QSqlDatabase db;

    QGridLayout *grid;
};

#endif
