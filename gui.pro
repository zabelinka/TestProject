#-------------------------------------------------
#
# Project created by QtCreator 2016-02-21T15:07:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv

LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio

SOURCES += main.cpp \
    pip.cpp

HEADERS += \
    pip.h \
    videothread.h

FORMS += \
    pip.ui
