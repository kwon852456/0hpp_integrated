#include "usb_log.h"
#include "usb_logplugin.h"

#include <QtPlugin>

Usb_logPlugin::Usb_logPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void Usb_logPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool Usb_logPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *Usb_logPlugin::createWidget(QWidget *parent)
{
    return new Usb_log(parent);
}

QString Usb_logPlugin::name() const
{
    return QLatin1String("Usb_log");
}

QString Usb_logPlugin::group() const
{
    return QLatin1String("");
}

QIcon Usb_logPlugin::icon() const
{
    return QIcon();
}

QString Usb_logPlugin::toolTip() const
{
    return QLatin1String("");
}

QString Usb_logPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool Usb_logPlugin::isContainer() const
{
    return false;
}

QString Usb_logPlugin::domXml() const
{
    return QLatin1String("<widget class=\"Usb_log\" name=\"usb_log\">\n</widget>\n");
}

QString Usb_logPlugin::includeFile() const
{
    return QLatin1String("usb_log.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(usb_logplugin, Usb_logPlugin)
#endif // QT_VERSION < 0x050000
