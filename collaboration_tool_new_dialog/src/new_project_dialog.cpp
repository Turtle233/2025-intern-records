#include "new_project_dialog.h"
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFont>
#include <QListWidget>
#include <QInputDialog>
#include <QDebug>
#include <QAction>
#include <QPoint>
#include <QMenu>
#include <QCursor>
#include <QFile>
#include <QApplication>
#include "translations/zh_CN.h"

new_project_dialog::new_project_dialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	// load global style sheet from qss resource
	QFile file(":/style/style.qss");
	if (file.open(QFile::ReadOnly))
	{
		qApp->setStyleSheet(file.readAll());
	}

	setWindowTitle(NEWDIALOG_TITLE);
	resize(810, 520);
	setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

	QLabel *top_left_label = new QLabel;
	top_left_label->setText(NEWDIALOG_PROGRAM_NAME);

	top_left_line = new QLineEdit(this);
	top_left_line->setMinimumHeight(30);
	top_left_line->setPlaceholderText(NEWDIALOG_PROGRAM_NAME_HINT);
	QString get_top_left_line = top_left_line->text();

	QLabel *top_right_label = new QLabel;
	top_right_label->setText(NEWDIALOG_PROGRAM_INFO);

	top_right_line = new QLineEdit(this);
	top_right_line->setMinimumHeight(30);
	top_right_line->setPlaceholderText(NEWDIALOG_PROGRAM_INFO_HINT);
	QString get_top_right_line = top_right_line->text();

	// admin user group
	QLabel *adminUser_label = new QLabel;
	adminUser_label->setText(NEWDIALOG_ADMIN);
	QPushButton *admin_edit_button = new QPushButton;
	admin_edit_button->setText(NEWDIALOG_ADD);
	admin_edit_button->setMinimumSize(55, 25);
	QHBoxLayout *admin_layout = new QHBoxLayout;
	admin_layout->addWidget(adminUser_label);
	admin_layout->addStretch();
	admin_layout->addWidget(admin_edit_button);
	admin_list = new QListWidget();
	admin_list->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(admin_edit_button, &QPushButton::clicked, this, [=]()
			{ add_to_list(admin_list); });
	connect(admin_list, &QListWidget::customContextMenuRequested, this, [=]()
			{ show_context(admin_list); });

	// editor user group
	QLabel *editorUser_label = new QLabel;
	editorUser_label->setText(NEWDIALOG_EDITOR);
	QPushButton *editor_user_button = new QPushButton;
	editor_user_button->setText(NEWDIALOG_ADD);
	editor_user_button->setMinimumSize(55, 25);
	QHBoxLayout *editor_user_layout = new QHBoxLayout;
	editor_user_layout->addWidget(editorUser_label);
	editor_user_layout->addStretch();
	editor_user_layout->addWidget(editor_user_button);
	editor_user_list = new QListWidget();
	editor_user_list->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(editor_user_button, &QPushButton::clicked, this, [=]()
			{ add_to_list(editor_user_list); });
	connect(editor_user_list, &QListWidget::customContextMenuRequested, this, [=]()
			{ show_context(editor_user_list); });

	// read-only user group
	QLabel *readonlyUser_label = new QLabel;
	readonlyUser_label->setText(NEWDIALOG_READONLY);
	QPushButton *readonly_user_button = new QPushButton;
	readonly_user_button->setText(NEWDIALOG_ADD);
	readonly_user_button->setMinimumSize(55, 25);
	QHBoxLayout *readonly_user_layout = new QHBoxLayout;
	readonly_user_layout->addWidget(readonlyUser_label);
	readonly_user_layout->addStretch();
	readonly_user_layout->addWidget(readonly_user_button);
	readonly_user_list = new QListWidget();
	readonly_user_list->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(readonly_user_button, &QPushButton::clicked, this, [=]()
			{ add_to_list(readonly_user_list); });
	connect(readonly_user_list, &QListWidget::customContextMenuRequested, this, [=]()
			{ show_context(readonly_user_list); });

	// bottom action buttons
	QPushButton *ok_button = new QPushButton;
	ok_button->setText(NEWDIALOG_ACCEPT);
	ok_button->setMinimumSize(85, 30);

	QPushButton *cancel_button = new QPushButton;
	cancel_button->setText(NEWDIALOG_CANCEL);
	cancel_button->setMinimumSize(85, 30);
	cancel_button->setObjectName("cancel_button"); // used for .qss styling
	connect(ok_button, &QPushButton::clicked, this, &QDialog::accept);
	connect(cancel_button, &QPushButton::clicked, this, &QDialog::close);

	// horizontal layout for bottom buttons
	QHBoxLayout *button_layout = new QHBoxLayout;
	button_layout->addStretch();
	button_layout->addWidget(ok_button);
	button_layout->setSpacing(12);
	button_layout->addWidget(cancel_button);

	// top row layout for program name & information fields
	QHBoxLayout *top_layout = new QHBoxLayout;
	top_layout->addWidget(top_left_label);
	top_layout->addWidget(top_left_line);
	top_layout->addSpacing(8);
	top_layout->addWidget(top_right_label);
	top_layout->addWidget(top_right_line);

	// grid layout for three user groups (admin / editor / read-only)
	QGridLayout *grid_layout = new QGridLayout;
	grid_layout->addLayout(admin_layout, 0, 0);
	grid_layout->addLayout(editor_user_layout, 0, 1);
	grid_layout->addLayout(readonly_user_layout, 0, 2);
	grid_layout->addWidget(admin_list, 1, 0);
	grid_layout->addWidget(editor_user_list, 1, 1);
	grid_layout->addWidget(readonly_user_list, 1, 2);
	grid_layout->setHorizontalSpacing(10);

	// main vertical layout for the dialog
	QVBoxLayout *main_layout = new QVBoxLayout;
	main_layout->addSpacing(5);
	main_layout->addLayout(top_layout);
	main_layout->addSpacing(15);
	main_layout->addLayout(grid_layout);
	main_layout->addSpacing(5);
	main_layout->addLayout(button_layout);

	setLayout(main_layout);
}

// add text items to a given list widget (used by "Add" button)
void new_project_dialog::add_to_list(QListWidget *target_list)
{
	bool ok = false;

	QString list_text = QInputDialog::getText(this, NEWDIALOG_ADD_USER, NEWDIALOG_TYPE_TO_ADD_USER, QLineEdit::Normal, QString(), &ok);

	if (!ok || list_text.isEmpty())
		return;

	target_list->addItem(list_text);
}

// design mouse right-click context menu for list widgets
void new_project_dialog::show_context(QListWidget *target_list)
{
	// build a context menu for item operations on the provided list widget
	QMenu context(this); // create a context menu anchored to this dialog

	QAction *move_to_head_action = context.addAction(NEWDIALOG_MOVETOHEAD); // move selected item to the top
	QAction *move_up_action = context.addAction(NEWDIALOG_MOVEUP);
	QAction *move_down_action = context.addAction(NEWDIALOG_MOVEDOWN);
	QAction *delete_action = context.addAction(NEWDIALOG_DELETE); // delete selected item

	connect(move_to_head_action, &QAction::triggered, this, [=] { // move the selected item to the first row
		QListWidgetItem *selected_item = target_list->currentItem();
		if (selected_item != 0)
		{
			QListWidgetItem *cloned_item = selected_item->clone();
			delete selected_item;
			target_list->insertItem(0, cloned_item); // insert at row 0

			target_list->setCurrentItem(cloned_item); // keep visual selection on the moved item
		}
	});

	connect(delete_action, &QAction::triggered, this, [=]() { // delete the current selected item
		QListWidgetItem *selected_item = target_list->currentItem();
		if (selected_item != nullptr)
		{
			delete selected_item;
		}
	});

	connect(move_up_action, &QAction::triggered, this, [=]()
			{
				QListWidgetItem *selected_item = target_list->currentItem();
				if (selected_item)
				{
					int current_row = target_list->row(selected_item);		 // current row index of the selected item
					target_list->takeItem(current_row);						 // temporarily remove the item from the list
					target_list->insertItem(current_row - 1, selected_item); // insert it back to the row above
					target_list->setCurrentItem(selected_item);				 // keep it selected after moving
				} });

	connect(move_down_action, &QAction::triggered, this, [=]()
			{
				QListWidgetItem *selected_item = target_list->currentItem();
				if (selected_item)
				{
					int current_row = target_list->row(selected_item);
					target_list->takeItem(current_row);						 // temporarily remove the item
					target_list->insertItem(current_row + 1, selected_item); // insert it back to the row below
					target_list->setCurrentItem(selected_item);              // keep selection on the moved item
				} });

	// pop up the context menu at current mouse cursor position and block until a choice is made
	context.exec(QCursor::pos());
}

// get and print project name
QString new_project_dialog::get_project_name() const
{
	qDebug().noquote() << "\nThe project name is : ";
	qDebug() << top_left_line->text() << endl;
	return top_left_line->text();
}

// get and print project information
QString new_project_dialog::get_project_info() const
{
	qDebug().noquote() << "The project information is : ";
	qDebug() << top_right_line->text() << endl;
	return top_right_line->text();
}

// get and print all entries in a list widget
QString new_project_dialog::get_list_data(QListWidget *targeted_list)
{
	QString arr_listData;
	for (int i = 0; i < targeted_list->count(); i++)
	{
		QListWidgetItem *item = targeted_list->item(i);
		arr_listData += item->text();
		arr_listData += "\n";
	}

	qDebug().noquote() << "The content for this list is printed as: " << endl;
	qDebug().noquote() << arr_listData;

	return arr_listData;
}

// general getters for underlying list widgets
QListWidget *new_project_dialog::admin_list_getter()
{
	return admin_list;
}
QListWidget *new_project_dialog::editor_list_getter()
{
	return editor_user_list;
}
QListWidget *new_project_dialog::readonly_list_getter()
{
	return readonly_user_list;
}

// destructor
new_project_dialog::~new_project_dialog()
{
}
