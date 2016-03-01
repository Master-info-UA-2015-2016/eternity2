#-------------------------------------------------
#
# Project created by QtCreator 2016-02-24T13:33:27
#
#-------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = eternity2
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp \
    Model/instance_model.cpp \
    Model/piece_model.cpp \
    Model/board_model.cpp \
    Model/coordinates.cpp \
    Model/configuration.cpp \
    View/piece_view.cpp \
    View/board_view.cpp \
    View/motif.cpp \
    View/mainwindow.cpp \
    Tools/string_tools.cpp \
    algorithm.cpp

HEADERS  +=  Model/instance_model.h \
    Model/piece_model.h \
    Model/board_model.h \
    Model/coordinates.h \
    Model/configuration.h \
    View/cell.h \
    View/piece_view.h \
    View/board_view.h \
    View/motif.h \
    View/mainwindow.h \
    Tools/string_tools.h \
    algorithm.h \
    debug.h

FORMS    += mainwindow.ui \
    exemple.ui

OTHER_FILES += \
    TODO.txt

DISTFILES += \
    recherche_locale.txt
