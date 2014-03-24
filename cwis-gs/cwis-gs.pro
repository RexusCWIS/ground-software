#-------------------------------------------------
#
# Project created by QtCreator 2014-03-19T13:20:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = cwis-gs
TEMPLATE = app


SOURCES += main.cpp             \
    mainwindow.cpp              \
    interface/tabletab.cpp      \
    interface/statuspanel.cpp   \
    interface/statusflag.cpp    \
    interface/qcustomplot.cpp   \
    interface/graphtab.cpp      \
    test/serialsim.cpp          \
    interface/clockwidget.cpp   \
    interface/heatercontroltab.cpp

HEADERS  += mainwindow.h        \
    interface/tabletab.h        \
    interface/statuspanel.h     \
    interface/statusflag.h      \
    interface/qcustomplot.h     \
    interface/graphtab.h        \
    experiment/controlmoduledata.h  \
    test/serialsim.h            \
    clockwidget.h               \
    interface/clockwidget.h     \
    interface/heatercontroltab.h

FORMS    +=
