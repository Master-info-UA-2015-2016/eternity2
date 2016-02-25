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
    Model/instance_model.cpp \
    Model/piece_model.cpp \
    Model/board_model.cpp \
    View/piece_view.cpp \
    View/board_view.cpp \
    Model/coordinates.cpp

HEADERS  += mainwindow.h \
    pieceswidget.h \
    Model/instance_model.h \
    Model/piece_model.h \
    Model/board_model.h \
    View/cell.h \
    View/coordinates.h \
    View/piece_view.h \
    View/board_view.h \
    Model/coordinates.h

FORMS    += mainwindow.ui \
    exemple.ui

OTHER_FILES += \
    TODO.txt
