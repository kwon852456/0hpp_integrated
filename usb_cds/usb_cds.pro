CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(usb_cdsplugin)
TEMPLATE    = lib

HEADERS     = usb_cdsplugin.hpp \
    usb_cds.hpp \
    3dll_usb_cds01stt.hpp
SOURCES     = usb_cdsplugin.cpp \
    usb_cds.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer concurrent
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(usb_cds.pri)

FORMS += \
    usb_cds.ui

INCLUDEPATH += R:\dev\release\0hpp \
                R:\dev\release \
                    C:\Users\Admin\Downloads\0hpp


LIBS += -lws2_32 -luser32
