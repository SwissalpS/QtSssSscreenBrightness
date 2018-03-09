#include "CLIprocess.h"

#include <iostream>
#include <QTimer>
#include <QHash>



CLIprocess::CLIprocess(QObject *pParent) :
	QProcess(pParent),
	bHaveError(false),
	bHaveEnded(false),
	bHaveSetSpeed(false),
	bHaveStarted(false),
	bHaveStartedSorta(false) {

	this->asErrors.empty();
	this->asOutput.empty();

	connect(this, SIGNAL(error(QProcess::ProcessError)),
			this, SLOT(onGotError(QProcess::ProcessError)));

	connect(this, SIGNAL(finished(int,QProcess::ExitStatus)),
			this, SLOT(onGotFinished(int,QProcess::ExitStatus)));

	connect(this, SIGNAL(started()),
			this, SLOT(onGotStarted()));

	connect(this, SIGNAL(stateChanged(QProcess::ProcessState)),
			this, SLOT(onGotStateChanged(QProcess::ProcessState)));

	connect(this, SIGNAL(readyReadStandardError()),
			this, SLOT(onGotStdErr()));

	connect(this, SIGNAL(readyReadStandardOutput()),
			this, SLOT(onGotStdOut()));

	connect(this, SIGNAL(readyRead()),
			this, SLOT(onGotReadyRead()));

} // construct


CLIprocess::~CLIprocess() {

	disconnect(this);

	this->asErrors.empty();
	this->asOutput.empty();

} // deconstruct


void CLIprocess::onGotError(QProcess::ProcessError error) {

	// this does not need to be fatal, it may even be useful for info

	QString sMessage = "CLIprocess:onGotError:";

	switch (error) {

		case QProcess::FailedToStart:

			sMessage.append(tr("Failed To Start."));

			break;

		case QProcess::Crashed:

			sMessage.append(tr("Crashed."));

			break;

		case QProcess::Timedout:

			sMessage.append(tr("Timed-out."));

			break;

		case QProcess::ReadError:

			sMessage.append(tr("Read Error."));

			break;

		case QProcess::WriteError:

			sMessage.append(tr("Write Error."));

			break;

		case QProcess::UnknownError:
		default:

			sMessage.append(tr("Unknown Error"));

			break;

	} // switch error

	this->bHaveError = true;

	this->asErrors.append(sMessage);

	std::cout << sMessage.toStdString() << std::endl;

} // onGotError


void CLIprocess::onGotFinished(int iExitCode, QProcess::ExitStatus iExitStatus) {
	//std::cout << "CLIprocess:onGotFinished: " << iExitCode << ":" << iExitStatus << std::endl;

	this->bHaveEnded = true;

	if (QProcess::CrashExit == iExitStatus) Q_EMIT this->crashed();

	Q_EMIT this->ended();

} // onGotFinished


void CLIprocess::onGotReadyRead() {
	//std::cout << "CLIprocess::onGotReadyRead " << std::endl;

	// wait for readyStdOut
	//std::cout << QString(this->readAll()).toStdString() << std::endl;

} // onGotReadyRead


void CLIprocess::onGotStarted() {
	//std::cout << "CLIprocess:onGotStarted: " << std::endl;

	Q_EMIT this->started();

} // onGotStarted


void CLIprocess::onGotStateChanged(QProcess::ProcessState newState) {

	QString sMessage = "CLIprocess:onGotStateChanged: ";

	switch (newState) {

		case QProcess::NotRunning:

			sMessage.append(tr("NotRunning"));

			break;

		case QProcess::Starting:

			sMessage.append(tr("Starting"));

			break;

		case QProcess::Running:

			sMessage.append(tr("Running"));

			break;

		default:

			sMessage.append(tr("Unknown"));

			break;

	} // switch newState

	//std::cout << sMessage.toStdString() << std::endl;

	Q_EMIT this->message(sMessage);

} // onGotStateChanged


void CLIprocess::onGotStdErr() {
	std::cout << "CLIprocess:onGotStdErr: " << std::endl;

	this->bHaveError = true;

	QString sMessage(this->readAllStandardError());
	std::cout << sMessage.toStdString() << std::endl;

	this->asErrors.append(sMessage);

	Q_EMIT this->message(sMessage);

} // onGotStdErr


void CLIprocess::onGotStdOut() {
	//std::cout << "CLIprocess:onGotStdOut: " << std::endl;

	QString sMessage(this->readAll());
	//std::cout << sMessage.toStdString() << std::endl;

	this->asOutput.append(sMessage);

	Q_EMIT this->message(sMessage);

} // onGotStdOut

