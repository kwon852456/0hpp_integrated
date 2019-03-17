CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(usb_mmfplugin)
TEMPLATE    = lib

HEADERS     = usb_mmfplugin.hpp \
    usb_mmf.hpp
SOURCES     = usb_mmfplugin.cpp \
    usb_mmf.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer concurrent
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(usb_mmf.pri)

FORMS += \
    usb_mmf.ui

INCLUDEPATH += C:\Users\Admin\Downloads\0hpp

LIBS += -lws2_32 -luser32
