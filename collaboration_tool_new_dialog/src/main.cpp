// v20250618

#include "new_project_dialog.h"
#include <QtWidgets/QApplication>
#include <QTranslator>
#include <QString>
#include <QDebug>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QTranslator translator(qApp);
	if (translator.load(":/translations/zh_CN.qm"))
	{
		qApp->installTranslator(&translator);
	}

	new_project_dialog w;

	if (w.exec() == QDialog::Accepted)
	{
		w.get_project_name();
		w.get_project_info();
		w.get_list_data(w.admin_list_getter());
		w.get_list_data(w.editor_list_getter());
		w.get_list_data(w.readonly_list_getter());
	}

	return 0;
}