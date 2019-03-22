#-------------------------------------------------
#
# Project created by QtCreator 2019-03-17T19:23:56
#
#-------------------------------------------------

QT       += core gui concurrent serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = usb_integrated
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

#DEFINES += QT_NO_DEBUG_OUTPUT

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.hpp \
    3dll_usb_01stt.hpp

FORMS += \
        mainwindow.ui
INCLUDEPATH += \
                C:/Users/Admin/Documents/include

INCLUDEPATH += R:\dev\release\0hpp \
               D:\dev\gdrv\dev\code\rv\qt\0.0.5\proj\0hpp_integrated-master\include \
               D:\dev\gdrv\dev\code\rv\qt\0.0.5\proj\0hpp_integrated-master


LIBS += -lws2_32 -luser32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/include/ -loffsetplugin
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/include/ -loffsetplugind
else:unix: LIBS += -L$$PWD/include/ -loffsetplugin

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/include/ -lusb_mmfplugin
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/include/ -lusb_mmfplugind
else:unix: LIBS += -L$$PWD/include/ -lusb_mmfplugin

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/include/ -lusb_logplugin
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/include/ -lusb_logplugind
else:unix: LIBS += -L$$PWD/include/ -lusb_logplugin

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
