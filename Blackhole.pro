#-------------------------------------------------
#
# Project created by QtCreator 2016-03-15T17:18:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Blackhole
TEMPLATE = app


SOURCES += main.cpp\
    Sources/infopanel.cpp \
    Sources/mainwindow_view.cpp \
    Sources/mainwindow_model.cpp \
    Sources/gamesession_model.cpp \
    Sources/gamesession_view.cpp \
    Sources/tableview.cpp \
    Sources/viewdata.cpp \

HEADERS  += \
    Headers/datastructures.h \
    Headers/gamesession_model.h \
    Headers/gamesession_view.h \
    Headers/infopanel.h \
    Headers/mainwindow_model.h \
    Headers/mainwindow_view.h \
    Headers/tableview.h \
    Headers/viewdata.h

FORMS    += UI\mainwindow.ui \
    UI\infopanel.ui \
    UI\gamesession.ui \
    UI/gamesession.ui \
    UI/infopanel.ui \
    UI/mainwindow.ui

RESOURCES += \
    resources.qrc
