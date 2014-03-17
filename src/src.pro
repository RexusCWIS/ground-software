#CONFIG += serialport
QT      += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport serialport

HEADERS += \
    mainwindow.h \
    statustab.h \
    qcustomplot.h \
    graphtab.h \
    crc.h \
    serial/serialframedescriptor.h \
    serial/serialportlistener.h \
    serial/serialportdialog.h \
    serial/serialportconfig.h \
    controlmoduleserialportlistener.h \
    controlmoduledata.h

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    statustab.cpp \
    qcustomplot.cpp \
    graphtab.cpp \
    crc_table.c \
    crc.c \
    serial/serialportlistener.cpp \
    serial/serialportdialog.cpp \
    serial/serialframedescriptor.cpp \
    controlmoduleserialportlistener.cpp

