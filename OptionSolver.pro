#-------------------------------------------------
#
# Project created by QtCreator 2015-06-13T13:50:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OptionSolver
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    optioncontroller.cpp \
    mythread.cpp \
    methods/blackscholesanalytic.cpp \
    methods/montecarlomethod.cpp \
    methods/simpartsdialog.cpp

HEADERS  += mainwindow.h \
    optioncontroller.h \
    mythread.h \
    methods/blackscholesanalytic.h \
    methods/montecarlomethod.h \
    methods/simpartsdialog.h

FORMS    += mainwindow.ui \
    methods/simpartsdialog.ui
