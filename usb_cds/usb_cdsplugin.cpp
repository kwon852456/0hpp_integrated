#include "usb_cds.hpp"
#include "usb_cdsplugin.hpp"

#include <QtPlugin>

Usb_cdsPlugin::Usb_cdsPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void Usb_cdsPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool Usb_cdsPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *Usb_cdsPlugin::createWidget(QWidget *parent)
{
    return new Usb_cds(parent);
}

QString Usb_cdsPlugin::name() const
{
    return QLatin1String("Usb_cds");
}

QString Usb_cdsPlugin::group() const
{
    return QLatin1String("");
}

QIcon Usb_cdsPlugin::icon() const
{
    return QIcon();
}

QString Usb_cdsPlugin::toolTip() const
{
    return QLatin1String("");
}

QString Usb_cdsPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool Usb_cdsPlugin::isContainer() const
{
    return false;
}

QString Usb_cdsPlugin::domXml() const
{
    return QLatin1String("<widget class=\"Usb_cds\" name=\"usb_cds\">\n</widget>\n");
}

QString Usb_cdsPlugin::includeFile() const
{
    return QLatin1String("usb_cds.hpp");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(usb_cdsplugin, Usb_cdsPlugin)
#endif // QT_VERSION < 0x050000
