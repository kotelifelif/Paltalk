QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abstracttab.cpp \
    allroomstab.cpp \
    category.cpp \
    main.cpp \
    mainwindow.cpp \
    myroomstab.cpp \
    recentstab.cpp \
    room.cpp \
    stylemanager.cpp \
    subcategory.cpp \
    treeitem.cpp \
    treemodel.cpp \
    user.cpp

HEADERS += \
    abstracttab.h \
    allroomstab.h \
    category.h \
    mainwindow.h \
    myroomstab.h \
    recentstab.h \
    room.h \
    stylemanager.h \
    subcategory.h \
    treeitem.h \
    treemodel.h \
    user.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Ff.qml
