#include "offset.hpp"
#include "offsetplugin.hpp"

#include <QtPlugin>

OffsetPlugin::OffsetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OffsetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OffsetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OffsetPlugin::createWidget(QWidget *parent)
{
    return new Offset(parent);
}

QString OffsetPlugin::name() const
{
    return QLatin1String("Offset");
}

QString OffsetPlugin::group() const
{
    return QLatin1String("");
}

QIcon OffsetPlugin::icon() const
{
    return QIcon();
}

QString OffsetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OffsetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OffsetPlugin::isContainer() const
{
    return false;
}

QString OffsetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"Offset\" name=\"offset\">\n</widget>\n");
}

QString OffsetPlugin::includeFile() const
{
    return QLatin1String("offset.hpp");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(offsetplugin, OffsetPlugin)
#endif // QT_VERSION < 0x050000
