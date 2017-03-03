#include "Calculator.h"
#include <QtWidgets/QApplication>

/**
*maybe here are lots of bugs;
*if you are interested in fix bug, welcome you to fix them!
*and welcome you to make the program more powerful
*if you have good suggestions , welcome email me. e-mail: songapril@qq.com
*/


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.setMinimumSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));
	w.setMaximumSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));
	w.setWindowTitle("calculator");
	w.show();
	return a.exec();
}
