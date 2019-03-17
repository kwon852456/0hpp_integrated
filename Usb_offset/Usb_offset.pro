CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(offsetplugin)
TEMPLATE    = lib

HEADERS     = offsetplugin.hpp \
    offset.hpp
SOURCES     = offsetplugin.cpp \
    offset.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(offset.pri)

FORMS += \
    offset.ui
