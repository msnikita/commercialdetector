#-------------------------------------------------
#
# Project created by QtCreator 2013-03-12T23:11:07
#
#-------------------------------------------------

QT       += core gui

TARGET = finalad
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    welcome.cpp \
    clickwindow.cpp \
    menu.cpp \
    admin.cpp \
    addlogo.cpp

HEADERS  += mainwindow.h \
    welcome.h \
    clickwindow.h \
    menu.h \
    admin.h \
    addlogo1.h

FORMS    += mainwindow.ui \
    welcome.ui \
    menu.ui \
    admin.ui \
    addlogo1.ui
INCLUDEPATH+=-I /usr/local/include/opencv2\
/usr/local/include/opencv\
/usr/local/qt4/include

QT+=phonon
LIBS+= /usr/local/lib/*.so

