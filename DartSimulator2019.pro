#-------------------------------------------------
#
# Project created by QtCreator 2019-07-17T17:13:22
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DartSimulator2019
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        customjsonassembler.cpp \
        dbmanager.cpp \
        gamemanager.cpp \
        main.cpp \
        mainapplication.cpp \
        idartsimulator.cpp \
        model.cpp \
        modeldb.cpp \
        point.cpp \
        round.cpp \
        tournament.cpp \
        user.cpp \
        httpreplyobject.cpp \
        myobject.cpp \
        localhttpclientapi.cpp

HEADERS += \
        customjsonassembler.h \
        dbmanager.h \
        gamemanager.h \
        idartsimulator.h \
        idatabasemanager.h \
        imodelizer.h \
        mainapplication.h \
        model.h \
        modeldb.h \
        point.h \
        round.h \
        tournament.h \
        user.h \
        httpreplyobject.h \
        myobject.h \
        localhttpclientapi.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
