#-------------------------------------------------
#
# Project created by QtCreator 2015-04-25T20:45:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Huffman
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imageanalyzer.cpp \
    probabilitiescalculator.cpp \
    huffmanalgorithm.cpp \
    about.cpp \
    symbol.cpp \
    nextension.cpp \
    filecompressor.cpp

HEADERS  += mainwindow.h \
    imageanalyzer.h \
    probabilitiescalculator.h \
    huffmanalgorithm.h \
    about.h \
    symbol.h \
    nextension.h \
    filecompressor.h

FORMS    += mainwindow.ui \
    about.ui \
    nextension.ui
