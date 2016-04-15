#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T08:34:21
#
#-------------------------------------------------

QT       += core gui
QT       += webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PotatoFoldersMetadata
TEMPLATE = app


SOURCES += main.cpp\
        mainmenu.cpp \
    foldermetadata.cpp \
    utilityclass.cpp

HEADERS  += mainmenu.h \
    foldermetadata.h \
    utilityclass.h

FORMS    += mainmenu.ui

DISTFILES += \
    JsonSample.txt
