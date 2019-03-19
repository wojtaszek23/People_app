#-------------------------------------------------
#
# Project created by QtCreator 2019-03-13T19:42:10
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = People_app
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    delegate.cpp \
    xmlreader.cpp \
    xmlwriter.cpp \
    dialogsave.cpp \
    date.cpp \
    modelmanager.cpp

HEADERS  += dialog.h \
    delegate.h \
    xmlreader.h \
    xmlwriter.h \
    dialogsave.h \
    date.h \
    modelmanager.h

FORMS    += dialog.ui \
    dialogsave.ui
