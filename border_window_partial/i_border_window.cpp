#include "i_border_window.h"
#include <QStyleOption>
#include <QPainter>
#include <QApplication>

i_border_window::i_border_window(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);

    title_widget_ = new i_title_widget();
    center_widget_ = new QWidget();

    // Initialize controls
    title_widget_->set_button_flag(BUTTON_MIN | BUTTON_NOR | BUTTON_EXT);

    // Layout
    main_grid_ = new QGridLayout();
    main_grid_->addWidget(top_left_border_, 0, 0, 1, 1);
    main_grid_->addWidget(top_center_border_, 0, 1, 1, 1);
    main_grid_->addWidget(top_right_border_, 0, 2, 1, 1);

    main_grid_->addWidget(center_left_border_, 1, 0, 2, 1);
    main_grid_->addWidget(title_widget_, 1, 1, 1, 1);
    main_grid_->addWidget(center_widget_, 2, 1, 1, 1);
    main_grid_->addWidget(center_right_border_, 1, 2, 2, 1);

    main_grid_->addWidget(bottom_left_border_, 3, 0, 1, 1);
    main_grid_->addWidget(bottom_center_border_, 3, 1, 1, 1);
    main_grid_->addWidget(bottom_right_border_, 3, 2, 1, 1);

    main_grid_->setMargin(0);
    main_grid_->setSpacing(0);

    main_grid_->setColumnStretch(0, 0);
    main_grid_->setColumnStretch(1, 1);
    main_grid_->setColumnStretch(2, 0);

    main_grid_->setRowStretch(0, 0);
    main_grid_->setRowStretch(1, 0);
    main_grid_->setRowStretch(2, 1);
    main_grid_->setRowStretch(3, 0);

    setCentralWidget(new QWidget());
    centralWidget()->setLayout(main_grid_);

    connect(title_widget_, SIGNAL(sig_move(int, int)), this, SLOT(on_title_move(int, int)));
    connect(title_widget_, SIGNAL(sig_min()), this, SLOT(on_title_min()));
    connect(title_widget_, SIGNAL(sig_max()), this, SLOT(on_title_max()));
    connect(title_widget_, SIGNAL(sig_ext()), this, SLOT(on_title_ext()));
}

i_border_window::~i_border_window()
{
}

void i_border_window::on_title_move(int x, int y)
{
    if (isMaximized())
    {
        showNormal();
        title_widget_->set_button_flag(BUTTON_MIN | BUTTON_MAX | BUTTON_EXT);
        QApplication::processEvents();

        QPoint cur = QCursor::pos();
        int title_len = 20;
        QPoint normalized(width() / 2, title_len / 2);

        move(cur - normalized);
        return;
    }

    QRect r = geometry();
    r.moveLeft(r.left() + x);
    r.moveTop(r.top() + y);
    setGeometry(r);
}

void i_border_window::on_title_min()
{
    showMinimized();
}

void i_border_window::on_title_max()
{
    showMaximized();
    title_widget_->set_button_flag(BUTTON_MIN | BUTTON_NOR | BUTTON_EXT);
}

void i_border_window::on_title_ext()
{
    close();
}
