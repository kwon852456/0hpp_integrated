#include "usb_mmf.hpp"
#include "usb_mmfplugin.hpp"

#include <QtPlugin>

Usb_mmfPlugin::Usb_mmfPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void Usb_mmfPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool Usb_mmfPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *Usb_mmfPlugin::createWidget(QWidget *parent)
{
    return new Usb_mmf(parent);
}

QString Usb_mmfPlugin::name() const
{
    return QLatin1String("Usb_mmf");
}

QString Usb_mmfPlugin::group() const
{
    return QLatin1String("");
}

QIcon Usb_mmfPlugin::icon() const
{
    return QIcon();
}

QString Usb_mmfPlugin::toolTip() const
{
    return QLatin1String("");
}

QString Usb_mmfPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool Usb_mmfPlugin::isContainer() const
{
    return false;
}

QString Usb_mmfPlugin::domXml() const
{
    return QLatin1String("<widget class=\"Usb_mmf\" name=\"usb_mmf\">\n</widget>\n");
}

QString Usb_mmfPlugin::includeFile() const
{
    return QLatin1String("usb_mmf.hpp");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(usb_mmfplugin, Usb_mmfPlugin)
#endif // QT_VERSION < 0x050000
