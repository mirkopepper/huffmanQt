#-------------------------------------------------
#
# Project created by QtCreator 2015-04-25T20:45:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Hoffman
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imageanalyzer.cpp \
    probabilitiescalculator.cpp

HEADERS  += mainwindow.h \
    imageanalyzer.h \
    probabilitiescalculator.h

FORMS    += mainwindow.ui
