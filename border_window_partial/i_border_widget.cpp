#include "i_border_widget.h"
#include <QPainter>
#include <QStyleOption>
#include <QMouseEvent>

#define DEFAULT_BORDER_WIDTH 2

i_border_widget::i_border_widget(int index_x, int index_y, QWidget *parent)
    : QWidget(parent), index_x_(index_x), index_y_(index_y)
{
    focused_ = false;
    last_pos_x_ = 0;
    last_pos_y_ = 0;

    QString tag = "border_" + ver_tag(index_y_) + "_" + hor_tag(index_x_);
    setProperty("border_tag", tag);

    set_hor_size(index_x_);
    set_ver_size(index_y_);
}

i_border_widget::~i_border_widget()
{
}

void i_border_widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        focused_ = true;
        last_pos_x_ = event->globalX();
        last_pos_y_ = event->globalY();
    }
}

void i_border_widget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        focused_ = false;
    }
}

void i_border_widget::mouseMoveEvent(QMouseEvent *event)
{
    if (focused_)
    {
        emit sig_resize(event->globalX() - last_pos_x_,
                        event->globalY() - last_pos_y_);

        last_pos_x_ = event->globalX();
        last_pos_y_ = event->globalY();
    }
}

void i_border_widget::paintEvent(QPaintEvent *)
{
    QStyleOption option;
    option.initFrom(this);

    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}
