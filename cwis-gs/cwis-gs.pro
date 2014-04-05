#-------------------------------------------------
#
# Project created by QtCreator 2014-03-19T13:20:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport serialport

TARGET = cwis-gs
TEMPLATE = app


SOURCES += main.cpp                 \
    mainwindow.cpp                  \
    interface/tabletab.cpp          \
    interface/statuspanel.cpp       \
    interface/statusflag.cpp        \
    interface/qcustomplot.cpp       \
    interface/graphtab.cpp          \
    test/serialsim.cpp              \
    interface/clockwidget.cpp       \
    interface/heatercontroltab.cpp  \
    interface/dataplot.cpp \
    serial/serialportlistener.cpp \
    serial/serialportdialog.cpp \
    serial/serialframedescriptor.cpp \
    serial/crc/crc.c \
    serial/crc/crc_table.c

HEADERS  += mainwindow.h            \
    interface/tabletab.h            \
    interface/statuspanel.h         \
    interface/statusflag.h          \
    interface/qcustomplot.h         \
    interface/graphtab.h            \
    experiment/controlmoduledata.h  \
    test/serialsim.h                \
    clockwidget.h                   \
    interface/clockwidget.h         \
    interface/heatercontroltab.h    \
    interface/dataplot.h \
    interface.h \
    serial/serialportlistener.h \
    serial/serialportdialog.h \
    serial/serialportconfig.h \
    serial/serialframedescriptor.h \
    serial/crc/crc.h

FORMS    +=
