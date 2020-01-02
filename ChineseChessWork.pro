QT       += core gui network

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
    boardcontroller.cpp \
    boardfactory.cpp \
    chessboard.cpp \
    chessboardutil.cpp \
    chesscharacter.cpp \
    choosemode.cpp \
    convertcoordinate.cpp \
    main.cpp \
    mainwindow.cpp \
    mygraphicsscene.cpp \
    mygraphicsview.cpp \
    netgamewindow.cpp

HEADERS += \
    ChessID.h \
    boardcontroller.h \
    boardfactory.h \
    chessboard.h \
    chessboardutil.h \
    chesscharacter.h \
    choosemode.h \
    convertcoordinate.h \
    mainwindow.h \
    mygraphicsscene.h \
    mygraphicsview.h \
    netgamewindow.h

FORMS += \
    choosemode.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Resource/0.png \
    Resource/1.png \
    Resource/10.png \
    Resource/11.png \
    Resource/12.png \
    Resource/13.png \
    Resource/14.png \
    Resource/15.png \
    Resource/16.png \
    Resource/17.png \
    Resource/18.png \
    Resource/19.png \
    Resource/2.png \
    Resource/20.png \
    Resource/21.png \
    Resource/22.png \
    Resource/23.png \
    Resource/24.png \
    Resource/25.png \
    Resource/26.png \
    Resource/27.png \
    Resource/28.png \
    Resource/29.png \
    Resource/3.png \
    Resource/30.png \
    Resource/31.png \
    Resource/32.png \
    Resource/4.png \
    Resource/5.png \
    Resource/6.png \
    Resource/7.png \
    Resource/8.png \
    Resource/9.png \
    Resource/back.png \
    Resource/board.png \
    Resource/table.jpg

