CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(usb_logplugin)
TEMPLATE    = lib

HEADERS     = usb_logplugin.h \
    usb_log.h
SOURCES     = usb_logplugin.cpp \
    usb_log.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(usb_log.pri)

FORMS += \
    usb_log.ui
