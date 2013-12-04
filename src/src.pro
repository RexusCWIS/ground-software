#CONFIG += serialport
QT      += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport serialport

HEADERS += \
    mainwindow.h \
    statustab.h \
    qcustomplot.h \
    graphtab.h \
    timelinetab.h \
    experiment.h \
    serialportlistener.h \
    serialportselector.h \
    experimentdatagenerator.h

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    statustab.cpp \
    qcustomplot.cpp \
    graphtab.cpp \
    timelinetab.cpp \
    serialportlistener.cpp \
    serialportselector.cpp \
    experimentdatagenerator.cpp
