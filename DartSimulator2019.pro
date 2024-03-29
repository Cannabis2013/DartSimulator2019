#-------------------------------------------------
#
# Project created by QtCreator 2019-07-17T17:13:22
#
#-------------------------------------------------

QT       += core gui network quick

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

CONFIG += c++17

SOURCES += \
        loginview.cpp \
        abstractframeimplementable.cpp \
        customdialog.cpp \
        datamodelmanager.cpp \
        gamemanager.cpp \
        iurlparser.cpp \
        main.cpp \
        mainapplication.cpp \
        idartsimulator.cpp \
        networkmanager.cpp \
        remotemodelmanager.cpp \
        remoteusermanager.cpp \
        topframeform.cpp \
        tournamentselectorview.cpp \
        urlparser.cpp \
        userdomain.cpp \
        view.cpp

HEADERS += \
        loginview.h \
        abstractframeimplementable.h \
        customdialog.h \
        datamodelmanager.h \
        gamemanager.h \
        idartsimulator.h \
        igraphicaluserinterface.h \
        ijsonconverter.h \
        iurlparser.h \
        mainapplication.h \
        networkmanager.h \
        remotemodelmanager.h \
        remoteusermanager.h \
        replytimeout.h \
        topframeform.h \
        tournamentselectorview.h \
        urlparser.h \
        userdomain.h \
        view.h

FORMS += \
    loginview.ui \
    topframeform.ui \
    customdialog.ui \
    tournamentselectorview.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pictures.qrc

DISTFILES +=

