#-------------------------------------------------
#
# Project created by QtCreator 2018-02-05T14:20:16
#
#-------------------------------------------------

QT       += core gui \
                widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BITS-DIC
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui

FORMS += \
    setroi.ui \
    mainwindow.ui

HEADERS += \
    dic.h \
    setroi.h \
    mainwindow.h \
    disp.h \
    utils.h \
    params.h

SOURCES += \
    utils.cpp \
    dic.cpp \
    setroi.cpp \
    mainwindow.cpp \
    disp.cpp \
    main.cpp \
    params.cpp
