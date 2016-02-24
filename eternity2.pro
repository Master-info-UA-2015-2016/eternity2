#-------------------------------------------------
#
# Project created by QtCreator 2016-02-24T13:33:27
#
#-------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = eternity2
TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    pieceswidget.cpp \
    Model/instance_model.cpp \
    Model/piece_model.cpp \
    Model/coordinates.cpp \
    model/board_model.cpp

HEADERS  += mainwindow.h \
    pieceswidget.h \
    Model/instance_model.h \
    Model/piece_model.h \
    Model/coordinates.h \
    Model/cell.h \
    Model/board_model.h

FORMS    += mainwindow.ui
