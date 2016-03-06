#-------------------------------------------------
#
# Project created by QtCreator 2016-02-24T13:33:27
#
#-------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = eternity2
TEMPLATE = app

CONFIG      += c++11
CONFIG      += plugin
QT          += widgets uiplugin

SOURCES += main.cpp \
    Model/board.cpp \
    Model/configuration.cpp \
    Model/coordinates.cpp \
    Model/instance.cpp \
    Model/piece.cpp \
    View/mainwindow.cpp \
    View/board_view.cpp \
    View/motif_view.cpp \
    View/piece_view.cpp \
    Tools/string_tools.cpp \
    algorithm.cpp

HEADERS  +=  \
    Model/board.h \
    Model/configuration.h \
    Model/coordinates.h \
    Model/instance.h \
    Model/piece.h \
    Model/motif.h \
    View/cell.h \
    View/piece_view.h \
    View/board_view.h \
    View/mainwindow.h \
    Tools/string_tools.h \
    algorithm.h \
    debug.h \
    View/motif_view.h

FORMS    += mainwindow.ui \
    exemple.ui

OTHER_FILES += \
    TODO.txt

DISTFILES += \
    recherche_locale.txt \
    backtrack.txt
