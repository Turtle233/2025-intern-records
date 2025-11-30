#pragma once

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QListWidget>
#include <QPoint>

#include <QtWidgets/QDialog>
#include "ui_new_project_dialog.h"

class new_project_dialog : public QDialog
{
	Q_OBJECT

public:
	new_project_dialog(QWidget *parent = nullptr);
	~new_project_dialog();

	QListWidget *admin_list_getter();
	QListWidget *editor_list_getter();
	QListWidget *readonly_list_getter();

	QString get_project_name() const;
	QString get_project_info() const;
	QString get_list_data(QListWidget *x);

protected slots:
	void add_to_list(QListWidget *x);
	void show_context(QListWidget *x);

private:
	Ui::new_project_dialogClass ui;

	QLineEdit *top_left_line;
	QLineEdit *top_right_line;

	QListWidget *admin_list;
	QListWidget *editor_user_list;
	QListWidget *readonly_user_list;
};
