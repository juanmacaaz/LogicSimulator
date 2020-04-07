QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    conections/Cable.cpp \
    conections/Conections.cpp \
    conections/Point.cpp \
    cursor/gcursor.cpp \
    diagram/diagram.cpp \
    diagram/gand.cpp \
    diagram/gcable.cpp \
    diagram/ggate.cpp \
    diagram/ginout.cpp \
    diagram/ginv.cpp \
    diagram/gor.cpp \
    diagram/gvertex.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    conections/Cable.h \
    conections/Conections.h \
    conections/Point.h \
    cursor/gcursor.h \
    diagram/diagram.h \
    diagram/gand.h \
    diagram/gcable.h \
    diagram/ggate.h \
    diagram/ginout.h \
    diagram/ginv.h \
    diagram/gor.h \
    diagram/gvertex.h \
    diagram/gxor.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    img/and.png \
    img/inv.png \
    img/or.png \
    img/xor.png
