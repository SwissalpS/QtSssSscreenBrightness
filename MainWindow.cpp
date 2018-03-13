#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CLIprocess.h"



MainWindow::MainWindow(QWidget *pParent) :
	QMainWindow(pParent),
	pUI(new Ui::MainWindow) {

	pUI->setupUi(this);

	// get current value
	CLIprocess *pP = new CLIprocess(this);
	//pP->setProgram("stdbuf -o0 xrandr --verbose | awk '/Brightness/ { print $2; exit }'");
	pP->start("/home/luke/gitSwissalpS/FedoraScripts/graphics/getBrightnessXrandr.sh");

	pP->waitForFinished();

	float fCurrent = 0.55f;

	if (!pP->hasProcessError()) {

		fCurrent = pP->processOutput().last().toFloat();

	} // if got result

	int iCurrent = (int)(fCurrent * 1000);
	this->pUI->verticalScrollBar->setValue(iCurrent);

	delete pP;

} // construct


MainWindow::~MainWindow() {

	delete this->pUI;

} // dealloc


void MainWindow::changeEvent(QEvent *pEvent) {

	QMainWindow::changeEvent(pEvent);

	switch (pEvent->type()) {

		case QEvent::LanguageChange: pUI->retranslateUi(this); break;

		default:
		break;

	} // switch type

} // changeEvent


void MainWindow::on_checkBox_clicked(bool bChecked) {

	QScrollBar *pS = this->pUI->verticalScrollBar;
	if (bChecked) {

		pS->setMaximum(10000);

	} else {

		pS->setMaximum(1000);

	} // if boost or not

} // on_checkBox_clicked


void MainWindow::on_verticalScrollBar_valueChanged(int iNewValue) {

	double fValue = ((double)iNewValue) * 0.001f;
	QString sValue = QString::number(fValue, 'f', 3);

	CLIprocess *pP = new CLIprocess(this);

	pP->start("xrandr --output eDP --brightness " + sValue);

	// keep from possibly overflowing by pausing execution
	pP->waitForFinished();

	delete pP;

} // on_verticalScrollBar_valueChanged
