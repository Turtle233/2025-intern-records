#include "wind_view.h"
#include <QtWidgets/QApplication>
#include <QCoreApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QTranslator translator(qApp);
	if (translator.load("translations/zh_CN.qm"))
		qApp->installTranslator(&translator);

	wind_view w;
	w.show();
	return a.exec();
}
