#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>



namespace Ui {



class MainWindow;



} // namespace Ui



class MainWindow : public QMainWindow {

	Q_OBJECT

private:
	Ui::MainWindow *pUI;

private slots:
	void on_checkBox_clicked(bool bChecked);
	void on_verticalScrollBar_valueChanged(int iNewValue);

protected:
	void changeEvent(QEvent *e);

public:
	explicit MainWindow(QWidget *pParent = 0);
	~MainWindow();
};

#endif // MAINWINDOW_H
