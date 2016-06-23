#-------------------------------------------------
#
# Project created by QtCreator 2014-01-12T19:50:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sortowanie
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sortwidget.cpp \
    SortingClasses.cpp

HEADERS  += mainwindow.h \
    sortwidget.h \
    SortingClasses.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
