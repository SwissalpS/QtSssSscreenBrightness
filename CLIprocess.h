#ifndef CLIPROCESS_H
#define CLIPROCESS_H

#include <QProcess>



class CLIprocess : public QProcess {

	Q_OBJECT

protected:
	QStringList asErrors;
	QStringList asOutput;

	bool bHaveError;
	bool bHaveEnded;
	bool bHaveSetSpeed;
	bool bHaveStarted;
	bool bHaveStartedSorta;

protected slots:
	void onGotError(QProcess::ProcessError error);
	void onGotFinished(int iExitCode, QProcess::ExitStatus iExitStatus);
	void onGotReadyRead();
	void onGotStarted();
	void onGotStateChanged(QProcess::ProcessState newState);
	void onGotStdErr();
	void onGotStdOut();

public:
	explicit CLIprocess(QObject *pParent = 0);
	virtual ~CLIprocess();

	inline bool hasProcessEnded()      { return this->bHaveEnded; }
	inline bool hasProcessError()      { return this->bHaveError; }
	inline bool hasProcessStarted()    { return this->bHaveStarted; }
	inline QStringList processErrors() { return this->asErrors; }
	inline QStringList processOutput() { return this->asOutput; }

public slots:

signals:
	void crashed();
	void ended();
	void message(QString sMessage);
	void started();

}; // OmxProcess



#endif // CLIPROCESS_H
