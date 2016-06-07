#-------------------------------------------------
#
# Project created by QtCreator 2015-05-22T13:11:22
#
#-------------------------------------------------

QT       += core gui sql
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = resManageSys
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    formqueryresult.cpp \
    formjumptoolkit.cpp \
    queryresults.cpp \
    mytablewidegetitem.cpp \
    formquerydialog.cpp \
    dbdateacontroler.cpp \
    dbproxy.cpp \
    formattributeitemselection.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    formqueryresult.h \
    formjumptoolkit.h \
    queryresults.h \
    mytablewidegetitem.h \
    formquerydialog.h \
    common.h \
    dbdateacontroler.h \
    dbproxy.h \
    formattributeitemselection.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    formqueryresult.ui \
    formjumptoolkit.ui \
    formquerydialog.ui \
    formattributeitemselection.ui

RESOURCES += \
    images.qrc
