#ifndef SYSTEMDSERVICEBACKEND_H
#define SYSTEMDSERVICEBACKEND_H

#include <QtCore/QTimer>
#include <QtService/ServiceBackend>

class SystemdServiceBackend : public QtService::ServiceBackend
{
	Q_OBJECT

public:
	explicit SystemdServiceBackend(QtService::Service *service);

	int runService(int &argc, char **argv, int flags) override;
	void quitService() override;
	void reloadService() override;
	QList<int> getActivatedSockets(const QByteArray &name) override;

protected Q_SLOTS:
	void signalTriggered(int signal) override;

private Q_SLOTS:
	void sendWatchdog();

	void onStarted(bool success);
	void onReloaded(bool success);
	void onStopped(int exitCode);
	void onPaused(bool success);

private:
	QTimer *_watchdogTimer = nullptr;
	QMultiHash<QByteArray, int> _sockets;

	int run(int &argc, char **argv, int flags);
	int stop(int pid);
	int reload(int pid);

	void prepareWatchdog();
	bool findArg(const char *command, int argc, char **argv, int &pid);

	static void systemdMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &message);
};

#endif // SYSTEMDSERVICEBACKEND_H
