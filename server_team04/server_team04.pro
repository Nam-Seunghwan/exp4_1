#-------------------------------------------------
#
# Project created by QtCreator 2014-05-03T04:31:59
#
#-------------------------------------------------

QT       += core gui network declarative

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = server_team04
TEMPLATE = app


SOURCES += main.cpp\
    EchoServer.cpp \
    mainwindow.cpp

HEADERS  += \
    EchoServer.h \
    ClientSocket.h \
    mainwindow.h

FORMS    += mainwindow.ui
