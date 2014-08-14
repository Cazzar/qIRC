#-------------------------------------------------
#
# Project created by QtCreator 2014-08-14T08:53:08
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qIRC
TEMPLATE = app

INCLUDEPATH += ./sources
INCLUDEPATH += ./include

#SOURCES += main.cpp\
#        mainwindow.cpp \
#    ircconnection.cpp \
#    serversetup.cpp

SOURCES += sources/*.cpp

#HEADERS  += mainwindow.h \
#    ircconnection.h \
#    IRCStatus.h \
#    serversetup.h

HEADERS += include/*.h

#FORMS    += mainwindow.ui \
#    serversetup.ui

FORMS += forms/*.ui

