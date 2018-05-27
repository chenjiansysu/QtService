#include "windowsserviceplugin.h"
#include "windowsservicebackend.h"

WindowsServicePlugin::WindowsServicePlugin(QObject *parent) :
	QObject(parent)
{}

QtService::ServiceBackend *WindowsServicePlugin::createInstance(const QString &provider, QtService::Service *service)
{
	if(provider == QStringLiteral("windows"))
		return new WindowsServiceBackend{service};
	else
		return nullptr;
}