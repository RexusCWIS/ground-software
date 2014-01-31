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
    experimentdatagenerator.h \
    crc.h \
    thermometer/thermometer.h \
    thermometer/abstractmeter.h \
    thermometer/widgetwithbackground.h \
    thermometer/functions.h

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    statustab.cpp \
    qcustomplot.cpp \
    graphtab.cpp \
    timelinetab.cpp \
    serialportlistener.cpp \
    serialportselector.cpp \
    experimentdatagenerator.cpp \
    crc_table.c \
    crc.c \
    thermometer/thermometer.cpp \
    thermometer/abstractmeter.cpp \
    thermometer/widgetwithbackground.cpp \
    thermometer/functions.cpp

