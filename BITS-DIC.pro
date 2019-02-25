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

INCLUDEPATH += /home/vikramaditya/thesis/dice/opencv-3.2.0/build/install/include/
LIBS += -L/home/vikramaditya/thesis/dice/opencv-3.2.0/build/install/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui

#PRECOMPILED_HEADER = /home/vikramaditya/thesis/qt/kukreja-vikramaditya/pch.h
#CONFIG += precompile_header

FORMS += \
    setroi.ui \
    mainwindow.ui \
    displwindow.ui \
    setdicparams.ui

HEADERS += \
    dic.h \
    setroi.h \
    mainwindow.h \
    utils.h \
    params.h \
    displwindow.h \
    colormap.h \
    array2d.h \
    dicimage.h \
    class_integer_array.h \
    class_logical_array.h \
    class_double_array.h \
    class_region.h \
    struct_cirroi.h \
    struct_info_cirroi.h \
    class_roi.h \
    vec_struct_region.h \
    local_struct_queue_roi_separate.h \
    local_struct_roi_separate.h \
    local_struct_roi_overall.h \
    class_inverseregion.h \
    class_img.h \
    setdicparams.h

SOURCES += \
    utils.cpp \
    dic.cpp \
    setroi.cpp \
    mainwindow.cpp \
    main.cpp \
    params.cpp \
    displwindow.cpp \
    colormap.cpp \
    array2d.cpp \
    dicimage.cpp \
    class_integer_array.cpp \
    class_logical_array.cpp \
    class_double_array.cpp \
    class_region.cpp \
    struct_cirroi.cpp \
    struct_info_cirroi.cpp \
    class_roi.cpp \
    vec_struct_region.cpp \
    local_struct_queue_roi_separate.cpp \
    local_struct_roi_separate.cpp \
    local_struct_roi_overall.cpp \
    class_inverseregion.cpp \
    class_img.cpp \
    setdicparams.cpp

RESOURCES += \
    resources.qrc
