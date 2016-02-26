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
    Model/coordinates.cpp \
    View/piece_view.cpp \
    View/board_view.cpp \
    View/motif.cpp \
    Model/configuration.cpp \
    Tools/string_tools.cpp \
    Controller/controller_config.cpp

HEADERS  += mainwindow.h \
    Model/instance_model.h \
    Model/piece_model.h \
    Model/board_model.h \
    Model/coordinates.h \
    View/cell.h \
    View/piece_view.h \
    View/board_view.h \
    View/motif.h \
    Model/configuration.h \
    Tools/string_tools.h

FORMS    += mainwindow.ui \
    exemple.ui

OTHER_FILES += \
    TODO.txt
