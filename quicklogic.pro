#-------------------------------------------------
#
# Project created by QtCreator 2016-09-01T18:09:32
#
#-------------------------------------------------

QT       += core gui

CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = quicklogic
TEMPLATE = app


SOURCES += main.cpp\
        qlmainwindow.cpp \
    qlmisc.cpp \
    qlproject.cpp

HEADERS  += qlmainwindow.h \
    qlmisc.h \
    qlproject.h \
    qlprocess.h

FORMS    += qlmainwindow.ui
