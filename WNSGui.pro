#-------------------------------------------------
#
# Project created by QtCreator 2018-01-26T19:16:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WNSGui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    AXI_Wrapper.cpp

HEADERS  += mainwindow.h \
    AXI_Wrapper.h

FORMS    += mainwindow.ui
